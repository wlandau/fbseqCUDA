#ifndef UTIL_ESTIMATES_UPDATE_H
#define UTIL_ESTIMATES_UPDATE_H

/*
 * Precise cumulative sum due to Welford, B. P. (1962),
 * "Note on a method for calculating corrected sums of squares and products",
 * Technometrics 4(3), 419–420.
 */
__device__ double pcs(double x_n, double x_mean, int n){
  double dn = (double) n;
  double y1 = x_n/dn;
  double y2 = x_mean/dn;
  double diff = y1 - y2;
  return x_mean + diff;
}

__global__ void estimates_update_kernel1(chain_t *dd, int m){
  int l;

  dd->nuPostMean[0] = pcs(dd->nu[0], dd->nuPostMean[0], m);
  dd->tauPostMean[0] = pcs(dd->tau[0], dd->tauPostMean[0], m);

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMean[l] = pcs(dd->sigmaSquared[l], dd->sigmaSquaredPostMean[l], m);
    dd->thetaPostMean[l] = pcs(dd->theta[l], dd->thetaPostMean[l], m);
  }
}

__global__ void estimates_update_kernel2(chain_t *dd, int m){
  int l;

  dd->nuPostMeanSquare[0] = pcs(dd->nu[0]*dd->nu[0], dd->nuPostMeanSquare[0], m);
  dd->tauPostMeanSquare[0] = pcs(dd->tau[0]*dd->tau[0], dd->tauPostMeanSquare[0], m);

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMeanSquare[l] = pcs(dd->sigmaSquared[l]*dd->sigmaSquared[l], dd->sigmaSquaredPostMeanSquare[l], m);
    dd->thetaPostMeanSquare[l] = pcs(dd->theta[l]*dd->theta[l], dd->thetaPostMeanSquare[l], m);
  }
}

__global__ void estimates_update_kernel3(chain_t *dd, int m){
  int id, l, n;
  for(id = IDX; id < dd->G; id += NTHREADSX){
    dd->gammaPostMean[id] = pcs(dd->gamma[id], dd->gammaPostMean[id], m);
    for(l = 0; l < dd->L; ++l){
      dd->betaPostMean[I(l, id)] = pcs(dd->beta[I(l, id)], dd->betaPostMean[I(l, id)], m);
      dd->xiPostMean[I(l, id)] = pcs(dd->xi[I(l, id)], dd->xiPostMean[I(l, id)], m);
    }
    for(n = 0; n < dd->N; ++n)
      dd->epsilonPostMean[I(n, id)] = pcs(dd->epsilon[I(n, id)], dd->epsilonPostMean[I(n, id)], m);
  }
}

__global__ void estimates_update_kernel4(chain_t *dd, int m){
  int id, l, n;
  for(id = IDX; id < dd->G; id += NTHREADSX){
    dd->gammaPostMeanSquare[id] = pcs(dd->gamma[id]*dd->gamma[id], dd->gammaPostMeanSquare[id], m);
    for(l = 0; l < dd->L; ++l){
      dd->betaPostMeanSquare[I(l, id)] = pcs(dd->beta[I(l, id)]*dd->beta[I(l, id)], dd->betaPostMeanSquare[I(l, id)], m);
      dd->xiPostMeanSquare[I(l, id)] = pcs(dd->xi[I(l, id)]*dd->xi[I(l, id)], dd->xiPostMeanSquare[I(l, id)], m);
    }
    for(n = 0; n < dd->N; ++n)
      dd->epsilonPostMeanSquare[I(n, id)] = pcs(dd->epsilon[I(n, id)]*dd->epsilon[I(n, id)], dd->epsilonPostMeanSquare[I(n, id)], m);
  }
}

__global__ void estimates_update_kernel5(chain_t *dd, int m){
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

      dd->probs[I(p, g)] = pcs(truth, dd->probs[I(p, g)], m);
    }
  }
}

__global__ void estimates_update_kernel6(chain_t *dd, int m){
  int c, g, l;
  double contrast;
  for(g = IDX; g < dd->G; g += NTHREADSX){
    for(c = 0; c < dd->C; ++c){
      contrast = 0.0;
      for(l = 0; l < dd->L; ++l){
        contrast += dd->contrasts[Icontrasts(c, l)] * dd->beta[I(l, g)];
      }
      dd->contrastsPostMean[I(c, g)] = pcs(contrast, dd->contrastsPostMean[I(c, g)], m);
      dd->contrastsPostMeanSquare[I(c, g)] = pcs(contrast*contrast, dd->contrastsPostMeanSquare[I(c, g)], m);
    }
  }
}

void estimates_update(SEXP hh, chain_t *hd, chain_t *dd, int m){
  estimates_update_kernel1<<<1, 1>>>(dd, m);
  estimates_update_kernel2<<<1, 1>>>(dd, m);
  estimates_update_kernel3<<<GRID, BLOCK>>>(dd, m);
  estimates_update_kernel4<<<GRID, BLOCK>>>(dd, m);
  estimates_update_kernel5<<<GRID, BLOCK>>>(dd, m);
}

#endif // UTIL_ESTIMATES_UPDATE_H
