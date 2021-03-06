#ifndef UTIL_RESET_STARTS_H
#define UTIL_RESET_STARTS_H

void reset_starts(SEXP hh, chain_t *hd){

  int G = li(hh, "G")[0],
      L = li(hh, "L")[0],
      N = li(hh, "N")[0];

  CUDA_CALL(cudaMemcpy(lr(hh, "betaStart"), hd->beta, L * G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "epsilonStart"), hd->epsilon, N * G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "gammaStart"), hd->gamma, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "nuStart"), hd->nu, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "sigmaSquaredStart"), hd->sigmaSquared, L * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "tauStart"), hd->tau, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "thetaStart"), hd->theta, L * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "xiStart"), hd->xi, L * G * sizeof(double), cudaMemcpyDeviceToHost));
}

#endif // UTIL_RESET_STARTS_H
