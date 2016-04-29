#ifndef GIBBS_THETA_H
#define GIBBS_THETA_H

__global__ void theta_kernel1(chain_t *dd, int l){
  int g;
  for(g = IDX; g < dd->G; g += NTHREADSX)
    dd->aux[g] = 1.0 / dd->xi[I(l, g)];
}

__global__ void theta_kernel2(chain_t *dd, int l){
  int g;
  for(g = IDX; g < dd->G; g += NTHREADSX)
    dd->aux[g] = dd->beta[I(l, g)] / dd->xi[I(l, g)];
}

__global__ void theta_kernel3(chain_t *dd, double A0, double B0, int l){ // single thread
  double A = 0.5 * (1.0/(dd->c[l]*dd->c[l]) + A0/dd->sigmaSquared[l]),
         B = B0/dd->sigmaSquared[l];
  dd->theta[l] = rnormal(dd, l, 0.5*B/A, sqrt(0.5/A));
}

void thetaSample(SEXP hh, chain_t *hd, chain_t *dd){
  int l, G = li(hh, "G")[0];
  if(!(vi(le(hh, "parameter_sets_update"), "theta"))) return;

  for(l = 0; l < li(hh, "L")[0]; ++l){
    theta_kernel1<<<GRID, BLOCK>>>(dd, l);
//    thrust::device_ptr<double> tmpA(hd->aux);
//    double A0 = thrust::reduce(tmpA, tmpA + G);
    serial_reduce_aux<<<1, 1>>>(dd);
    double A0;
    CUDA_CALL(cudaMemcpy(&A0, hd->aux, sizeof(double), cudaMemcpyDeviceToHost));
    printf("A0 = %g\n", A0);

    theta_kernel2<<<GRID, BLOCK>>>(dd, l);
//    thrust::device_ptr<double> tmpB(hd->aux);
//    double B0 = thrust::reduce(tmpB, tmpB + G);
    serial_reduce_aux<<<1, 1>>>(dd);
    double B0;
    CUDA_CALL(cudaMemcpy(&B0, hd->aux, sizeof(double), cudaMemcpyDeviceToHost));
    printf("B0 = %g\n", B0);

    theta_kernel3<<<1, 1>>>(dd, A0, B0, l);
  }
}

#endif // GIBBS_THETA_H
