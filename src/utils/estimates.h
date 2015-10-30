#ifndef ESTIMATES_H
#define ESTIMATES_H

__global__ void initialize_estimates_kernel1(chain_t *dd){
  int l, n;

  dd->nuGammaPostMean[0] = 0.0;
  dd->nuRhoPostMean[0] = 0.0;
  dd->omegaSquaredPostMean[0] = 0.0;
  dd->tauGammaPostMean[0] = 0.0;
  dd->tauRhoPostMean[0] = 0.0;

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMean[l] = 0.0;
    dd->thetaPostMean[l] = 0.0;
  }

  for(n = 0; n < dd->N; ++n){
    dd->psiPostMean[n] = 0.0;
    dd->rhoPostMean[n] = 0.0;
  }

  dd->nuGammaPostMeanSquare[0] = 0.0;
  dd->nuRhoPostMeanSquare[0] = 0.0;
  dd->omegaSquaredPostMeanSquare[0] = 0.0;
  dd->tauGammaPostMeanSquare[0] = 0.0;
  dd->tauRhoPostMeanSquare[0] = 0.0;

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMeanSquare[l] = 0.0;
    dd->thetaPostMeanSquare[l] = 0.0;
  }

  for(n = 0; n < dd->N; ++n){
    dd->psiPostMeanSquare[n] = 0.0;
    dd->rhoPostMeanSquare[n] = 0.0;
  }
}

__global__ void initialize_estimates_kernel2(chain_t *dd){
  int id = IDX, l, n;
  if(id < dd->G){
    dd->gammaPostMean[id] = 0.0;
    for(l = 0; l < dd->L; ++l){
      dd->betaPostMean[I(l, id)] = 0.0;
      dd->xiPostMean[I(l, id)] = 0.0;
    }
    for(n = 0; n < dd->N; ++n)
      dd->epsilonPostMean[I(n, id)] = 0.0;

    dd->gammaPostMeanSquare[id] = 0.0;
    for(l = 0; l < dd->L; ++l){
      dd->betaPostMeanSquare[I(l, id)] = 0.0;
      dd->xiPostMeanSquare[I(l, id)] = 0.0;
    }
    for(n = 0; n < dd->N; ++n)
      dd->epsilonPostMeanSquare[I(n, id)] = 0.0;
  }
}

void initialize_estimates(SEXP hh,chain_t *dd){
  initialize_estimates_kernel1<<<1, 1>>>(dd);
  initialize_estimates_kernel2<<<GRID, BLOCK>>>(dd);
}

__global__ void update_estimates_kernel1(chain_t *dd){
  int l, n;

  dd->nuGammaPostMean[0] += dd->nuGamma[0];
  dd->nuRhoPostMean[0] += dd->nuRho[0];
  dd->omegaSquaredPostMean[0] += dd->omegaSquared[0];
  dd->tauGammaPostMean[0] += dd->tauGamma[0];
  dd->tauRhoPostMean[0] += dd->tauRho[0];

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMean[l] += dd->sigmaSquared[l];
    dd->thetaPostMean[l] += dd->theta[l];
  }

  for(n = 0; n < dd->N; ++n){
    dd->psiPostMean[n] += dd->psi[n];
    dd->rhoPostMean[n] += dd->rho[n];
  }

  dd->nuGammaPostMeanSquare[0] += dd->nuGamma[0]*dd->nuGamma[0];
  dd->nuRhoPostMeanSquare[0] += dd->nuRho[0]*dd->nuRho[0];
  dd->omegaSquaredPostMeanSquare[0] += dd->omegaSquared[0]*dd->omegaSquared[0];
  dd->tauGammaPostMeanSquare[0] += dd->tauGamma[0]*dd->tauGamma[0];
  dd->tauRhoPostMeanSquare[0] += dd->tauRho[0]*dd->tauRho[0];

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMeanSquare[l] += dd->sigmaSquared[l]*dd->sigmaSquared[l];
    dd->thetaPostMeanSquare[l] += dd->theta[l]*dd->theta[l];
  }

  for(n = 0; n < dd->N; ++n){
    dd->psiPostMeanSquare[n] += dd->psi[n]*dd->psi[n];
    dd->rhoPostMeanSquare[n] += dd->rho[n]*dd->rho[n];
  }
}

__global__ void update_estimates_kernel2(chain_t *dd){
  int id = IDX, l, n;
  if(id < dd->G){
    dd->gammaPostMean[id] += dd->gamma[id];
    for(l = 0; l < dd->L; ++l){
      dd->betaPostMean[I(l, id)] += dd->beta[I(l, id)];
      dd->xiPostMean[I(l, id)] += dd->xi[I(l, id)];
    }
    for(n = 0; n < dd->N; ++n)
      dd->epsilonPostMean[I(n, id)] += dd->epsilon[I(n, id)];

    dd->gammaPostMeanSquare[id] += dd->gamma[id]*dd->gamma[id];
    for(l = 0; l < dd->L; ++l){
      dd->betaPostMeanSquare[I(l, id)] += dd->beta[I(l, id)]*dd->beta[I(l, id)];
      dd->xiPostMeanSquare[I(l, id)] += dd->xi[I(l, id)]*dd->xi[I(l, id)];
    }
    for(n = 0; n < dd->N; ++n)
      dd->epsilonPostMeanSquare[I(n, id)] += dd->epsilon[I(n, id)]*dd->epsilon[I(n, id)];
  }
}

void update_estimates(SEXP hh, chain_t *dd){
  update_estimates_kernel1<<<1, 1>>>(dd);
  update_estimates_kernel2<<<GRID, BLOCK>>>(dd);
}

__global__ void scale_estimates_kernel1(chain_t *dd, double iterations){
  int l, n;

  dd->nuGammaPostMean[0]/= iterations;
  dd->nuRhoPostMean[0]/= iterations;
  dd->omegaSquaredPostMean[0]/= iterations;
  dd->tauGammaPostMean[0]/= iterations;
  dd->tauRhoPostMean[0]/= iterations;

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMean[l]/= iterations;
    dd->thetaPostMean[l]/= iterations;
  }

  for(n = 0; n < dd->N; ++n){
    dd->psiPostMean[n]/= iterations;
    dd->rhoPostMean[n]/= iterations;
  }

  dd->nuGammaPostMeanSquare[0]/= iterations;
  dd->nuRhoPostMeanSquare[0]/= iterations;
  dd->omegaSquaredPostMeanSquare[0]/= iterations;
  dd->tauGammaPostMeanSquare[0]/= iterations;
  dd->tauRhoPostMeanSquare[0]/= iterations;

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMeanSquare[l]/= iterations;
    dd->thetaPostMeanSquare[l]/= iterations;
  }

  for(n = 0; n < dd->N; ++n){
    dd->psiPostMeanSquare[n]/= iterations;
    dd->rhoPostMeanSquare[n]/= iterations;
  }
}

__global__ void scale_estimates_kernel2(chain_t *dd, double iterations){
  int id = IDX, l, n;
  if(id < dd->G){
    dd->gammaPostMean[id]/= iterations;
    for(l = 0; l < dd->L; ++l){
      dd->betaPostMean[I(l, id)]/= iterations;
      dd->xiPostMean[I(l, id)]/= iterations;
    }
    for(n = 0; n < dd->N; ++n)
      dd->epsilonPostMean[I(n, id)]/= iterations;

    dd->gammaPostMeanSquare[id]/= iterations;
    for(l = 0; l < dd->L; ++l){
      dd->betaPostMeanSquare[I(l, id)]/= iterations;
      dd->xiPostMeanSquare[I(l, id)]/= iterations;
    }
    for(n = 0; n < dd->N; ++n)
      dd->epsilonPostMeanSquare[I(n, id)]/= iterations;
  }
}

void scale_estimates(SEXP hh, chain_t *dd){
  double iterations = (double) li(hh, "iterations")[0];
  scale_estimates_kernel1<<<1, 1>>>(dd, iterations);
  scale_estimates_kernel2<<<GRID, BLOCK>>>(dd, iterations);
}

void save_estimates(SEXP hh, chain_t *hd){
  int N = (double) li(hh, "N")[0],
      L = (double) li(hh, "L")[0],
      G = (double) li(hh, "G")[0];

  CUDA_CALL(cudaMemcpy(lr(hh, "betaPostMean"), hd->betaPostMean, L * G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "epsilonPostMean"), hd->epsilonPostMean, N * G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "gammaPostMean"), hd->gammaPostMean, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "nuGammaPostMean"), hd->nuGammaPostMean, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "nuRhoPostMean"), hd->nuRhoPostMean, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "omegaSquaredPostMean"), hd->omegaSquaredPostMean, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "psiPostMean"), hd->psiPostMean, N * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "rhoPostMean"), hd->rhoPostMean, N * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "sigmaSquaredPostMean"), hd->sigmaSquaredPostMean, L * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "tauGammaPostMean"), hd->tauGammaPostMean, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "tauRhoPostMean"), hd->tauRhoPostMean, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "thetaPostMean"), hd->thetaPostMean, L * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "xiPostMean"), hd->xiPostMean, L * G * sizeof(double), cudaMemcpyDeviceToHost));

  CUDA_CALL(cudaMemcpy(lr(hh, "betaPostMeanSquare"), hd->betaPostMeanSquare, L * G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "epsilonPostMeanSquare"), hd->epsilonPostMeanSquare, N * G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "gammaPostMeanSquare"), hd->gammaPostMeanSquare, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "nuGammaPostMeanSquare"), hd->nuGammaPostMeanSquare, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "nuRhoPostMeanSquare"), hd->nuRhoPostMeanSquare, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "omegaSquaredPostMeanSquare"), hd->omegaSquaredPostMeanSquare, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "psiPostMeanSquare"), hd->psiPostMeanSquare, N * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "rhoPostMeanSquare"), hd->rhoPostMeanSquare, N * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "sigmaSquaredPostMeanSquare"), hd->sigmaSquaredPostMeanSquare, L * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "tauGammaPostMeanSquare"), hd->tauGammaPostMeanSquare, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "tauRhoPostMeanSquare"), hd->tauRhoPostMeanSquare, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "thetaPostMeanSquare"), hd->thetaPostMeanSquare, L * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "xiPostMeanSquare"), hd->xiPostMeanSquare, L * G * sizeof(double), cudaMemcpyDeviceToHost));
}

void finish_estimates(SEXP hh, chain_t *hd, chain_t *dd){
  scale_estimates(hh, dd);
  save_estimates(hh, hd);
}

#endif // ESTIMATES_H
