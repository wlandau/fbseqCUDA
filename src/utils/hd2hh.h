#ifndef HD2HH_H
#define HD2HH_H

void hd2hh(SEXP hh, chain_t *hd, int m){

  int l,
      greturn,
      nreturn,
      G = li(hh, "G")[0],
      L = li(hh, "L")[0],
      N = li(hh, "N")[0],
      Greturn = li(hh, "Greturn")[0],
      Nreturn = li(hh, "Nreturn")[0],
      GreturnEps = li(hh, "GreturnEps")[0],
      NreturnEps = li(hh, "NreturnEps")[0],
      *genes_return = li(hh, "genes_return"),
      *libraries_return = li(hh, "libraries_return"),
      *genes_return_eps = li(hh, "genes_return_eps"),
      *libraries_return_eps = li(hh, "libraries_return_eps");

  SEXP parameter_sets_return = le(hh, "parameter_sets_return");

  if(vi(parameter_sets_return, "beta"))
    for(l = 0; l < L; ++l)
      for(greturn = 0; greturn < Greturn; ++greturn)
        CUDA_CALL(cudaMemcpy(lr(hh, "beta") + m*L*Greturn + l*Greturn + greturn,
                             hd->beta + (libraries_return[l]-1)*G + genes_return[greturn]-1,
                             sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(parameter_sets_return, "epsilon"))
    for(nreturn = 0; nreturn < NreturnEps; ++nreturn)
      for(greturn = 0; greturn < GreturnEps; ++greturn)
        CUDA_CALL(cudaMemcpy(lr(hh, "epsilon") + m*NreturnEps*GreturnEps + nreturn*GreturnEps + greturn,
                             hd->epsilon + (libraries_return_eps[nreturn]-1)*G + genes_return_eps[greturn]-1,
                             sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(parameter_sets_return, "gamma"))
    for(greturn = 0; greturn < Greturn; ++greturn)
      CUDA_CALL(cudaMemcpy(lr(hh, "gamma") + m*Greturn + greturn,
                           hd->gamma + genes_return[greturn]-1,
                           sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(parameter_sets_return, "nuGamma"))
    CUDA_CALL(cudaMemcpy(lr(hh, "nuGamma") + m, hd->nuGamma, sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(parameter_sets_return, "nuRho"))
    CUDA_CALL(cudaMemcpy(lr(hh, "nuRho") + m, hd->nuRho, sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(parameter_sets_return, "omega"))
    for(l = 0; l < L; ++l)
      CUDA_CALL(cudaMemcpy(lr(hh, "omega") + m*L + l, hd->omega + l,
                           sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(parameter_sets_return, "rho"))
    for(nreturn = 0; nreturn < Nreturn; ++nreturn)
      CUDA_CALL(cudaMemcpy(lr(hh, "rho") + m*Nreturn + nreturn,
                           hd->rho + libraries_return[nreturn]-1,
                           sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(parameter_sets_return, "tauGamma"))
    CUDA_CALL(cudaMemcpy(lr(hh, "tauGamma") + m, hd->tauGamma, sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(parameter_sets_return, "tauRho"))
    CUDA_CALL(cudaMemcpy(lr(hh, "tauRho") + m, hd->tauRho, sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(parameter_sets_return, "theta"))
    for(l = 0; l < L; ++l)
      CUDA_CALL(cudaMemcpy(lr(hh, "theta") + m*L + l, hd->theta + l,
                           sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(parameter_sets_return, "xi"))
    for(l = 0; l < L; ++l)
      for(greturn = 0; greturn < Greturn; ++greturn)
        CUDA_CALL(cudaMemcpy(lr(hh, "xi") + m*L*Greturn + l*Greturn + greturn,
                             hd->xi + (libraries_return[l]-1)*G + genes_return[greturn]-1,
                             sizeof(double), cudaMemcpyDeviceToHost));
}

#endif // HD2HH_H
