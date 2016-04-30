#ifndef UTIL_RESET_STARTS_H
#define UTIL_RESET_STARTS_H

void reset_starts(SEXP hh, chain_t *hd){

  int G = li(hh, "G")[0],
      L = li(hh, "L")[0],
      N = li(hh, "N")[0];

  memcpy(lr(hh, "betaStart"), hd->beta, L * G * sizeof(double));
  memcpy(lr(hh, "epsilonStart"), hd->epsilon, N * G * sizeof(double));
  memcpy(lr(hh, "gammaStart"), hd->gamma, G * sizeof(double));
  memcpy(lr(hh, "nuStart"), hd->nu, sizeof(double));
  memcpy(lr(hh, "sigmaSquaredStart"), hd->sigmaSquared, L * sizeof(double));
  memcpy(lr(hh, "tauStart"), hd->tau, sizeof(double));
  memcpy(lr(hh, "thetaStart"), hd->theta, L * sizeof(double));
  memcpy(lr(hh, "xiStart"), hd->xi, L * G * sizeof(double));
}

#endif // UTIL_RESET_STARTS_H
