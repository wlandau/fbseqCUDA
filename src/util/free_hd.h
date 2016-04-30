#ifndef UTIL_FREE_HD_H
#define UTIL_FREE_HD_H

void free_hd(chain_t *hd){

  free(hd->bounds);
  free(hd->contrasts);
  free(hd->counts);
  free(hd->design);
  free(hd->propositions);

  free(hd->countSums_g);
  free(hd->countSums_n);
  free(hd->designUnique);
  free(hd->designUniqueN);
  free(hd->probs);
  free(hd->seeds);

  free(hd->a);
  free(hd->b);
  free(hd->c);
  free(hd->d);
  free(hd->h);
  free(hd->k);
  free(hd->q);
  free(hd->r);
  free(hd->s);

  free(hd->beta);
  free(hd->epsilon);
  free(hd->gamma);
  free(hd->nu);
  free(hd->sigmaSquared);
  free(hd->tau);
  free(hd->theta);
  free(hd->xi);

  free(hd->betaStart);
  free(hd->epsilonStart);
  free(hd->gammaStart);
  free(hd->nuStart);
  free(hd->sigmaSquaredStart);
  free(hd->tauStart);
  free(hd->thetaStart);
  free(hd->xiStart);

  free(hd->loglikPostMean);
  free(hd->betaPostMean);
  free(hd->epsilonPostMean);
  free(hd->gammaPostMean);
  free(hd->nuPostMean);
  free(hd->sigmaSquaredPostMean);
  free(hd->tauPostMean);
  free(hd->thetaPostMean);
  free(hd->xiPostMean);

  free(hd->betaPostMeanSquare);
  free(hd->epsilonPostMeanSquare);
  free(hd->gammaPostMeanSquare);
  free(hd->nuPostMeanSquare);
  free(hd->sigmaSquaredPostMeanSquare);
  free(hd->tauPostMeanSquare);
  free(hd->thetaPostMeanSquare);
  free(hd->xiPostMeanSquare);

  free(hd->betaTune);
  free(hd->epsilonTune);
  free(hd->gammaTune);
  free(hd->nuTune);
  free(hd->sigmaSquaredTune);
  free(hd->tauTune);
  free(hd->thetaTune);
  free(hd->xiTune);

  free(hd->betaTuneAux);
  free(hd->epsilonTuneAux);
  free(hd->gammaTuneAux);
  free(hd->nuTuneAux);
  free(hd->sigmaSquaredTuneAux);
  free(hd->tauTuneAux);
  free(hd->thetaTuneAux);
  free(hd->xiTuneAux);

  free(hd->aux);
  free(hd->D);

  free(hd);
}

#endif // UTIL_FREE_HD_H
