#ifndef FREE_HD_H
#define FREE_HD_H

void free_hd(chain_t *hd){

  CUDA_CALL(cudaFree(hd->bounds));
  CUDA_CALL(cudaFree(hd->contrasts));
  CUDA_CALL(cudaFree(hd->counts));
  CUDA_CALL(cudaFree(hd->design));
  CUDA_CALL(cudaFree(hd->propositions));

  CUDA_CALL(cudaFree(hd->countSums_g));
  CUDA_CALL(cudaFree(hd->countSums_n));
  CUDA_CALL(cudaFree(hd->designUnique));
  CUDA_CALL(cudaFree(hd->designUniqueN));
  CUDA_CALL(cudaFree(hd->probs));
  CUDA_CALL(cudaFree(hd->seeds));

  CUDA_CALL(cudaFree(hd->a));
  CUDA_CALL(cudaFree(hd->b));
  CUDA_CALL(cudaFree(hd->c));
  CUDA_CALL(cudaFree(hd->d));
  CUDA_CALL(cudaFree(hd->k));
  CUDA_CALL(cudaFree(hd->r));
  CUDA_CALL(cudaFree(hd->s));
  CUDA_CALL(cudaFree(hd->w));

  CUDA_CALL(cudaFree(hd->beta));
  CUDA_CALL(cudaFree(hd->epsilon));
  CUDA_CALL(cudaFree(hd->gamma));
  CUDA_CALL(cudaFree(hd->nu));
  CUDA_CALL(cudaFree(hd->omegaSquared));
  CUDA_CALL(cudaFree(hd->rho));
  CUDA_CALL(cudaFree(hd->sigmaSquared));
  CUDA_CALL(cudaFree(hd->tau));
  CUDA_CALL(cudaFree(hd->theta));
  CUDA_CALL(cudaFree(hd->xi));

  CUDA_CALL(cudaFree(hd->betaStart));
  CUDA_CALL(cudaFree(hd->epsilonStart));
  CUDA_CALL(cudaFree(hd->gammaStart));
  CUDA_CALL(cudaFree(hd->nuStart));
  CUDA_CALL(cudaFree(hd->omegaSquaredStart));
  CUDA_CALL(cudaFree(hd->rhoStart));
  CUDA_CALL(cudaFree(hd->sigmaSquaredStart));
  CUDA_CALL(cudaFree(hd->tauStart));
  CUDA_CALL(cudaFree(hd->thetaStart));
  CUDA_CALL(cudaFree(hd->xiStart));

  CUDA_CALL(cudaFree(hd->betaPostMean));
  CUDA_CALL(cudaFree(hd->epsilonPostMean));
  CUDA_CALL(cudaFree(hd->gammaPostMean));
  CUDA_CALL(cudaFree(hd->nuPostMean));
  CUDA_CALL(cudaFree(hd->omegaSquaredPostMean));
  CUDA_CALL(cudaFree(hd->rhoPostMean));
  CUDA_CALL(cudaFree(hd->sigmaSquaredPostMean));
  CUDA_CALL(cudaFree(hd->tauPostMean));
  CUDA_CALL(cudaFree(hd->thetaPostMean));
  CUDA_CALL(cudaFree(hd->xiPostMean));

  CUDA_CALL(cudaFree(hd->betaPostMeanSquare));
  CUDA_CALL(cudaFree(hd->epsilonPostMeanSquare));
  CUDA_CALL(cudaFree(hd->gammaPostMeanSquare));
  CUDA_CALL(cudaFree(hd->nuPostMeanSquare));
  CUDA_CALL(cudaFree(hd->omegaSquaredPostMeanSquare));
  CUDA_CALL(cudaFree(hd->rhoPostMeanSquare));
  CUDA_CALL(cudaFree(hd->sigmaSquaredPostMeanSquare));
  CUDA_CALL(cudaFree(hd->tauPostMeanSquare));
  CUDA_CALL(cudaFree(hd->thetaPostMeanSquare));
  CUDA_CALL(cudaFree(hd->xiPostMeanSquare));

  CUDA_CALL(cudaFree(hd->states));
  CUDA_CALL(cudaFree(hd->aux));
  CUDA_CALL(cudaFree(hd->D));

  free(hd);
}

#endif // FREE_HD_H
