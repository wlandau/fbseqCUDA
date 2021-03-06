#ifndef STAGE_END_H
#define STAGE_END_H

void end(SEXP hh, chain_t *hd, chain_t *dd){
  estimates_save(hh, hd);
  reset_starts(hh, hd);

  free_hd(hd);
  CUDA_CALL(cudaFree(dd));

  if(li(hh, "verbose")[0])
    Rprintf("Finished MCMC on GPU %d.\n", getDevice());

  cudaDeviceReset();
}

#endif // STAGE_END_H
