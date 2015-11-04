#ifndef CHAIN_H
#define CHAIN_H

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
  double *probs,
         *seeds,

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
