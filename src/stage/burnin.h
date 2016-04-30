#ifndef STAGE_BURNIN_H
#define STAGE_BURNIN_H

void burnin(SEXP hh, chain_t *hd, chain_t *dd){
  int m,
    burnin = li(hh, "burnin")[0],
    print_every = burnin + 2,
    verbose = li(hh, "verbose")[0];

  set_adapt(dd, 1);

  if(burnin && verbose){
    print_every = burnin/verbose + (burnin < verbose);
    Rprintf("Starting burnin.\n");
  }

  for(m = 0; m < burnin; ++m){
    if(verbose && !((m + 1) % print_every))
      Rprintf("  burnin iteration %d of %d.\n", m + 1, burnin);

    iteration(hh, hd, dd, m);
  }
}

#endif // STAGE_BURNIN_H
