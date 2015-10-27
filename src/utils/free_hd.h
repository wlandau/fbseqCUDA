#ifndef FREE_HD_H
#define FREE_HD_H

void free_hd(chain_t *hd){

  CUDA_CALL(cudaFree(hd->counts));
  CUDA_CALL(cudaFree(hd->countSums_g));
  CUDA_CALL(cudaFree(hd->countSums_n));
  CUDA_CALL(cudaFree(hd->design));
  CUDA_CALL(cudaFree(hd->seeds));

  CUDA_CALL(cudaFree(hd->aGamma));
  CUDA_CALL(cudaFree(hd->aRho));
  CUDA_CALL(cudaFree(hd->bGamma));
  CUDA_CALL(cudaFree(hd->bRho));
  CUDA_CALL(cudaFree(hd->c));
  CUDA_CALL(cudaFree(hd->dGamma));
  CUDA_CALL(cudaFree(hd->dRho));
  CUDA_CALL(cudaFree(hd->k));
  CUDA_CALL(cudaFree(hd->r));
  CUDA_CALL(cudaFree(hd->s));

  CUDA_CALL(cudaFree(hd->beta));
  CUDA_CALL(cudaFree(hd->epsilon));
  CUDA_CALL(cudaFree(hd->gamma));
  CUDA_CALL(cudaFree(hd->nuGamma));
  CUDA_CALL(cudaFree(hd->nuRho));
  CUDA_CALL(cudaFree(hd->rho));
  CUDA_CALL(cudaFree(hd->sigmaSquared));
  CUDA_CALL(cudaFree(hd->tauGamma));
  CUDA_CALL(cudaFree(hd->tauRho));
  CUDA_CALL(cudaFree(hd->theta));
  CUDA_CALL(cudaFree(hd->xi));

  CUDA_CALL(cudaFree(hd->betaStart));
  CUDA_CALL(cudaFree(hd->epsilonStart));
  CUDA_CALL(cudaFree(hd->gammaStart));
  CUDA_CALL(cudaFree(hd->nuGammaStart));
  CUDA_CALL(cudaFree(hd->nuRhoStart));
  CUDA_CALL(cudaFree(hd->rhoStart));
  CUDA_CALL(cudaFree(hd->sigmaSquaredStart));
  CUDA_CALL(cudaFree(hd->tauGammaStart));
  CUDA_CALL(cudaFree(hd->tauRhoStart));
  CUDA_CALL(cudaFree(hd->thetaStart));
  CUDA_CALL(cudaFree(hd->xiStart));

  CUDA_CALL(cudaFree(hd->betaPostMean));
  CUDA_CALL(cudaFree(hd->epsilonPostMean));
  CUDA_CALL(cudaFree(hd->gammaPostMean));
  CUDA_CALL(cudaFree(hd->nuGammaPostMean));
  CUDA_CALL(cudaFree(hd->nuRhoPostMean));
  CUDA_CALL(cudaFree(hd->rhoPostMean));
  CUDA_CALL(cudaFree(hd->sigmaSquaredPostMean));
  CUDA_CALL(cudaFree(hd->tauGammaPostMean));
  CUDA_CALL(cudaFree(hd->tauRhoPostMean));
  CUDA_CALL(cudaFree(hd->thetaPostMean));
  CUDA_CALL(cudaFree(hd->xiPostMean));

  CUDA_CALL(cudaFree(hd->betaPostMeanSquare));
  CUDA_CALL(cudaFree(hd->epsilonPostMeanSquare));
  CUDA_CALL(cudaFree(hd->gammaPostMeanSquare));
  CUDA_CALL(cudaFree(hd->nuGammaPostMeanSquare));
  CUDA_CALL(cudaFree(hd->nuRhoPostMeanSquare));
  CUDA_CALL(cudaFree(hd->rhoPostMeanSquare));
  CUDA_CALL(cudaFree(hd->sigmaSquaredPostMeanSquare));
  CUDA_CALL(cudaFree(hd->tauGammaPostMeanSquare));
  CUDA_CALL(cudaFree(hd->tauRhoPostMeanSquare));
  CUDA_CALL(cudaFree(hd->thetaPostMeanSquare));
  CUDA_CALL(cudaFree(hd->xiPostMeanSquare));

  CUDA_CALL(cudaFree(hd->states));
  CUDA_CALL(cudaFree(hd->aux));

  free(hd);
}

#endif // FREE_HD_H
