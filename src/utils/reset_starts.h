#ifndef RESET_STARTS_H
#define RESET_STARTS_H

void reset_starts(SEXP hh, chain_t *hd){

  int N = li(hh, "N")[0],
      G = li(hh, "G")[0];

  CUDA_CALL(cudaMemcpy(lr(hh, "nuRhoStart"), hd->nuRho, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "nuGamStart"), hd->nuGam, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "tauRhoStart"), hd->tauRho, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "tauGamStart"), hd->tauGam, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "thePhiStart"), hd->thePhi, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "theAlpStart"), hd->theAlp, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "theDelStart"), hd->theDel, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "sigPhiStart"), hd->sigPhi, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "sigAlpStart"), hd->sigAlp, sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "sigDelStart"), hd->sigDel, sizeof(double), cudaMemcpyDeviceToHost));

  CUDA_CALL(cudaMemcpy(lr(hh, "phiStart"), hd->phi, G*sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "alpStart"), hd->alp, G*sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "delStart"), hd->del, G*sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "rhoStart"), hd->rho, N*sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "gamStart"), hd->gam, G*sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "xiPhiStart"), hd->xiPhi, G*sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "xiAlpStart"), hd->xiAlp, G*sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "xiDelStart"), hd->xiDel, G*sizeof(double), cudaMemcpyDeviceToHost));
  CUDA_CALL(cudaMemcpy(lr(hh, "epsStart"), hd->eps, N*G*sizeof(double), cudaMemcpyDeviceToHost));
}

#endif // RESET_STARTS_H
