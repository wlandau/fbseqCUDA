#ifndef UTIL_CHAIN_H
#define UTIL_CHAIN_H

typedef struct {

  double *bounds,
         *contrasts;
  int    *counts;
  double *design;
  int    *propositions,

         C,
         *countSums_g,
         *countSums_n;
  double *designUnique;
  int    *designUniqueN,
         G,
         L,
         N,
         P;
  double *probs;
  int    *seeds;

  double *a,
         *b,
         *c,
         *d,
         *h,
         *k,
         *q,
         *r,
         *s,

         *beta,
         *epsilon,
         *gamma,
         *nu,
         *sigmaSquared,
         *tau,
         *theta,
         *xi,

         *betaStart,
         *epsilonStart,
         *gammaStart,
         *nuStart,
         *sigmaSquaredStart,
         *tauStart,
         *thetaStart,
         *xiStart,

         *loglikPostMean,
         *betaPostMean,
         *epsilonPostMean,
         *gammaPostMean,
         *nuPostMean,
         *sigmaSquaredPostMean,
         *tauPostMean,
         *thetaPostMean,
         *xiPostMean,

         *betaPostMeanSquare,
         *epsilonPostMeanSquare,
         *gammaPostMeanSquare,
         *nuPostMeanSquare,
         *sigmaSquaredPostMeanSquare,
         *tauPostMeanSquare,
         *thetaPostMeanSquare,
         *xiPostMeanSquare,

         *betaTune,
         *epsilonTune,
         *gammaTune,
         *nuTune,
         *sigmaSquaredTune,
         *tauTune,
         *thetaTune,
         *xiTune,

         *betaTuneAux,
         *epsilonTuneAux,
         *gammaTuneAux,
         *nuTuneAux,
         *sigmaSquaredTuneAux,
         *tauTuneAux,
         *thetaTuneAux,
         *xiTuneAux,

         *aux,
         *D,
         *loglik;

  int adapt, deviceIndex, m;
} chain_t;

#endif // UTIL_CHAIN_H
