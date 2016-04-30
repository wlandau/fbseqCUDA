#include "util/include.h"
#include "util/config.h"
#include "util/element.h"
#include "util/chain.h"
#include "util/cuda_usage.h"
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

#include "sampler/args.h"
#include "sampler/targets.h"
#include "sampler/slice_step.h"
#include "sampler/sampler_wrap.h"

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
    Rprintf("Loading MCMC.\n");

  chain_t *hd = alloc_hd(hh);
  hh2hd(hh, hd);

  chain_t *dd;
  dd = (chain_t*) calloc(1, sizeof(chain_t));
  memcpy(dd, hd, sizeof(chain_t));

  estimates_initialize(hh, hd, dd);

  burnin(hh, hd, dd);
  mcmc(hh, hd, dd);
  end(hh, hd, dd);

  UNPROTECT(1);
  return hh;
}
