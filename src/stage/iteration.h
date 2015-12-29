#ifndef ITERATION_H
#define ITERATION_H

void iteration(SEXP hh, chain_t *hd, chain_t *dd, int m){
  set_m<<<1, 1>>>(dd, m);

  epsilonSample(hh, hd, dd);
  gammaSample(hh, hd, dd);
  nuSample(hh, hd, dd);
  tauSample(hh, hd, dd);

  betaSample(hh, hd, dd);
  thetaSample(hh, hd, dd);
  sigmaSquaredSample(hh, hd, dd);
  xiSample(hh, hd, dd);
}

#endif // ITERATION_H
