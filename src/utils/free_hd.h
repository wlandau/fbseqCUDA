#ifndef FREE_HD_H
#define FREE_HD_H

void free_hd(chain_t *hd){

  CUDA_CALL(cudaFree(hd->counts));
  CUDA_CALL(cudaFree(hd->group));

  CUDA_CALL(cudaFree(hd->sums_n));
  CUDA_CALL(cudaFree(hd->sums_g));

  CUDA_CALL(cudaFree(hd->seeds));

  CUDA_CALL(cudaFree(hd->hph));
  CUDA_CALL(cudaFree(hd->lph));
  CUDA_CALL(cudaFree(hd->mph));

  CUDA_CALL(cudaFree(hd->dRho));
  CUDA_CALL(cudaFree(hd->dGam));
  CUDA_CALL(cudaFree(hd->aRho));
  CUDA_CALL(cudaFree(hd->aGam));
  CUDA_CALL(cudaFree(hd->bRho));
  CUDA_CALL(cudaFree(hd->bGam));
  CUDA_CALL(cudaFree(hd->cPhi));
  CUDA_CALL(cudaFree(hd->cAlp));
  CUDA_CALL(cudaFree(hd->cDel));
  CUDA_CALL(cudaFree(hd->sPhi));
  CUDA_CALL(cudaFree(hd->sAlp));
  CUDA_CALL(cudaFree(hd->sDel));
  CUDA_CALL(cudaFree(hd->kPhi));
  CUDA_CALL(cudaFree(hd->kAlp));
  CUDA_CALL(cudaFree(hd->kDel));
  CUDA_CALL(cudaFree(hd->rPhi));
  CUDA_CALL(cudaFree(hd->rAlp));
  CUDA_CALL(cudaFree(hd->rDel));

  CUDA_CALL(cudaFree(hd->nuRho));
  CUDA_CALL(cudaFree(hd->nuGam));
  CUDA_CALL(cudaFree(hd->tauRho));
  CUDA_CALL(cudaFree(hd->tauGam));
  CUDA_CALL(cudaFree(hd->thePhi));
  CUDA_CALL(cudaFree(hd->theAlp));
  CUDA_CALL(cudaFree(hd->theDel));
  CUDA_CALL(cudaFree(hd->sigPhi));
  CUDA_CALL(cudaFree(hd->sigAlp));
  CUDA_CALL(cudaFree(hd->sigDel));

  CUDA_CALL(cudaFree(hd->phi));
  CUDA_CALL(cudaFree(hd->alp));
  CUDA_CALL(cudaFree(hd->del));
  CUDA_CALL(cudaFree(hd->rho));
  CUDA_CALL(cudaFree(hd->gam));
  CUDA_CALL(cudaFree(hd->xiPhi));
  CUDA_CALL(cudaFree(hd->xiAlp));
  CUDA_CALL(cudaFree(hd->xiDel));
  CUDA_CALL(cudaFree(hd->eps));

  CUDA_CALL(cudaFree(hd->nuRhoPostMean));
  CUDA_CALL(cudaFree(hd->nuGamPostMean));
  CUDA_CALL(cudaFree(hd->tauRhoPostMean));
  CUDA_CALL(cudaFree(hd->tauGamPostMean));
  CUDA_CALL(cudaFree(hd->thePhiPostMean));
  CUDA_CALL(cudaFree(hd->theAlpPostMean));
  CUDA_CALL(cudaFree(hd->theDelPostMean));
  CUDA_CALL(cudaFree(hd->sigPhiPostMean));
  CUDA_CALL(cudaFree(hd->sigAlpPostMean));
  CUDA_CALL(cudaFree(hd->sigDelPostMean));
  CUDA_CALL(cudaFree(hd->phiPostMean));
  CUDA_CALL(cudaFree(hd->alpPostMean));
  CUDA_CALL(cudaFree(hd->delPostMean));
  CUDA_CALL(cudaFree(hd->rhoPostMean));
  CUDA_CALL(cudaFree(hd->gamPostMean));
  CUDA_CALL(cudaFree(hd->xiPhiPostMean));
  CUDA_CALL(cudaFree(hd->xiAlpPostMean));
  CUDA_CALL(cudaFree(hd->xiDelPostMean));
  CUDA_CALL(cudaFree(hd->epsPostMean));

  CUDA_CALL(cudaFree(hd->nuRhoPostMeanSq));
  CUDA_CALL(cudaFree(hd->nuGamPostMeanSq));
  CUDA_CALL(cudaFree(hd->tauRhoPostMeanSq));
  CUDA_CALL(cudaFree(hd->tauGamPostMeanSq));
  CUDA_CALL(cudaFree(hd->thePhiPostMeanSq));
  CUDA_CALL(cudaFree(hd->theAlpPostMeanSq));
  CUDA_CALL(cudaFree(hd->theDelPostMeanSq));
  CUDA_CALL(cudaFree(hd->sigPhiPostMeanSq));
  CUDA_CALL(cudaFree(hd->sigAlpPostMeanSq));
  CUDA_CALL(cudaFree(hd->sigDelPostMeanSq));
  CUDA_CALL(cudaFree(hd->phiPostMeanSq));
  CUDA_CALL(cudaFree(hd->alpPostMeanSq));
  CUDA_CALL(cudaFree(hd->delPostMeanSq));
  CUDA_CALL(cudaFree(hd->rhoPostMeanSq));
  CUDA_CALL(cudaFree(hd->gamPostMeanSq));
  CUDA_CALL(cudaFree(hd->xiPhiPostMeanSq));
  CUDA_CALL(cudaFree(hd->xiAlpPostMeanSq));
  CUDA_CALL(cudaFree(hd->xiDelPostMeanSq));
  CUDA_CALL(cudaFree(hd->epsPostMeanSq));

  CUDA_CALL(cudaFree(hd->states));
  CUDA_CALL(cudaFree(hd->aux));

  free(hd);
}

#endif // FREE_HD_H
