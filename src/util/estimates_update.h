#ifndef UTIL_ESTIMATES_UPDATE_H
#define UTIL_ESTIMATES_UPDATE_H

void estimates_update_kernel1(chain_t *dd){
  int l;

  dd->nuPostMean[0] += dd->nu[0];
  dd->tauPostMean[0] += dd->tau[0];

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMean[l] += dd->sigmaSquared[l];
    dd->thetaPostMean[l] += dd->theta[l];
  }
}

void estimates_update_kernel2(chain_t *dd){
  int l;

  dd->nuPostMeanSquare[0] += dd->nu[0]*dd->nu[0];
  dd->tauPostMeanSquare[0] += dd->tau[0]*dd->tau[0];

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMeanSquare[l] += dd->sigmaSquared[l]*dd->sigmaSquared[l];
    dd->thetaPostMeanSquare[l] += dd->theta[l]*dd->theta[l];
  }
}

void estimates_update_kernel3(chain_t *dd){
  int id, l, n;
  for(id = IDX; id < dd->G; id += NTHREADSX){
    dd->gammaPostMean[id] += dd->gamma[id];
    for(l = 0; l < dd->L; ++l){
      dd->betaPostMean[I(l, id)] += dd->beta[I(l, id)];
      dd->xiPostMean[I(l, id)] += dd->xi[I(l, id)];
    }
    for(n = 0; n < dd->N; ++n)
      dd->epsilonPostMean[I(n, id)] += dd->epsilon[I(n, id)];
  }
}

void estimates_update_kernel4(chain_t *dd){
  int id, l, n;
  for(id = IDX; id < dd->G; id += NTHREADSX){
    dd->gammaPostMeanSquare[id] += dd->gamma[id]*dd->gamma[id];
    for(l = 0; l < dd->L; ++l){
      dd->betaPostMeanSquare[I(l, id)] += dd->beta[I(l, id)]*dd->beta[I(l, id)];
      dd->xiPostMeanSquare[I(l, id)] += dd->xi[I(l, id)]*dd->xi[I(l, id)];
    }
    for(n = 0; n < dd->N; ++n)
      dd->epsilonPostMeanSquare[I(n, id)] += dd->epsilon[I(n, id)]*dd->epsilon[I(n, id)];
  }
}

void estimates_update_kernel5(chain_t *dd){
  int c, g, truth, l, p;
  double contrast;
  for(g = IDX; g < dd->G; g += NTHREADSX){
    for(p = 0; p < dd->P; ++p){
      truth = 1;

      for(c = 0; c < dd->C; ++c){
        if(!dd->propositions[Ipropositions(p, c)]) continue;
        contrast = 0.0;
        for(l = 0; l < dd->L; ++l)
          contrast += dd->contrasts[Icontrasts(c, l)] * dd->beta[I(l, g)];
        truth *= (contrast > dd->bounds[c]);
      }

      dd->probs[I(p, g)] += truth;
    }
  }
}

void estimates_update(SEXP hh, chain_t *hd, chain_t *dd){
  estimates_update_kernel1(dd);
  estimates_update_kernel2(dd);
  estimates_update_kernel3(dd);
  estimates_update_kernel4(dd);
  estimates_update_kernel5(dd);
}

#endif // UTIL_ESTIMATES_UPDATE_H
