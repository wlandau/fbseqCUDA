#ifndef UTIL_HH2HD_H
#define UTIL_HH2HD_H

void hh2hd(SEXP hh, chain_t *hd){
  int C = li(hh, "C")[0],
      G = li(hh, "G")[0],
      L = li(hh, "L")[0],
      N = li(hh, "N")[0],
      P = li(hh, "P")[0];

  hd->C = C;
  hd->G = G;
  hd->L = L;
  hd->N = N;
  hd->P = P;

  memcpy(hd->bounds, lr(hh, "bounds"), C * sizeof(double));
  memcpy(hd->contrasts, lr(hh, "contrasts"), C * L * sizeof(double));
  memcpy(hd->counts, li(hh, "counts"), N * G * sizeof(int));
  memcpy(hd->design, lr(hh, "design"), L * N * sizeof(double));
  memcpy(hd->propositions, li(hh, "propositions"), P * C * sizeof(int));

  memcpy(hd->countSums_g, li(hh, "countSums_g"), G * sizeof(int));
  memcpy(hd->countSums_n, li(hh, "countSums_n"), N * sizeof(int));
  memcpy(hd->designUnique, lr(hh, "designUnique"), L * N * sizeof(double));
  memcpy(hd->designUniqueN, li(hh, "designUniqueN"), L * sizeof(int));
  memcpy(hd->probs, lr(hh, "probs"), P * G * sizeof(double));
  memcpy(hd->seeds, li(hh, "seeds"), N * G * sizeof(int));

  memcpy(hd->a, lr(hh, "a"), sizeof(double));
  memcpy(hd->b, lr(hh, "b"), sizeof(double));
  memcpy(hd->c, lr(hh, "c"), L * sizeof(double));
  memcpy(hd->d, lr(hh, "d"), sizeof(double));
  memcpy(hd->h, lr(hh, "h"), N * sizeof(double));
  memcpy(hd->k, lr(hh, "k"), L * sizeof(double));
  memcpy(hd->q, lr(hh, "q"), L * sizeof(double));
  memcpy(hd->r, lr(hh, "r"), L * sizeof(double));
  memcpy(hd->s, lr(hh, "s"), L * sizeof(double));

  memcpy(hd->beta, lr(hh, "betaStart"), L * G * sizeof(double));
  memcpy(hd->epsilon, lr(hh, "epsilonStart"), N * G * sizeof(double));
  memcpy(hd->gamma, lr(hh, "gammaStart"), G * sizeof(double));
  memcpy(hd->nu, lr(hh, "nuStart"), sizeof(double));
  memcpy(hd->sigmaSquared, lr(hh, "sigmaSquaredStart"), L * sizeof(double));
  memcpy(hd->tau, lr(hh, "tauStart"), sizeof(double));
  memcpy(hd->theta, lr(hh, "thetaStart"), L * sizeof(double));
  memcpy(hd->xi, lr(hh, "xiStart"), L * G * sizeof(double));
}

#endif // UTIL_HH2HD_H
