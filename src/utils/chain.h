#ifndef CHAIN_H
#define CHAIN_H

typedef struct {

  int *counts,
      *countSums_g,
      *countSums_n,
      *designUniqueN,
      G,
      L,
      N,
      *seeds;

  double *design,
         *designUnique,

         *a,
         *b,
         *c,
         *d,
         *k,
         *r,
         *s,
         *w,

         *beta,
         *epsilon,
         *gamma,
         *nu,
         *omegaSquared,
         *rho,
         *sigmaSquared,
         *tau,
         *theta,
         *xi,

         *betaStart,
         *epsilonStart,
         *gammaStart,
         *nuStart,
         *omegaSquaredStart,
         *rhoStart,
         *sigmaSquaredStart,
         *tauStart,
         *thetaStart,
         *xiStart,

         *betaPostMean,
         *epsilonPostMean,
         *gammaPostMean,
         *nuPostMean,
         *omegaSquaredPostMean,
         *rhoPostMean,
         *sigmaSquaredPostMean,
         *tauPostMean,
         *thetaPostMean,
         *xiPostMean,

         *betaPostMeanSquare,
         *epsilonPostMeanSquare,
         *gammaPostMeanSquare,
         *nuPostMeanSquare,
         *omegaSquaredPostMeanSquare,
         *rhoPostMeanSquare,
         *sigmaSquaredPostMeanSquare,
         *tauPostMeanSquare,
         *thetaPostMeanSquare,
         *xiPostMeanSquare,

         *aux,
         *D;

  curandState_t *states;
} chain_t;

#endif // CHAIN_H
