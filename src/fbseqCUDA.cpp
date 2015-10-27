#include "utils/include.h"
#include "utils/element.h"
#include "utils/cuda_usage.h"
#include "utils/chain.h"
#include "utils/alloc_hd.h"
#include "utils/free_hd.h"
#include "utils/hd2hh.h"
#include "utils/hh2hd.h"
#include "utils/estimates.h"
#include "utils/xbeta.h"
#include "utils/priors.h"
#include "utils/curand_usage.h"
#include "utils/reset_starts.h"

#include "slice/args.h"
#include "slice/targets.h"
#include "slice/slice.h"

/*

#include "gibbs/beta.h"
#include "gibbs/epsilon.h"
#include "gibbs/gamma.h"
#include "gibbs/nuGamma.h"
#include "gibbs/nuRho.h"
#include "gibbs/rho.h"
#include "gibbs/sigmaSquared.h"
#include "gibbs/tauGamma.h"
#include "gibbs/tauRho.h"
#include "gibbs/theta.h"
#include "gibbs/xi.h"
*/

void iteration(SEXP hh, chain_t *hd, chain_t *dd){
/*

  epsilonSample(hh, hd, dd);
  gammaSample(hh, hd, dd);
  rhoSample(hh, hd, dd);

  betaSample(hh, hd, dd);
  thetaSample(hh, hd, dd);
  sigmaSquaredSample(hh, hd, dd);
  xiSample(hh, hd, dd);

  tauGammaSample(hh, hd, dd);
  tauRhoSample(hh, hd, dd);

  nuGammaSample(hh, hd, dd);
  nuRhoSample(hh, hd, dd);

  */
}

void burnin(SEXP hh, chain_t *hd, chain_t *dd){
  int m,
      burnin = li(hh, "burnin")[0],
      print_every = burnin + 2,
      verbose = li(hh, "verbose")[0];

  if(!burnin) return;

  if(verbose){
    print_every = burnin/verbose + (burnin < verbose);
    Rprintf("Starting burnin on GPU %d.\n", getDevice());
  }

  for(m = 0; m < burnin; ++m){
    if(verbose && !((m + 1) % print_every))
      Rprintf("  burnin iteration %d of %d on GPU %d\n", m + 1, burnin, getDevice());

    iteration(hh, hd, dd);
  }
}

void chain(SEXP hh, chain_t *hd, chain_t *dd){
  int i, m,
      iterations = li(hh, "iterations")[0],
      print_every = iterations + 2,
      thin = li(hh, "thin")[0],
      verbose = li(hh, "verbose")[0];

  if(verbose){
    print_every = iterations/verbose + (iterations < verbose);
    Rprintf("Starting MCMC on GPU %d.\n", getDevice());
  }

  for(m = 0; m < iterations; ++m){
    if(verbose && !((m + 1) % print_every)){
      Rprintf("  MCMC iteration %d of %d on GPU %d", m + 1, iterations, getDevice());
      if(thin) Rprintf(" (thin = %d)", thin);
      Rprintf("\n");
    }


    iteration(hh, hd, dd);
    update_estimates(hh, dd);
    hd2hh(hh, hd, m);

    if(m < iterations - 1)
      for(i = 0; i < thin; ++i)
        iteration(hh, hd, dd);
  }
}

void end(SEXP hh, chain_t *hd, chain_t *dd){
  finish_estimates(hh, hd, dd);
  reset_starts(hh, hd);

  free_hd(hd);
  CUDA_CALL(cudaFree(dd));

  if(li(hh, "verbose")[0])
    Rprintf("Finished MCMC on GPU %d.\n", getDevice());

  cudaDeviceReset();
}

extern "C" SEXP fbseqCUDA(SEXP hh){
  if(li(hh, "verbose")[0])
    Rprintf("Loading MCMC on GPU %d.\n", getDevice());

  chain_t *hd = alloc_hd(hh);
  hh2hd(hh, hd);

  chain_t *dd;
  CUDA_CALL(cudaMalloc((void**) &dd, sizeof(chain_t)));
  CUDA_CALL(cudaMemcpy(dd, hd, sizeof(chain_t), cudaMemcpyHostToDevice));

  dim3 grid(GRID_N, GRID_G), block(BLOCK_N, BLOCK_G);
  curand_setup_kernel<<<grid, block>>>(dd);

  initialize_estimates(hh, dd);
  burnin(hh, hd, dd);
  chain(hh, hd, dd);
  end(hh, hd, dd);

  return hh;
}
