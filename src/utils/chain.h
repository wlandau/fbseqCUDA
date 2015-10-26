#ifndef CHAIN_H
#define CHAIN_H

typedef struct {

  int *counts,
      *countSums_g,
      *countSums_n,
      *design,
      G,
      L,
      N,
      *seeds;

  double *aGamma,
         *aRho,
         *bGamma,
         *bRho,
         *c,
         *dGamma,
         *dRho,
         *k,
         *r,
         *s,

         *beta,
         *epsilon,
         *gamma,
         *nuGamma,
         *nuRho,
         *omega,
         *rho,
         *tauGamma,
         *tauRho,
         *theta,
         *xi,

         *betaStart,
         *epsilonStart,
         *gammaStart,
         *nuGammaStart,
         *nuRhoStart,
         *omegaStart,
         *rhoStart,
         *tauGammaStart,
         *tauRhoStart,
         *thetaStart,
         *xiStart,

         *betaPostMean,
         *epsilonPostMean,
         *gammaPostMean,
         *nuGammaPostMean,
         *nuRhoPostMean,
         *omegaPostMean,
         *rhoPostMean,
         *tauGammaPostMean,
         *tauRhoPostMean,
         *thetaPostMean,
         *xiPostMean,

         *betaPostMeanSquare,
         *epsilonPostMeanSquare,
         *gammaPostMeanSquare,
         *nuGammaPostMeanSquare,
         *nuRhoPostMeanSquare,
         *omegaPostMeanSquare,
         *rhoPostMeanSquare,
         *tauGammaPostMeanSquare,
         *tauRhoPostMeanSquare,
         *thetaPostMeanSquare,
         *xiPostMeanSquare,

         *aux;

  curandState_t *states;
} chain_t;

#endif // CHAIN_H
