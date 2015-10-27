#ifndef HH2HD_H
#define HH2HD_H

void hh2hd(SEXP hh, chain_t *hd){
  int N = li(hh, "N")[0],
      L = li(hh, "L")[0],
      G = li(hh, "G")[0];

  CUDA_CALL(cudaMemcpy(hd->counts, li(hh, "counts"), N * G * sizeof(int), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->countSums_g, li(hh, "countSums_g"), G * sizeof(int), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->countSums_n, li(hh, "countSums_n"), N * sizeof(int), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->design, li(hh, "design"), L * N * sizeof(int), cudaMemcpyHostToDevice));
  hd->N = N;
  hd->L = L;
  hd->G = G;
  CUDA_CALL(cudaMemcpy(hd->seeds, li(hh, "seeds"), G * sizeof(int), cudaMemcpyHostToDevice));

  CUDA_CALL(cudaMemcpy(hd->aGamma, lr(hh, "aGamma"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->aRho, lr(hh, "aRho"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->bGamma, lr(hh, "bGamma"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->bRho, lr(hh, "bRho"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->c, lr(hh, "c"), L * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->dGamma, lr(hh, "dGamma"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->dRho, lr(hh, "dRho"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->k, lr(hh, "k"), L * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->r, lr(hh, "r"), L * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->s, lr(hh, "s"), L * sizeof(double), cudaMemcpyHostToDevice));

  CUDA_CALL(cudaMemcpy(hd->beta, lr(hh, "betaStart"), L * G * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->epsilon, lr(hh, "epsilonStart"), N * G * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->gamma, lr(hh, "gammaStart"), G * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->nuGamma, lr(hh, "nuGammaStart"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->nuRho, lr(hh, "nuRhoStart"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->omega, lr(hh, "omegaStart"), L * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->rho, lr(hh, "rhoStart"), N * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->tauGamma, lr(hh, "tauGammaStart"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->tauRho, lr(hh, "tauRhoStart"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->theta, lr(hh, "thetaStart"), L * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->xi, lr(hh, "xiStart"), L * G * sizeof(double), cudaMemcpyHostToDevice));
}

#endif // HH2HD_H
