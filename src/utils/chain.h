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

         *aGamma,
         *aRho,
         *bGamma,
         *bRho,
         *c,
         *dGamma,
         *dRho,
         *k,
         *r,
         *s,
         *w,

         *beta,
         *epsilon,
         *gamma,
         *nuGamma,
         *nuRho,
         *omegaSquared,
         *psi,
         *rho,
         *sigmaSquared,
         *tauGamma,
         *tauRho,
         *theta,
         *xi,

         *betaStart,
         *epsilonStart,
         *gammaStart,
         *nuGammaStart,
         *nuRhoStart,
         *rhoStart,
         *omegaSquaredStart,
         *psiStart,
         *sigmaSquaredStart,
         *tauGammaStart,
         *tauRhoStart,
         *thetaStart,
         *xiStart,

         *betaPostMean,
         *epsilonPostMean,
         *gammaPostMean,
         *nuGammaPostMean,
         *nuRhoPostMean,
         *omegaSquaredPostMean,
         *psiPostMean,
         *rhoPostMean,
         *sigmaSquaredPostMean,
         *tauGammaPostMean,
         *tauRhoPostMean,
         *thetaPostMean,
         *xiPostMean,

         *betaPostMeanSquare,
         *epsilonPostMeanSquare,
         *gammaPostMeanSquare,
         *nuGammaPostMeanSquare,
         *nuRhoPostMeanSquare,
         *omegaSquaredPostMeanSquare,
         *psiPostMeanSquare,
         *rhoPostMeanSquare,
         *sigmaSquaredPostMeanSquare,
         *tauGammaPostMeanSquare,
         *tauRhoPostMeanSquare,
         *thetaPostMeanSquare,
         *xiPostMeanSquare,

         *aux,
         *D;

  curandState_t *states;
} chain_t;

#endif // CHAIN_H
