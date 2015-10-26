#ifndef HD2HH_H
#define HD2HH_H

void hd2hh(SEXP hh, chain_t *hd, int m){

  int nreturn,
      greturn,
      N = li(hh, "N")[0],
      G = li(hh, "G")[0],
      Nreturn = li(hh, "Nreturn")[0],
      Greturn = li(hh, "Greturn")[0],
      NreturnEps = li(hh, "NreturnEps")[0],
      GreturnEps = li(hh, "GreturnEps")[0],
      *samples_return = li(hh, "samples_return"),
      *features_return = li(hh, "features_return"),
      *samples_return_eps = li(hh, "samples_return_eps"),
      *features_return_eps = li(hh, "features_return_eps");

  SEXP returns = le(hh, "returns");

  if(vi(returns, "nuRho"))
    CUDA_CALL(cudaMemcpy(lr(hh, "nuRho") + m, hd->nuRho, sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(returns, "nuGam"))
    CUDA_CALL(cudaMemcpy(lr(hh, "nuGam") + m, hd->nuGam, sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(returns, "tauRho"))
    CUDA_CALL(cudaMemcpy(lr(hh, "tauRho") + m, hd->tauRho, sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(returns, "tauGam"))
    CUDA_CALL(cudaMemcpy(lr(hh, "tauGam") + m, hd->tauGam, sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(returns, "thePhi"))
    CUDA_CALL(cudaMemcpy(lr(hh, "thePhi") + m, hd->thePhi, sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(returns, "theAlp"))
    CUDA_CALL(cudaMemcpy(lr(hh, "theAlp") + m, hd->theAlp, sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(returns, "theDel"))
    CUDA_CALL(cudaMemcpy(lr(hh, "theDel") + m, hd->theDel, sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(returns, "sigPhi"))
    CUDA_CALL(cudaMemcpy(lr(hh, "sigPhi") + m, hd->sigPhi, sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(returns, "sigAlp"))
    CUDA_CALL(cudaMemcpy(lr(hh, "sigAlp") + m, hd->sigAlp, sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(returns, "sigDel"))
    CUDA_CALL(cudaMemcpy(lr(hh, "sigDel") + m, hd->sigDel, sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(returns, "rho"))
    for(nreturn = 0; nreturn < Nreturn; ++nreturn)
      CUDA_CALL(cudaMemcpy(lr(hh, "rho") + m*Nreturn + nreturn,
                           hd->rho + samples_return[nreturn]-1,
                           sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(returns, "phi"))
    for(greturn = 0; greturn < Greturn; ++greturn)
      CUDA_CALL(cudaMemcpy(lr(hh, "phi") + m*Greturn + greturn,
                           hd->phi + features_return[greturn]-1,
                           sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(returns, "alp"))
    for(greturn = 0; greturn < Greturn; ++greturn)
      CUDA_CALL(cudaMemcpy(lr(hh, "alp") + m*Greturn + greturn,
                           hd->alp + features_return[greturn]-1,
                           sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(returns, "del"))
    for(greturn = 0; greturn < Greturn; ++greturn)
      CUDA_CALL(cudaMemcpy(lr(hh, "del") + m*Greturn + greturn,
                           hd->del + features_return[greturn]-1,
                           sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(returns, "gam"))
    for(greturn = 0; greturn < Greturn; ++greturn)
      CUDA_CALL(cudaMemcpy(lr(hh, "gam") + m*Greturn + greturn,
                           hd->gam + features_return[greturn]-1,
                           sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(returns, "xiPhi"))
    for(greturn = 0; greturn < Greturn; ++greturn)
      CUDA_CALL(cudaMemcpy(lr(hh, "xiPhi") + m*Greturn + greturn,
                           hd->xiPhi + features_return[greturn]-1,
                           sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(returns, "xiAlp"))
    for(greturn = 0; greturn < Greturn; ++greturn)
      CUDA_CALL(cudaMemcpy(lr(hh, "xiAlp") + m*Greturn + greturn,
                           hd->xiAlp + features_return[greturn]-1,
                           sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(returns, "xiDel"))
    for(greturn = 0; greturn < Greturn; ++greturn)
      CUDA_CALL(cudaMemcpy(lr(hh, "xiDel") + m*Greturn + greturn,
                           hd->xiDel + features_return[greturn]-1,
                           sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(returns, "eps"))
    for(nreturn = 0; nreturn < NreturnEps; ++nreturn)
      for(greturn = 0; greturn < GreturnEps; ++greturn)
        CUDA_CALL(cudaMemcpy(lr(hh, "eps") + m*NreturnEps*GreturnEps + nreturn*GreturnEps + greturn,
                             hd->eps + (samples_return_eps[nreturn]-1)*G + features_return_eps[greturn]-1,
                             sizeof(double), cudaMemcpyDeviceToHost));
}

#endif // HD2HH_H
