#ifndef SAMPLER_TARGETS_H
#define SAMPLER_TARGETS_H

#define LTARGET_BETA         0
#define LTARGET_EPSILON      1
#define LTARGET_GAMMA        2
#define LTARGET_INV_GAMMA    3
#define LTARGET_NU           4
#define LTARGET_XI_LAPLACE   5
#define LTARGET_XI_T         6
#define LTARGET_XI_HORSESHOE 7

double ltarget_beta(chain_t *dd, args_t args, double x){
  int j;
  double ret = -INFINITY, z = (x - args.C);
  ret = args.A*x - args.B*z*z;
  for(j = 0; j < args.designUniqueN; ++j)
    ret -= exp(dd->D[I(j, args.idx)]*x) * dd->aux[I(j, args.idx)];
  if(isnan(ret))
    ret = -INFINITY;
  return ret;
}

double ltarget_epsilon(chain_t *dd, args_t args, double x){
  double ret = -INFINITY;
  double z = (x - args.C);
  ret = args.A*x - args.B*z*z - args.D*exp(x);
  if(isnan(ret))
    ret = -INFINITY;
  return ret;
}

double ltarget_gamma(chain_t *dd, args_t args, double x){
  if(x <= args.lowerbound || x >= args.upperbound) return -INFINITY;
  double a = args.shape, b = args.rate;
  return /* a*log(b) - lgamma(a) + */ (a-1)*log(x) - b*x;
}

double ltarget_inv_gamma(chain_t *dd, args_t args, double x){
  if(x <= args.lowerbound || x >= args.upperbound) return -INFINITY;
  double a = args.shape, b = args.scale;
  return /* a*log(b) - lgamma(a) */ -(a+1)*log(x) - b/x;
}

double ltarget_nu(chain_t *dd, args_t args, double x){
  double ret = -INFINITY;
  if(x > args.lowerbound & x < args.D)
    ret = args.C * (-lgamma(0.5 * x) + 0.5 * x * log(args.A*x)) - args.B*x;
  if(isnan(ret))
    ret = -INFINITY;
  return ret;
}

double ltarget_xi_laplace(chain_t *dd, args_t args, double x){
  double ret = -INFINITY;
  if(x > args.lowerbound)
    ret = -0.5 * log(x) - args.A / x - args.B * x;
  if(isnan(ret))
    ret = -INFINITY;
  return ret;
}

double ltarget_xi_t(chain_t *dd, args_t args, double x){
  double ret = -INFINITY;
  if(x > args.lowerbound)
    ret = -args.A * log(x) - args.B / x;
  if(isnan(ret))
    ret = -INFINITY;
  return ret;
}

double ltarget_xi_horseshoe(chain_t *dd, args_t args, double x){
  double ret = -INFINITY;
  if(x > args.lowerbound)
    ret = -log(x * (1.0 + x)) - args.A / x;
  if(isnan(ret))
    ret = -INFINITY;
  return ret;
}

double ltarget(chain_t *dd, args_t args, double x){
  switch(args.target_type){
    case LTARGET_BETA         : return ltarget_beta(dd, args, x);
    case LTARGET_EPSILON      : return ltarget_epsilon(dd, args, x);
    case LTARGET_GAMMA        : return ltarget_gamma(dd, args, x);
    case LTARGET_INV_GAMMA    : return ltarget_inv_gamma(dd, args, x);
    case LTARGET_NU           : return ltarget_nu(dd, args, x);
    case LTARGET_XI_LAPLACE   : return ltarget_xi_laplace(dd, args, x);
    case LTARGET_XI_T         : return ltarget_xi_t(dd, args, x);
    case LTARGET_XI_HORSESHOE : return ltarget_xi_horseshoe(dd, args, x);
    default                   : return -INFINITY;
  }
}

#endif // SAMPLER_TARGETS_H
