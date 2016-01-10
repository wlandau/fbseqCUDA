#ifndef UTIL_HD2HH_H
#define UTIL_HD2HH_H

void hd2hh(SEXP hh, chain_t *hd, int m){

  int l,
      greturn,
      nreturn,

      G = li(hh, "G")[0],
      Greturn = li(hh, "Greturn")[0],
      GreturnEpsilon = li(hh, "GreturnEpsilon")[0],
      L = li(hh, "L")[0],
      N = li(hh, "N")[0],
      Nreturn = li(hh, "Nreturn")[0],
      NreturnEpsilon = li(hh, "NreturnEpsilon")[0],

      *genes_return = li(hh, "genes_return"),
      *genes_return_epsilon = li(hh, "genes_return_epsilon"),
      *libraries_return = li(hh, "libraries_return"),
      *libraries_return_epsilon = li(hh, "libraries_return_epsilon");

  SEXP parameter_sets_return = le(hh, "parameter_sets_return");

  if(vi(parameter_sets_return, "beta"))
    for(l = 0; l < L; ++l)
      for(greturn = 0; greturn < Greturn; ++greturn)
        CUDA_CALL(cudaMemcpy(lr(hh, "beta") + m*L*Greturn + l*Greturn + greturn,
                             hd->beta + l*G + genes_return[greturn]-1,
                             sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(parameter_sets_return, "epsilon"))
    for(nreturn = 0; nreturn < NreturnEpsilon; ++nreturn)
      for(greturn = 0; greturn < GreturnEpsilon; ++greturn)
        CUDA_CALL(cudaMemcpy(lr(hh, "epsilon") + m*NreturnEpsilon*GreturnEpsilon + nreturn*GreturnEpsilon + greturn,
                             hd->epsilon + (libraries_return_epsilon[nreturn]-1)*G + genes_return_epsilon[greturn]-1,
                             sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(parameter_sets_return, "gamma"))
    for(greturn = 0; greturn < Greturn; ++greturn)
      CUDA_CALL(cudaMemcpy(lr(hh, "gamma") + m*Greturn + greturn,
                           hd->gamma + genes_return[greturn]-1,
                           sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(parameter_sets_return, "nu"))
    CUDA_CALL(cudaMemcpy(lr(hh, "nu") + m, hd->nu, sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(parameter_sets_return, "sigmaSquared"))
    for(l = 0; l < L; ++l)
      CUDA_CALL(cudaMemcpy(lr(hh, "sigmaSquared") + m*L + l, hd->sigmaSquared + l,
                           sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(parameter_sets_return, "tau"))
    CUDA_CALL(cudaMemcpy(lr(hh, "tau") + m, hd->tau, sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(parameter_sets_return, "theta"))
    for(l = 0; l < L; ++l)
      CUDA_CALL(cudaMemcpy(lr(hh, "theta") + m*L + l, hd->theta + l,
                           sizeof(double), cudaMemcpyDeviceToHost));

  if(vi(parameter_sets_return, "xi"))
    for(l = 0; l < L; ++l)
      for(greturn = 0; greturn < Greturn; ++greturn)
        CUDA_CALL(cudaMemcpy(lr(hh, "xi") + m*L*Greturn + l*Greturn + greturn,
                             hd->xi + l*G + genes_return[greturn]-1,
                             sizeof(double), cudaMemcpyDeviceToHost));
}

#endif // UTIL_HD2HH_H
