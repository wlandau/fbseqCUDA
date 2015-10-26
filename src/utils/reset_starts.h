#ifndef RESET_STARTS_H
#define RESET_STARTS_H

void reset_starts(SEXP hh, chain_t *hd){

  int N = li(hh, "N")[0],
      L = li(hh, "L")[0],
      G = li(hh, "G")[0];

  CUDA_CALL(cudaMemcpy(lr(hh, "betaStart"), hd->beta, L * G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "epsilonStart"), hd->epsilon, N * G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "gammaStart"), hd->gamma, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "nuGammaStart"), hd->nuGamma, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "nuRhoStart"), hd->nuRho, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "omegaStart"), hd->omega, L * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "rhoStart"), hd->rho, N * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "tauGammaStart"), hd->tauGamma, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "tauRhoStart"), hd->tauRho, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "thetaStart"), hd->theta, L * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "xiStart"), hd->xi, L * G * sizeof(double), cudaMemcpyDeviceToHost));
}

#endif // RESET_STARTS_H
