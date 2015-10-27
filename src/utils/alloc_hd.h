#ifndef ALLOC_HD_H
#define ALLOC_HD_H

chain_t *alloc_hd(SEXP hh){
  int N = li(hh, "N")[0],
      L = li(hh, "L")[0],
      G = li(hh, "G")[0];

  chain_t *hd = (chain_t *) calloc(1, sizeof(chain_t));

  CUDA_CALL(cudaMalloc((void**) &(hd->counts), N * G * sizeof(int)));
  CUDA_CALL(cudaMalloc((void**) &(hd->countSums_g), G * sizeof(int)));
  CUDA_CALL(cudaMalloc((void**) &(hd->countSums_n), N * sizeof(int)));
  CUDA_CALL(cudaMalloc((void**) &(hd->design), L * N * sizeof(int)));
  CUDA_CALL(cudaMalloc((void**) &(hd->seeds), N * G * sizeof(int)));

  CUDA_CALL(cudaMalloc((void**) &(hd->aGamma), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->aRho), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->bGamma), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->bRho), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->c), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->dGamma), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->dRho), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->k), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->r), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->s), L * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->beta), L * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->epsilon), N * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->gamma), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nuGamma), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nuRho), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->rho), N * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigmaSquared), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauGamma), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauRho), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->theta), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xi), L * G * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->betaStart), L * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->epsilonStart), N * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->gammaStart), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nuGammaStart), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nuRhoStart), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->rhoStart), N * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigmaSquaredStart), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauGammaStart), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauRhoStart), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->thetaStart), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiStart), L * G * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->betaPostMean), L * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->epsilonPostMean), N * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->gammaPostMean), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nuGammaPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nuRhoPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->rhoPostMean), N * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigmaSquaredPostMean), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauGammaPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauRhoPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->thetaPostMean), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiPostMean), L * G * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->betaPostMeanSquare), L * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->epsilonPostMeanSquare), N * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->gammaPostMeanSquare), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nuGammaPostMeanSquare), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nuRhoPostMeanSquare), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->rhoPostMeanSquare), N * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigmaSquaredPostMeanSquare), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauGammaPostMeanSquare), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauRhoPostMeanSquare), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->thetaPostMeanSquare), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiPostMeanSquare), L * G * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->states), N * G * sizeof(curandState_t)));
  CUDA_CALL(cudaMalloc((void**) &(hd->aux), G * sizeof(double)));

  return hd;
}

#endif // ALLOC_HD_H
