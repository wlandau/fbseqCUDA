#ifndef STAGE_ITERATION_H
#define STAGE_ITERATION_H

void iteration(SEXP hh, chain_t *hd, chain_t *dd, int m){
  set_m(dd, m);

  epsilonSample(hh, hd, dd);
  gammaSample(hh, hd, dd);
  nuSample(hh, hd, dd);
  tauSample(hh, hd, dd);

  betaSample(hh, hd, dd);
  thetaSample(hh, hd, dd);
  sigmaSquaredSample(hh, hd, dd);
  xiSample(hh, hd, dd);
}

#endif // STAGE_ITERATION_H
