#ifndef UTIL_ESTIMATES_SAVE_H
#define UTIL_ESTIMATES_SAVE_H

void estimates_save(SEXP hh, chain_t *hd){
  int G = (double) li(hh, "G")[0],
      L = (double) li(hh, "L")[0],
      N = (double) li(hh, "N")[0],
      P = (double) li(hh, "P")[0];

  memcpy(lr(hh, "probs"), hd->probs, P * G * sizeof(double));

  memcpy(lr(hh, "betaPostMean"), hd->betaPostMean, L * G * sizeof(double));
  memcpy(lr(hh, "epsilonPostMean"), hd->epsilonPostMean, N * G * sizeof(double));
  memcpy(lr(hh, "gammaPostMean"), hd->gammaPostMean, G * sizeof(double));
  memcpy(lr(hh, "nuPostMean"), hd->nuPostMean, sizeof(double));
  memcpy(lr(hh, "sigmaSquaredPostMean"), hd->sigmaSquaredPostMean, L * sizeof(double));
  memcpy(lr(hh, "tauPostMean"), hd->tauPostMean, sizeof(double));
  memcpy(lr(hh, "thetaPostMean"), hd->thetaPostMean, L * sizeof(double));
  memcpy(lr(hh, "xiPostMean"), hd->xiPostMean, L * G * sizeof(double));

  memcpy(lr(hh, "betaPostMeanSquare"), hd->betaPostMeanSquare, L * G * sizeof(double));
  memcpy(lr(hh, "epsilonPostMeanSquare"), hd->epsilonPostMeanSquare, N * G * sizeof(double));
  memcpy(lr(hh, "gammaPostMeanSquare"), hd->gammaPostMeanSquare, G * sizeof(double));
  memcpy(lr(hh, "nuPostMeanSquare"), hd->nuPostMeanSquare, sizeof(double));
  memcpy(lr(hh, "sigmaSquaredPostMeanSquare"), hd->sigmaSquaredPostMeanSquare, L * sizeof(double));
  memcpy(lr(hh, "tauPostMeanSquare"), hd->tauPostMeanSquare, sizeof(double));
  memcpy(lr(hh, "thetaPostMeanSquare"), hd->thetaPostMeanSquare, L * sizeof(double));
  memcpy(lr(hh, "xiPostMeanSquare"), hd->xiPostMeanSquare, L * G * sizeof(double));

  memcpy(lr(hh, "betaTune"), hd->betaTune, L * G * sizeof(double));
  memcpy(lr(hh, "epsilonTune"), hd->epsilonTune, N * G * sizeof(double));
  memcpy(lr(hh, "gammaTune"), hd->gammaTune, G * sizeof(double));
  memcpy(lr(hh, "nuTune"), hd->nuTune, sizeof(double));
  memcpy(lr(hh, "sigmaSquaredTune"), hd->sigmaSquaredTune, L * sizeof(double));
  memcpy(lr(hh, "tauTune"), hd->tauTune, sizeof(double));
  memcpy(lr(hh, "thetaTune"), hd->thetaTune, L * sizeof(double));
  memcpy(lr(hh, "xiTune"), hd->xiTune, L * G * sizeof(double));
}

#endif // UTIL_ESTIMATES_SAVE_H
