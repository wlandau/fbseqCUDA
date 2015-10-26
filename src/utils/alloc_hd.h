#ifndef ALLOC_HD_H
#define ALLOC_HD_H

chain_t *alloc_hd(SEXP hh){
  int N = li(hh, "N")[0],
      G = li(hh, "G")[0];

  chain_t *hd = (chain_t *) calloc(1, sizeof(chain_t));

  CUDA_CALL(cudaMalloc((void**) &(hd->counts), N * G * sizeof(int)));
  CUDA_CALL(cudaMalloc((void**) &(hd->group), N * sizeof(int)));

  CUDA_CALL(cudaMalloc((void**) &(hd->sums_n), N * sizeof(int)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sums_g), G * sizeof(int)));

  CUDA_CALL(cudaMalloc((void**) &(hd->seeds), N * G * sizeof(int)));

  CUDA_CALL(cudaMalloc((void**) &(hd->hph), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->lph), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->mph), G * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->dRho), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->dGam), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->aRho), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->aGam), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->bRho), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->bGam), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->cPhi), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->cAlp), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->cDel), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sPhi), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sAlp), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sDel), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->kPhi), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->kAlp), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->kDel), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->rPhi), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->rAlp), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->rDel), sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->nuRho), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nuGam), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauRho), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauGam), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->thePhi), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->theAlp), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->theDel), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigPhi), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigAlp), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigDel), sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->phi), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->alp), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->del), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->rho), N * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->gam), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiPhi), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiAlp), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiDel), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->eps), N * G * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->nuRhoPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nuGamPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauRhoPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauGamPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->thePhiPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->theAlpPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->theDelPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigPhiPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigAlpPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigDelPostMean), sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->phiPostMean), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->alpPostMean), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->delPostMean), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->rhoPostMean), N * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->gamPostMean), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiPhiPostMean), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiAlpPostMean), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiDelPostMean), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->epsPostMean), N * G * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->nuRhoPostMeanSq), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nuGamPostMeanSq), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauRhoPostMeanSq), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauGamPostMeanSq), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->thePhiPostMeanSq), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->theAlpPostMeanSq), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->theDelPostMeanSq), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigPhiPostMeanSq), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigAlpPostMeanSq), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigDelPostMeanSq), sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->phiPostMeanSq), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->alpPostMeanSq), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->delPostMeanSq), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->rhoPostMeanSq), N * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->gamPostMeanSq), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiPhiPostMeanSq), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiAlpPostMeanSq), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiDelPostMeanSq), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->epsPostMeanSq), N * G * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->states), N * G * sizeof(curandState_t)));
  CUDA_CALL(cudaMalloc((void**) &(hd->aux), (G > 10 ? G : 10) * sizeof(double)));

  return hd;
}

#endif // ALLOC_HD_H
