#ifndef UTIL_ALLOC_HD_H
#define UTIL_ALLOC_HD_H

chain_t *alloc_hd(SEXP hh){
  int C = li(hh, "C")[0],
      G = li(hh, "G")[0],
      L = li(hh, "L")[0],
      N = li(hh, "N")[0],
      P = li(hh, "P")[0];

  chain_t *hd = (chain_t *) calloc(1, sizeof(chain_t));

  hd->bounds = (double*) calloc(C , sizeof(double));
  hd->contrasts = (double*) calloc(C * L , sizeof(double));
  hd->counts = (int*) calloc(N * G , sizeof(int));
  hd->design = (double*) calloc(L * N , sizeof(double));
  hd->propositions = (int*) calloc(P * C , sizeof(int));

  hd->countSums_g = (int*) calloc(G , sizeof(int));
  hd->countSums_n = (int*) calloc(N , sizeof(int));
  hd->designUnique = (double*) calloc(L * N , sizeof(double));
  hd->designUniqueN = (int*) calloc(L , sizeof(int));
  hd->probs = (double*) calloc(P * G , sizeof(double));
  hd->seeds = (int*) calloc(N * G , sizeof(int));

  hd->a = (double*) calloc(1, sizeof(double));
  hd->b = (double*) calloc(1, sizeof(double));
  hd->c = (double*) calloc(L , sizeof(double));
  hd->d = (double*) calloc(1, sizeof(double));
  hd->h = (double*) calloc(N , sizeof(double));
  hd->k = (double*) calloc(L , sizeof(double));
  hd->q = (double*) calloc(L , sizeof(double));
  hd->r = (double*) calloc(L , sizeof(double));
  hd->s = (double*) calloc(L , sizeof(double));

  hd->beta = (double*) calloc(L * G , sizeof(double));
  hd->epsilon = (double*) calloc(N * G , sizeof(double));
  hd->gamma = (double*) calloc(G , sizeof(double));
  hd->nu = (double*) calloc(1, sizeof(double));
  hd->sigmaSquared = (double*) calloc(L , sizeof(double));
  hd->tau = (double*) calloc(1, sizeof(double));
  hd->theta = (double*) calloc(L , sizeof(double));
  hd->xi = (double*) calloc(L * G , sizeof(double));

  hd->betaStart = (double*) calloc(L * G , sizeof(double));
  hd->epsilonStart = (double*) calloc(N * G , sizeof(double));
  hd->gammaStart = (double*) calloc(G , sizeof(double));
  hd->nuStart = (double*) calloc(1, sizeof(double));
  hd->sigmaSquaredStart = (double*) calloc(L , sizeof(double));
  hd->tauStart = (double*) calloc(1, sizeof(double));
  hd->thetaStart = (double*) calloc(L , sizeof(double));
  hd->xiStart = (double*) calloc(L * G , sizeof(double));

  hd->loglikPostMean = (double*) calloc(1, sizeof(double));
  hd->betaPostMean = (double*) calloc(L * G , sizeof(double));
  hd->epsilonPostMean = (double*) calloc(N * G , sizeof(double));
  hd->gammaPostMean = (double*) calloc(G , sizeof(double));
  hd->nuPostMean = (double*) calloc(1, sizeof(double));
  hd->sigmaSquaredPostMean = (double*) calloc(L , sizeof(double));
  hd->tauPostMean = (double*) calloc(1, sizeof(double));
  hd->thetaPostMean = (double*) calloc(L , sizeof(double));
  hd->xiPostMean = (double*) calloc(L * G , sizeof(double));

  hd->betaPostMeanSquare = (double*) calloc(L * G , sizeof(double));
  hd->epsilonPostMeanSquare = (double*) calloc(N * G , sizeof(double));
  hd->gammaPostMeanSquare = (double*) calloc(G , sizeof(double));
  hd->nuPostMeanSquare = (double*) calloc(1, sizeof(double));
  hd->sigmaSquaredPostMeanSquare = (double*) calloc(L , sizeof(double));
  hd->tauPostMeanSquare = (double*) calloc(1, sizeof(double));
  hd->thetaPostMeanSquare = (double*) calloc(L , sizeof(double));
  hd->xiPostMeanSquare = (double*) calloc(L * G , sizeof(double));

  hd->betaTune = (double*) calloc(L * G , sizeof(double));
  hd->epsilonTune = (double*) calloc(N * G , sizeof(double));
  hd->gammaTune = (double*) calloc(G , sizeof(double));
  hd->nuTune = (double*) calloc(1, sizeof(double));
  hd->sigmaSquaredTune = (double*) calloc(L , sizeof(double));
  hd->tauTune = (double*) calloc(1, sizeof(double));
  hd->thetaTune = (double*) calloc(L , sizeof(double));
  hd->xiTune = (double*) calloc(L * G , sizeof(double));

  hd->betaTuneAux = (double*) calloc(L * G , sizeof(double));
  hd->epsilonTuneAux = (double*) calloc(N * G , sizeof(double));
  hd->gammaTuneAux = (double*) calloc(G , sizeof(double));
  hd->nuTuneAux = (double*) calloc(1, sizeof(double));
  hd->sigmaSquaredTuneAux = (double*) calloc(L , sizeof(double));
  hd->tauTuneAux = (double*) calloc(1, sizeof(double));
  hd->thetaTuneAux = (double*) calloc(L , sizeof(double));
  hd->xiTuneAux = (double*) calloc(L * G , sizeof(double));

  hd->aux = (double*) calloc(N * G , sizeof(double));
  hd->D = (double*) calloc(N * G , sizeof(double));
  hd->loglik = (double*) calloc(1, sizeof(double));

  return hd;
}

#endif // UTIL_ALLOC_HD_H
