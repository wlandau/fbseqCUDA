#ifndef MCMC_H
#define MCMC_H

void mcmc(SEXP hh, chain_t *hd, chain_t *dd){
  int i, m,
    iterations = MAX(0, li(hh, "iterations")[0]),
    print_every = iterations + 2,
    thin = MAX(1, li(hh, "thin")[0]),
    verbose = MAX(0, li(hh, "verbose")[0]);

  set_adapt<<<1, 1>>>(dd, 0);

  if(verbose){
    print_every = iterations/verbose + (iterations < verbose);
    Rprintf("Starting MCMC on GPU %d.\n", getDevice());
  }

  for(m = 0; m < iterations; ++m){
    if(verbose && !((m + 1) % print_every))
      Rprintf("  MCMC iteration %d of %d (thin = %d) on GPU %d\n", m + 1, iterations, thin, getDevice());

    for(i = 0; i < thin; ++i){
      iteration(hh, hd, dd, m);
      estimates_update(hh, dd);
    }

    hd2hh(hh, hd, m);
  }
}

#endif // MCMC_H
