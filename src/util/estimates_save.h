#ifndef UTIL_ESTIMATES_SAVE_H
#define UTIL_ESTIMATES_SAVE_H

void estimates_save(SEXP hh, chain_t *hd){
  int G = (double) li(hh, "G")[0],
      L = (double) li(hh, "L")[0],
      N = (double) li(hh, "N")[0],
      P = (double) li(hh, "P")[0];

  CUDA_CALL(cudaMemcpy(lr(hh, "probs"), hd->probs, P * G * sizeof(double), cudaMemcpyDeviceToHost));

  CUDA_CALL(cudaMemcpy(lr(hh, "loglikPostMean"), hd->loglikPostMean, sizeof(double), cudaMemcpyDeviceToHost));
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

  CUDA_CALL(cudaMemcpy(lr(hh, "betaTune"), hd->betaTune, L * G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "epsilonTune"), hd->epsilonTune, N * G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "gammaTune"), hd->gammaTune, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "nuTune"), hd->nuTune, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "sigmaSquaredTune"), hd->sigmaSquaredTune, L * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "tauTune"), hd->tauTune, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "thetaTune"), hd->thetaTune, L * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "xiTune"), hd->xiTune, L * G * sizeof(double), cudaMemcpyDeviceToHost));
}

#endif // UTIL_ESTIMATES_SAVE_H
