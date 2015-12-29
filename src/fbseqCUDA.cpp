#include "utils/include.h"
#include "utils/element.h"
#include "utils/cuda_usage.h"
#include "utils/chain.h"
#include "utils/alloc_hd.h"
#include "utils/free_hd.h"
#include "utils/hd2hh.h"
#include "utils/hh2hd.h"
#include "utils/estimates_initialize.h"
#include "utils/estimates_save.h"
#include "utils/estimates_scale.h"
#include "utils/estimates_update.h"
#include "utils/xbeta.h"
#include "utils/priors.h"
#include "utils/curand_usage.h"
#include "utils/reset_starts.h"

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
