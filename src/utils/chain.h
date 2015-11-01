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
         *delta,
         *epsilon,
         *gamma,
         *nu,
         *omegaSquared,
         *pi,
         *rho,
         *sigmaSquared,
         *tau,
         *theta,
         *xi,

         *betaPostMean,
         *deltaPostMean,
         *epsilonPostMean,
         *gammaPostMean,
         *nuPostMean,
         *omegaSquaredPostMean,
         *piPostMean,
         *rhoPostMean,
         *sigmaSquaredPostMean,
         *tauPostMean,
         *thetaPostMean,
         *xiPostMean,

         *betaPostMeanSquare,
         *deltaPostMeanSquare,
         *epsilonPostMeanSquare,
         *gammaPostMeanSquare,
         *nuPostMeanSquare,
         *omegaSquaredPostMeanSquare,
         *piPostMeanSquare,
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
