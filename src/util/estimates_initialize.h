#ifndef UTIL_ESTIMATES_INITIALIZE_H
#define UTIL_ESTIMATES_INITIALIZE_H

void estimates_initialize_kernel1(chain_t *dd){
  int l;

  dd->nuPostMean[0] = 0.0;
  dd->tauPostMean[0] = 0.0;

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMean[l] = 0.0;
    dd->thetaPostMean[l] = 0.0;
  }
}

void estimates_initialize_kernel2(chain_t *dd){
  int l;

  dd->nuPostMeanSquare[0] = 0.0;
  dd->tauPostMeanSquare[0] = 0.0;

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMeanSquare[l] = 0.0;
    dd->thetaPostMeanSquare[l] = 0.0;
  }
}

void estimates_initialize_kernel3(chain_t *dd){
  int l;

  dd->nuTune[0] = INIT_TUNE;
  dd->tauTune[0] = INIT_TUNE;

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredTune[l] = INIT_TUNE;
    dd->thetaTune[l] = INIT_TUNE;
  }
}

void estimates_initialize_kernel4(chain_t *dd){
  int l;

  dd->nuTuneAux[0] = INIT_TUNE_AUX;
  dd->tauTuneAux[0] = INIT_TUNE_AUX;

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredTuneAux[l] = INIT_TUNE_AUX;
    dd->thetaTuneAux[l] = INIT_TUNE_AUX;
  }
}

void estimates_initialize_kernel5(chain_t *dd){
  int id, l, n;
  for(id = IDX; id < dd->G; id += NTHREADSX){
    dd->gammaPostMean[id] = 0.0;
    for(l = 0; l < dd->L; ++l){
      dd->betaPostMean[I(l, id)] = 0.0;
      dd->xiPostMean[I(l, id)] = 0.0;
    }
    for(n = 0; n < dd->N; ++n)
      dd->epsilonPostMean[I(n, id)] = 0.0;
  }
}

void estimates_initialize_kernel6(chain_t *dd){
  int id, l, n;
  for(id = IDX; id < dd->G; id += NTHREADSX){
    dd->gammaPostMeanSquare[id] = 0.0;
    for(l = 0; l < dd->L; ++l){
      dd->betaPostMeanSquare[I(l, id)] = 0.0;
      dd->xiPostMeanSquare[I(l, id)] = 0.0;
    }
    for(n = 0; n < dd->N; ++n)
      dd->epsilonPostMeanSquare[I(n, id)] = 0.0;
  }
}

void estimates_initialize_kernel7(chain_t *dd){
  int id, l, n;
  for(id = IDX; id < dd->G; id += NTHREADSX){
    dd->gammaTune[id] = INIT_TUNE;
    for(l = 0; l < dd->L; ++l){
      dd->betaTune[I(l, id)] = INIT_TUNE;
      dd->xiTune[I(l, id)] = INIT_TUNE;
    }
    for(n = 0; n < dd->N; ++n)
      dd->epsilonTune[I(n, id)] = INIT_TUNE;
  }
}

void estimates_initialize_kernel8(chain_t *dd){
  int id, l, n;
  for(id = IDX; id < dd->G; id += NTHREADSX){
    dd->gammaTuneAux[id] = INIT_TUNE_AUX;
    for(l = 0; l < dd->L; ++l){
      dd->betaTuneAux[I(l, id)] = INIT_TUNE_AUX;
      dd->xiTuneAux[I(l, id)] = INIT_TUNE_AUX;
    }
    for(n = 0; n < dd->N; ++n)
      dd->epsilonTuneAux[I(n, id)] = INIT_TUNE_AUX;
  }
}

void estimates_initialize_kernel9(chain_t *dd){
  int g, p;
  for(g = IDX; g < dd->G; g += NTHREADSX)
    for(p = 0; p < dd->P; ++p)
      dd->probs[I(p, g)] = 0.0;
}

void estimates_initialize(SEXP hh, chain_t *hd, chain_t *dd){
  estimates_initialize_kernel1(dd);
  estimates_initialize_kernel2(dd);
  estimates_initialize_kernel3(dd);
  estimates_initialize_kernel4(dd);
  estimates_initialize_kernel5(dd);
  estimates_initialize_kernel6(dd);
  estimates_initialize_kernel7(dd);
  estimates_initialize_kernel8(dd);
  estimates_initialize_kernel9(dd);
}

#endif // UTIL_ESTIMATES_INITIALIZE_H
