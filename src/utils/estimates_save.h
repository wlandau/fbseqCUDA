#ifndef ESTIMATES_SAVE_H
#define ESTIMATES_SAVE_H

void estimates_save(SEXP hh, chain_t *hd){
  int G = (double) li(hh, "G")[0],
      L = (double) li(hh, "L")[0],
      N = (double) li(hh, "N")[0],
      P = (double) li(hh, "P")[0];

  CUDA_CALL(cudaMemcpy(lr(hh, "probs"), hd->probs, P * G * sizeof(double), cudaMemcpyDeviceToHost));

  CUDA_CALL(cudaMemcpy(lr(hh, "betaPostMean"), hd->betaPostMean, L * G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "epsilonPostMean"), hd->epsilonPostMean, N * G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "gammaPostMean"), hd->gammaPostMean, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "nuPostMean"), hd->nuPostMean, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "sigmaSquaredPostMean"), hd->sigmaSquaredPostMean, L * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "tauPostMean"), hd->tauPostMean, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "thetaPostMean"), hd->thetaPostMean, L * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "xiPostMean"), hd->xiPostMean, L * G * sizeof(double), cudaMemcpyDeviceToHost));

  CUDA_CALL(cudaMemcpy(lr(hh, "betaPostMeanSquare"), hd->betaPostMeanSquare, L * G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "epsilonPostMeanSquare"), hd->epsilonPostMeanSquare, N * G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "gammaPostMeanSquare"), hd->gammaPostMeanSquare, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "nuPostMeanSquare"), hd->nuPostMeanSquare, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "sigmaSquaredPostMeanSquare"), hd->sigmaSquaredPostMeanSquare, L * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "tauPostMeanSquare"), hd->tauPostMeanSquare, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "thetaPostMeanSquare"), hd->thetaPostMeanSquare, L * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "xiPostMeanSquare"), hd->xiPostMeanSquare, L * G * sizeof(double), cudaMemcpyDeviceToHost));

  CUDA_CALL(cudaMemcpy(lr(hh, "betaWidth"), hd->betaWidth, L * G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "epsilonWidth"), hd->epsilonWidth, N * G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "gammaWidth"), hd->gammaWidth, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "nuWidth"), hd->nuWidth, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "sigmaSquaredWidth"), hd->sigmaSquaredWidth, L * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "tauWidth"), hd->tauWidth, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "thetaWidth"), hd->thetaWidth, L * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "xiWidth"), hd->xiWidth, L * G * sizeof(double), cudaMemcpyDeviceToHost));
}

#endif // ESTIMATES_SAVE_H
