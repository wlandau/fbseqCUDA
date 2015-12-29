#ifndef SAMPLER_METROPOLIS_H
#define SAMPLER_METROPOLIS_H

__device__ double ldt(double x, double mean, double sd, double df){
  double s =  sd * sqrt((df - 2.0)/df);
  double z = ((x - mean)/sd);
  -0.5 * (df + 1.0) * log(1.0 + ((z*z) / df));
}

__device__ args_t metropolis(chain_t *dd, args_t args){
  int accept, df = 5;
  double a, b, x, lf0, lf1, lq0, lq1, lp, lu;
  if(args.target_type == LTARGET_GAMMA){
    a = args.shape;
    b = args.rate;
    args.x0 = (a - 1.0)/b;
    args.tune = sqrt(a)/b;
  } else if(args.target_type == LTARGET_INV_GAMMA){
    a = args.shape;
    b = args.scale;
    args.x0 = b/(a + 1.0);
    args.tune = b/((a - 1.0) * sqrt(a - 2.0));
  }

  x = rt(dd, args.idx, args.x0, args.tune, df);

  lf1 = ltarget(dd, args, x);
  lf0 = ltarget(dd, args, args.x0);

  lq1 = ldt(x, args.x0, args.tune, df);
  lq0 = ldt(args.x0, x, args.tune, df);

  lp = lf1 - fl0 - lq1 + lq0;

  return args;
}

#endif // SAMPLER_METROPOLIS_H
