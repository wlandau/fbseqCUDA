#include "slice/config.h"

#include "util/include.h"
#include "util/element.h"
#include "util/cuda_usage.h"
#include "util/chain.h"
#include "util/alloc_hd.h"
#include "util/free_hd.h"
#include "util/hd2hh.h"
#include "util/hh2hd.h"
#include "util/estimates_initialize.h"
#include "util/estimates_save.h"
#include "util/estimates_scale.h"
#include "util/estimates_update.h"
#include "util/xbeta.h"
#include "util/priors.h"
#include "util/curand_usage.h"
#include "util/reset_starts.h"
#include "util/set.h"

#include "slice/args.h"
#include "slice/targets.h"
#include "slice/slice.h"

#include "gibbs/beta.h"
#include "gibbs/epsilon.h"
#include "gibbs/gamma.h"
#include "gibbs/nu.h"
#include "gibbs/sigmaSquared.h"
#include "gibbs/tau.h"
#include "gibbs/theta.h"
#include "gibbs/xi.h"

#include "stage/iteration.h"
#include "stage/burnin.h"
#include "stage/mcmc.h"
#include "stage/end.h"

extern "C" SEXP fbseqCUDA(SEXP arg){
  SEXP hh = PROTECT(duplicate(arg));

  if(li(hh, "verbose")[0])
    Rprintf("Loading MCMC on GPU %d.\n", getDevice());

  chain_t *hd = alloc_hd(hh);
  hh2hd(hh, hd);

  chain_t *dd;
  CUDA_CALL(cudaMalloc((void**) &dd, sizeof(chain_t)));
  CUDA_CALL(cudaMemcpy(dd, hd, sizeof(chain_t), cudaMemcpyHostToDevice));

  dim3 grid(GRID_N, GRID_G), block(BLOCK_N, BLOCK_G);
  curand_setup_kernel<<<grid, block>>>(dd);

  estimates_initialize(hh, dd);
  burnin(hh, hd, dd);
  mcmc(hh, hd, dd);
  end(hh, hd, dd);

  UNPROTECT(1);
  return hh;
}
