#ifndef HH2HD_H
#define HH2HD_H

void hh2hd(SEXP hh, chain_t *hd){
  int N = li(hh, "N")[0],
      G = li(hh, "G")[0];

  CUDA_CALL(cudaMemcpy(hd->counts, li(hh, "counts"), N * G * sizeof(int), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->group, li(hh, "group"), N * sizeof(int), cudaMemcpyHostToDevice));

  CUDA_CALL(cudaMemcpy(hd->sums_n, li(hh, "sums_n"), N * sizeof(int), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->sums_g, li(hh, "sums_g"), G * sizeof(int), cudaMemcpyHostToDevice));

  hd->N = N;
  hd->G = G;

  hd->mphtol = lr(hh, "mphtol")[0];
  CUDA_CALL(cudaMemcpy(hd->seeds, li(hh, "seeds"), G * sizeof(int), cudaMemcpyHostToDevice));

  CUDA_CALL(cudaMemcpy(hd->dRho, lr(hh, "dRho"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->dGam, lr(hh, "dGam"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->aRho, lr(hh, "aRho"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->aGam, lr(hh, "aGam"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->bRho, lr(hh, "bRho"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->bGam, lr(hh, "bGam"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->cPhi, lr(hh, "cPhi"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->cAlp, lr(hh, "cAlp"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->cDel, lr(hh, "cDel"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->sPhi, lr(hh, "sPhi"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->sAlp, lr(hh, "sAlp"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->sDel, lr(hh, "sDel"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->kPhi, lr(hh, "kPhi"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->kAlp, lr(hh, "kAlp"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->kDel, lr(hh, "kDel"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->rPhi, lr(hh, "rPhi"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->rAlp, lr(hh, "rAlp"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->rDel, lr(hh, "rDel"), sizeof(double), cudaMemcpyHostToDevice));

  CUDA_CALL(cudaMemcpy(hd->nuRho, lr(hh, "nuRhoStart"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->nuGam, lr(hh, "nuGamStart"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->tauRho, lr(hh, "tauRhoStart"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->tauGam, lr(hh, "tauGamStart"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->thePhi, lr(hh, "thePhiStart"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->theAlp, lr(hh, "theAlpStart"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->theDel, lr(hh, "theDelStart"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->sigPhi, lr(hh, "sigPhiStart"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->sigAlp, lr(hh, "sigAlpStart"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->sigDel, lr(hh, "sigDelStart"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->rho, lr(hh, "rhoStart"), N*sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->phi, lr(hh, "phiStart"), G*sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->alp, lr(hh, "alpStart"), G*sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->del, lr(hh, "delStart"), G*sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->gam, lr(hh, "gamStart"), G*sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->xiPhi, lr(hh, "xiPhiStart"), G*sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->xiAlp, lr(hh, "xiAlpStart"), G*sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->xiDel, lr(hh, "xiDelStart"), G*sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->eps, lr(hh, "epsStart"), N*G*sizeof(double), cudaMemcpyHostToDevice));
}

#endif // HH2HD_H
