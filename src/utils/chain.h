#ifndef CHAIN_H
#define CHAIN_H

typedef struct {

  int *counts;
  int *group;

  int *sums_n;
  int *sums_g;

  int N;
  int G;

  double mphtol;
  int *seeds;

  double *hph;
  double *lph;
  double *mph;

  double *dRho;
  double *dGam;
  double *aRho;
  double *aGam;
  double *bRho;
  double *bGam;
  double *cPhi;
  double *cAlp;
  double *cDel;
  double *sPhi;
  double *sAlp;
  double *sDel;
  double *kPhi;
  double *kAlp;
  double *kDel;
  double *rPhi;
  double *rAlp;
  double *rDel;

  double *nuRho;
  double *nuGam;
  double *tauRho;
  double *tauGam;
  double *thePhi;
  double *theAlp;
  double *theDel;
  double *sigPhi;
  double *sigAlp;
  double *sigDel;

  double *phi;
  double *alp;
  double *del;
  double *rho;
  double *gam;
  double *xiPhi;
  double *xiAlp;
  double *xiDel;
  double *eps;

  double *nuRhoPostMean;
  double *nuGamPostMean;
  double *tauRhoPostMean;
  double *tauGamPostMean;
  double *thePhiPostMean;
  double *theAlpPostMean;
  double *theDelPostMean;
  double *sigPhiPostMean;
  double *sigAlpPostMean;
  double *sigDelPostMean;

  double *phiPostMean;
  double *alpPostMean;
  double *delPostMean;
  double *rhoPostMean;
  double *gamPostMean;
  double *xiPhiPostMean;
  double *xiAlpPostMean;
  double *xiDelPostMean;
  double *epsPostMean;

  double *nuRhoPostMeanSq;
  double *nuGamPostMeanSq;
  double *tauRhoPostMeanSq;
  double *tauGamPostMeanSq;
  double *thePhiPostMeanSq;
  double *theAlpPostMeanSq;
  double *theDelPostMeanSq;
  double *sigPhiPostMeanSq;
  double *sigAlpPostMeanSq;
  double *sigDelPostMeanSq;

  double *phiPostMeanSq;
  double *alpPostMeanSq;
  double *delPostMeanSq;
  double *rhoPostMeanSq;
  double *gamPostMeanSq;
  double *xiPhiPostMeanSq;
  double *xiAlpPostMeanSq;
  double *xiDelPostMeanSq;
  double *epsPostMeanSq;

  curandState_t *states;
  double *aux;

} chain_t;

#endif // CHAIN_H
