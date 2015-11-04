#ifndef HH2HD_H
#define HH2HD_H

void hh2hd(SEXP hh, chain_t *hd){
  int C = li(hh, "C")[0],
      G = li(hh, "G")[0],
      L = li(hh, "L")[0],
      N = li(hh, "N")[0],
      P = li(hh, "P")[0];

  hd->C = C;
  hd->G = G;
  hd->L = L;
  hd->N = N;
  hd->P = P;

  CUDA_CALL(cudaMemcpy(hd->bounds, lr(hh, "bounds"), C * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->contrasts, lr(hh, "contrasts"), C * L * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->counts, li(hh, "counts"), N * G * sizeof(int), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->design, lr(hh, "design"), L * N * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->propositions, lr(hh, "propositions"), P * C * sizeof(double), cudaMemcpyHostToDevice));

  CUDA_CALL(cudaMemcpy(hd->countSums_g, li(hh, "countSums_g"), G * sizeof(int), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->countSums_n, li(hh, "countSums_n"), N * sizeof(int), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->designUnique, lr(hh, "designUnique"), L * N * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->designUniqueN, li(hh, "designUniqueN"), L * sizeof(int), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->probs, li(hh, "probs"), P * G * sizeof(int), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->seeds, li(hh, "seeds"), N * G * sizeof(int), cudaMemcpyHostToDevice));

  CUDA_CALL(cudaMemcpy(hd->a, lr(hh, "a"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->b, lr(hh, "b"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->c, lr(hh, "c"), L * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->d, lr(hh, "d"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->k, lr(hh, "k"), L * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->r, lr(hh, "r"), L * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->s, lr(hh, "s"), L * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->w, lr(hh, "w"), sizeof(double), cudaMemcpyHostToDevice));

  CUDA_CALL(cudaMemcpy(hd->beta, lr(hh, "betaStart"), L * G * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->epsilon, lr(hh, "epsilonStart"), N * G * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->gamma, lr(hh, "gammaStart"), G * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->nu, lr(hh, "nuStart"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->omegaSquared, lr(hh, "omegaSquaredStart"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->rho, lr(hh, "rhoStart"), N * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->sigmaSquared, lr(hh, "sigmaSquaredStart"), L * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->tau, lr(hh, "tauStart"), sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->theta, lr(hh, "thetaStart"), L * sizeof(double), cudaMemcpyHostToDevice));
  CUDA_CALL(cudaMemcpy(hd->xi, lr(hh, "xiStart"), L * G * sizeof(double), cudaMemcpyHostToDevice));
}

#endif // HH2HD_H
