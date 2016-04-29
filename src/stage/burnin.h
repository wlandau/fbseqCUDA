#ifndef STAGE_BURNIN_H
#define STAGE_BURNIN_H

void burnin(SEXP hh, chain_t *hd, chain_t *dd){
  int m,
    burnin = li(hh, "burnin")[0],
    print_every = burnin + 2,
    verbose = li(hh, "verbose")[0];

  set_adapt<<<1, 1>>>(dd, 1); KERNEL_CHECK;

  if(burnin && verbose){
    print_every = burnin/verbose + (burnin < verbose);
    Rprintf("Starting burnin on GPU %d.\n", getDevice());
  }

  for(m = 0; m < burnin; ++m){
    if(verbose && !((m + 1) % print_every))
      Rprintf("  burnin iteration %d of %d on GPU %d\n", m + 1, burnin, getDevice());

    iteration(hh, hd, dd, m);
  }
}

#endif // STAGE_BURNIN_H
