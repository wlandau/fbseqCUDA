#ifndef ESTIMATES_H
#define ESTIMATES_H

__global__ void initialize_estimates_kernel1(chain_t *dd){
  int n;
  dd->nuRhoPostMean[0] = 0.0;
  dd->nuGamPostMean[0] = 0.0;
  dd->tauRhoPostMean[0] = 0.0;
  dd->tauGamPostMean[0] = 0.0;
  dd->thePhiPostMean[0] = 0.0;
  dd->theAlpPostMean[0] = 0.0;
  dd->theDelPostMean[0] = 0.0;
  dd->sigPhiPostMean[0] = 0.0;
  dd->sigAlpPostMean[0] = 0.0;
  dd->sigDelPostMean[0] = 0.0;
  for(n = 0; n < dd->N; ++n)
    dd->rhoPostMean[n] = 0.0;

  dd->nuRhoPostMeanSq[0] = 0.0;
  dd->nuGamPostMeanSq[0] = 0.0;
  dd->tauRhoPostMeanSq[0] = 0.0;
  dd->tauGamPostMeanSq[0] = 0.0;
  dd->thePhiPostMeanSq[0] = 0.0;
  dd->theAlpPostMeanSq[0] = 0.0;
  dd->theDelPostMeanSq[0] = 0.0;
  dd->sigPhiPostMeanSq[0] = 0.0;
  dd->sigAlpPostMeanSq[0] = 0.0;
  dd->sigDelPostMeanSq[0] = 0.0;
  for(n = 0; n < dd->N; ++n)
    dd->rhoPostMeanSq[n] = 0.0;
}

__global__ void initialize_estimates_kernel2(chain_t *dd){
  int id = IDX, n;
  if(id < dd->G){
    dd->hph[id] = 0.0;
    dd->lph[id] = 0.0;
    dd->mph[id] = 0.0;

    dd->phiPostMean[id] = 0.0;
    dd->alpPostMean[id] = 0.0;
    dd->delPostMean[id] = 0.0;
    dd->gamPostMean[id] = 0.0;
    dd->xiPhiPostMean[id] = 0.0;
    dd->xiAlpPostMean[id] = 0.0;
    dd->xiDelPostMean[id] = 0.0;
    for(n = 0; n < dd->N; ++n)
      dd->epsPostMean[I(n, id)] = 0.0;

    dd->phiPostMeanSq[id] = 0.0;
    dd->alpPostMeanSq[id] = 0.0;
    dd->delPostMeanSq[id] = 0.0;
    dd->gamPostMeanSq[id] = 0.0;
    dd->xiPhiPostMeanSq[id] = 0.0;
    dd->xiAlpPostMeanSq[id] = 0.0;
    dd->xiDelPostMeanSq[id] = 0.0;
    for(n = 0; n < dd->N; ++n)
      dd->epsPostMeanSq[I(n, id)] = 0.0;
  }
}

void initialize_estimates(SEXP hh,chain_t *dd){
  initialize_estimates_kernel1<<<1, 1>>>(dd);
  initialize_estimates_kernel2<<<GRID, BLOCK>>>(dd);
}

__global__ void update_estimates_kernel1(chain_t *dd){
  int n;
  dd->nuRhoPostMean[0] += dd->nuRho[0];
  dd->nuGamPostMean[0] += dd->nuGam[0];
  dd->tauRhoPostMean[0] += dd->tauRho[0];
  dd->tauGamPostMean[0] += dd->tauGam[0];
  dd->thePhiPostMean[0] += dd->thePhi[0];
  dd->theAlpPostMean[0] += dd->theAlp[0];
  dd->theDelPostMean[0] += dd->theDel[0];
  dd->sigPhiPostMean[0] += dd->sigPhi[0];
  dd->sigAlpPostMean[0] += dd->sigAlp[0];
  dd->sigDelPostMean[0] += dd->sigDel[0];
  for(n = 0; n < dd->N; ++n)
    dd->rhoPostMean[n] += dd->rho[n];

  dd->nuRhoPostMeanSq[0] += dd->nuRho[0]*dd->nuRho[0];
  dd->nuGamPostMeanSq[0] += dd->nuGam[0]*dd->nuGam[0];
  dd->tauRhoPostMeanSq[0] += dd->tauRho[0]*dd->tauRho[0];
  dd->tauGamPostMeanSq[0] += dd->tauGam[0]*dd->tauGam[0];
  dd->thePhiPostMeanSq[0] += dd->thePhi[0]*dd->thePhi[0];
  dd->theAlpPostMeanSq[0] += dd->theAlp[0]*dd->theAlp[0];
  dd->theDelPostMeanSq[0] += dd->theDel[0]*dd->theDel[0];;
  dd->sigPhiPostMeanSq[0] += dd->sigPhi[0]*dd->sigPhi[0];
  dd->sigAlpPostMeanSq[0] += dd->sigAlp[0]*dd->sigAlp[0];
  dd->sigDelPostMeanSq[0] += dd->sigDel[0]*dd->sigDel[0];
  for(n = 0; n < dd->N; ++n)
    dd->rhoPostMeanSq[n] += dd->rho[n]*dd->rho[n];
}

__global__ void update_estimates_kernel2(chain_t *dd){
  int id = IDX, n;
  if(id < dd->G){
    dd->hph[id] += (dd->alp[id] + dd->del[id]) >  fabs(dd->alp[id] - dd->del[id]);
    dd->lph[id] += (dd->alp[id] + dd->del[id]) < -fabs(dd->alp[id] - dd->del[id]);
    dd->mph[id] += fabs(dd->alp[id] + dd->del[id]) > dd->mphtol;

    dd->phiPostMean[id] += dd->phi[id];
    dd->alpPostMean[id] += dd->alp[id];
    dd->delPostMean[id] += dd->del[id];
    dd->gamPostMean[id] += dd->gam[id];
    dd->xiPhiPostMean[id] += dd->xiPhi[id];
    dd->xiAlpPostMean[id] += dd->xiAlp[id];
    dd->xiDelPostMean[id] += dd->xiDel[id];
    for(n = 0; n < dd->N; ++n)
      dd->epsPostMean[I(n, id)] += dd->eps[I(n, id)];

    dd->phiPostMeanSq[id] += dd->phi[id]*dd->phi[id];
    dd->alpPostMeanSq[id] += dd->alp[id]*dd->alp[id];
    dd->delPostMeanSq[id] += dd->del[id]*dd->del[id];
    dd->gamPostMeanSq[id] += dd->gam[id]*dd->gam[id];
    dd->xiPhiPostMeanSq[id] += dd->xiPhi[id]*dd->xiPhi[id];
    dd->xiAlpPostMeanSq[id] += dd->xiAlp[id]*dd->xiAlp[id];
    dd->xiDelPostMeanSq[id] += dd->xiDel[id]*dd->xiDel[id];
    for(n = 0; n < dd->N; ++n)
      dd->epsPostMeanSq[I(n, id)] += dd->eps[I(n, id)]*dd->eps[I(n, id)];
  }
}

void update_estimates(SEXP hh, chain_t *dd){
  update_estimates_kernel1<<<1, 1>>>(dd);
  update_estimates_kernel2<<<GRID, BLOCK>>>(dd);
}

__global__ void scale_estimates_kernel1(chain_t *dd, double M){
  int n;
  dd->nuRhoPostMean[0] /= M;
  dd->nuGamPostMean[0] /= M;
  dd->tauRhoPostMean[0] /= M;
  dd->tauGamPostMean[0] /= M;
  dd->thePhiPostMean[0] /= M;
  dd->theAlpPostMean[0] /= M;
  dd->theDelPostMean[0] /= M;
  dd->sigPhiPostMean[0] /= M;
  dd->sigAlpPostMean[0] /= M;
  dd->sigDelPostMean[0] /= M;
  for(n = 0; n < dd->N; ++n)
    dd->rhoPostMean[n] /= M;

  dd->nuRhoPostMeanSq[0] /= M;
  dd->nuGamPostMeanSq[0] /= M;
  dd->tauRhoPostMeanSq[0] /= M;
  dd->tauGamPostMeanSq[0] /= M;
  dd->thePhiPostMeanSq[0] /= M;
  dd->theAlpPostMeanSq[0] /= M;
  dd->theDelPostMeanSq[0] /= M;
  dd->sigPhiPostMeanSq[0] /= M;
  dd->sigAlpPostMeanSq[0] /= M;
  dd->sigDelPostMeanSq[0] /= M;
  for(n = 0; n < dd->N; ++n)
    dd->rhoPostMeanSq[n] /= M;
}

__global__ void scale_estimates_kernel2(chain_t *dd, double M){
  int id = IDX, n;
  if(id < dd->G){
    dd->hph[id] /= M;
    dd->lph[id] /= M;
    dd->mph[id] /= M;

    dd->phiPostMean[id] /= M;
    dd->alpPostMean[id] /= M;
    dd->delPostMean[id] /= M;
    dd->gamPostMean[id] /= M;
    dd->xiPhiPostMean[id] /= M;
    dd->xiAlpPostMean[id] /= M;
    dd->xiDelPostMean[id] /= M;
    for(n = 0; n < dd->N; ++n)
      dd->epsPostMean[I(n, id)] /= M;

    dd->phiPostMeanSq[id] /= M;
    dd->alpPostMeanSq[id] /= M;
    dd->delPostMeanSq[id] /= M;
    dd->gamPostMeanSq[id] /= M;
    dd->xiPhiPostMeanSq[id] /= M;
    dd->xiAlpPostMeanSq[id] /= M;
    dd->xiDelPostMeanSq[id] /= M;
    for(n = 0; n < dd->N; ++n)
      dd->epsPostMeanSq[I(n, id)] /= M;
  }
}

void scale_estimates(SEXP hh, chain_t *dd){
  double M = (double) li(hh, "M")[0];
  scale_estimates_kernel1<<<1, 1>>>(dd, M);
  scale_estimates_kernel2<<<GRID, BLOCK>>>(dd, M);
}

void save_estimates(SEXP hh, chain_t *hd){
  int N = (double) li(hh, "N")[0],
      G = (double) li(hh, "G")[0];

  CUDA_CALL(cudaMemcpy(lr(hh, "hph"), hd->hph, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "lph"), hd->lph, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "mph"), hd->mph, G * sizeof(double), cudaMemcpyDeviceToHost));

  CUDA_CALL(cudaMemcpy(lr(hh, "nuRhoPostMean"), hd->nuRhoPostMean, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "nuGamPostMean"), hd->nuGamPostMean, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "tauRhoPostMean"), hd->tauRhoPostMean, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "tauGamPostMean"), hd->tauGamPostMean, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "thePhiPostMean"), hd->thePhiPostMean, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "theAlpPostMean"), hd->theAlpPostMean, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "theDelPostMean"), hd->theDelPostMean, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "sigPhiPostMean"), hd->sigPhiPostMean, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "sigAlpPostMean"), hd->sigAlpPostMean, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "sigDelPostMean"), hd->sigDelPostMean, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "phiPostMean"), hd->phiPostMean, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "alpPostMean"), hd->alpPostMean, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "delPostMean"), hd->delPostMean, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "rhoPostMean"), hd->rhoPostMean, N * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "gamPostMean"), hd->gamPostMean, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "xiPhiPostMean"), hd->xiPhiPostMean, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "xiAlpPostMean"), hd->xiAlpPostMean, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "xiDelPostMean"), hd->xiDelPostMean, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "epsPostMean"), hd->epsPostMean, N * G * sizeof(double), cudaMemcpyDeviceToHost));

  CUDA_CALL(cudaMemcpy(lr(hh, "nuRhoPostMeanSq"), hd->nuRhoPostMeanSq, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "nuGamPostMeanSq"), hd->nuGamPostMeanSq, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "tauRhoPostMeanSq"), hd->tauRhoPostMeanSq, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "tauGamPostMeanSq"), hd->tauGamPostMeanSq, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "thePhiPostMeanSq"), hd->thePhiPostMeanSq, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "theAlpPostMeanSq"), hd->theAlpPostMeanSq, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "theDelPostMeanSq"), hd->theDelPostMeanSq, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "sigPhiPostMeanSq"), hd->sigPhiPostMeanSq, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "sigAlpPostMeanSq"), hd->sigAlpPostMeanSq, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "sigDelPostMeanSq"), hd->sigDelPostMeanSq, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "phiPostMeanSq"), hd->phiPostMeanSq, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "alpPostMeanSq"), hd->alpPostMeanSq, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "delPostMeanSq"), hd->delPostMeanSq, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "rhoPostMeanSq"), hd->rhoPostMeanSq, N * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "gamPostMeanSq"), hd->gamPostMeanSq, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "xiPhiPostMeanSq"), hd->xiPhiPostMeanSq, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "xiAlpPostMeanSq"), hd->xiAlpPostMeanSq, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "xiDelPostMeanSq"), hd->xiDelPostMeanSq, G * sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "epsPostMeanSq"), hd->epsPostMeanSq, N * G * sizeof(double), cudaMemcpyDeviceToHost));
}

void finish_estimates(SEXP hh, chain_t *hd, chain_t *dd){
  scale_estimates(hh, dd);
  save_estimates(hh, hd);
}

#endif // ESTIMATES_H
