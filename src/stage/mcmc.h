#ifndef STAGE_MCMC_H
#define STAGE_MCMC_H

void mcmc(SEXP hh, chain_t *hd, chain_t *dd){
  int i, m,
    iterations = MAX(0, li(hh, "iterations")[0]),
    print_every = iterations + 2,
    thin = MAX(1, li(hh, "thin")[0]),
    verbose = MAX(0, li(hh, "verbose")[0]);

  set_adapt(dd, 0);

  if(verbose){
    print_every = iterations/verbose + (iterations < verbose);
    Rprintf("Starting MCMC.\n");
  }

  for(m = 0; m < iterations; ++m){
    if(verbose && !((m + 1) % print_every))
      Rprintf("  MCMC iteration %d of %d (thin = %d).\n", m + 1, iterations, thin);

    for(i = 0; i < thin; ++i){
      iteration(hh, hd, dd, m);
      estimates_update(hh, hd, dd);
    }

    hd2hh(hh, hd, m);
  }
}

#endif // STAGE_MCMC_H
