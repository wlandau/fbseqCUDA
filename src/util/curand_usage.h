#ifndef UTIL_CURAND_USAGE_H
#define UTIL_CURAND_USAGE_H

double runiform(chain_t *dd, int g, double LB, double UB){
  double x = ((double)rand()/(double)(RAND_MAX + 1.0));
  return x * (UB - LB) + LB;
}

double rnormal(chain_t *dd, int g, double mean, double sd){
  double x = runiform(dd, g, 0.0, 1.0),
         y = runiform(dd, g, 0.0, 1.0),
         z = sqrt(-2.0*log(x))*cos(2*M_PI*y);
  return z * sd + mean;
}

double rt(chain_t *dd, int g, double mean, double scale, int df){
  double z = rnormal(dd, g, 0.0, 1.0), v = 0, x, t;
  int i;
  for(i = 0; i < df; ++i){
    x = rnormal(dd, g, 0.0, 1.0);
    v += x*x;
  }
  t = z/sqrt(v/df);
  return t*scale + mean;
}

#endif // UTIL_CURAND_USAGE_H
