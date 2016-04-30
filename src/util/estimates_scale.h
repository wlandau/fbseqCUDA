#ifndef UTIL_ESTIMATES_SCALE_H
#define UTIL_ESTIMATES_SCALE_H

void estimates_scale_kernel1(chain_t *dd, double iterations){
  int l;

  dd->nuPostMean[0]/= iterations;
  dd->tauPostMean[0]/= iterations;

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMean[l]/= iterations;
    dd->thetaPostMean[l]/= iterations;
  }
}

void estimates_scale_kernel2(chain_t *dd, double iterations){
  int l;

  dd->nuPostMeanSquare[0]/= iterations;
  dd->tauPostMeanSquare[0]/= iterations;

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMeanSquare[l]/= iterations;
    dd->thetaPostMeanSquare[l]/= iterations;
  }
}

void estimates_scale_kernel3(chain_t *dd, double iterations){
  int id, l, n;
  for(id = IDX; id < dd->G; id += NTHREADSX){
    dd->gammaPostMean[id]/= iterations;
    for(l = 0; l < dd->L; ++l){
      dd->betaPostMean[I(l, id)]/= iterations;
      dd->xiPostMean[I(l, id)]/= iterations;
    }
    for(n = 0; n < dd->N; ++n)
      dd->epsilonPostMean[I(n, id)]/= iterations;
  }
}

void estimates_scale_kernel4(chain_t *dd, double iterations){
  int id, l, n;
  for(id = IDX; id < dd->G; id += NTHREADSX){
    dd->gammaPostMeanSquare[id]/= iterations;
    for(l = 0; l < dd->L; ++l){
      dd->betaPostMeanSquare[I(l, id)]/= iterations;
      dd->xiPostMeanSquare[I(l, id)]/= iterations;
    }
    for(n = 0; n < dd->N; ++n)
      dd->epsilonPostMeanSquare[I(n, id)]/= iterations;
  }
}

void estimates_scale_kernel5(chain_t *dd, double iterations){
  int g, p;
  for(g = IDX; g < dd->G; g += NTHREADSX)
    for(p = 0; p < dd->P; ++p)
      dd->probs[I(p, g)] /= iterations;
}

void estimates_scale(SEXP hh, chain_t *hd, chain_t *dd){
  double M = (double) (li(hh, "iterations")[0] * li(hh, "thin")[0]);
  estimates_scale_kernel1(dd, M);
  estimates_scale_kernel2(dd, M);
  estimates_scale_kernel3(dd, M);
  estimates_scale_kernel4(dd, M);
  estimates_scale_kernel5(dd, M);
}

#endif // UTIL_ESTIMATES_SCALE_H
