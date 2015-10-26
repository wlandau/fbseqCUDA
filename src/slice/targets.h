#ifndef TARGETS_H
#define TARGETS_H

#define LTARGET_BASIC        0
#define LTARGET_GAMMA        1
#define LTARGET_INV_GAMMA    2
#define LTARGET_NU           3
#define LTARGET_XI_LAPLACE   4
#define LTARGET_XI_T         5
#define LTARGET_XI_HORSESHOE 6

__device__ double ltarget_basic(chain_t *dd, args_t args, double x){
  double ret = -CUDART_INF;
  double z = (x - args.C);
  ret = args.A*x - args.B*z*z - args.D*exp(x) - args.E*exp(-x);
  if(isnan(ret))
    ret = -CUDART_INF;
  return ret;
}

__device__ double ltarget_gamma(chain_t *dd, args_t args, double x){
  if(x < 0.0 || x > args.upperbound) return -CUDART_INF;
  double a = args.shape, b = args.rate;
  return /* a*log(b) - lgamma(a) + */ (a-1)*log(x) - b*x;
}

__device__ double ltarget_inv_gamma(chain_t *dd, args_t args, double x){
  if(x < 0.0 || x > args.upperbound) return -CUDART_INF;
  double a = args.shape, b = args.scale;
  return /* a*log(b) - lgamma(a) */ -(a+1)*log(x) - b/x;
}

__device__ double ltarget_nu(chain_t *dd, args_t args, double x){
  double ret = -CUDART_INF;
  if(x > 0.0 && x < args.D)
    ret = args.C * (-lgamma(0.5*x) + 0.5*x*log(args.A*x) - args.B*x);
  if(isnan(ret))
    ret = -CUDART_INF;
  return ret;
}

__device__ double ltarget_xi_laplace(chain_t *dd, args_t args, double x){
  double ret = -CUDART_INF;
  if(x > 0.0)
    ret = -0.5 * log(x) - args.A / x - args.B * x;
  if(isnan(ret))
    ret = -CUDART_INF;
  return ret;
}

__device__ double ltarget_xi_t(chain_t *dd, args_t args, double x){
  double ret = -CUDART_INF;
  if(x > 0.0)
    ret = -args.A * log(x) - args.B / x;
  if(isnan(ret))
    ret = -CUDART_INF;
  return ret;
}

__device__ double ltarget_xi_horseshoe(chain_t *dd, args_t args, double x){
  double ret = -CUDART_INF;
  if(x > 0.0)
    ret = -log(x * (1.0 + x)) - args.A / x;
  if(isnan(ret))
    ret = -CUDART_INF;
  return ret;
}

__device__ double ltarget(chain_t *dd, args_t args, double x){
  switch(args.target_type){
    case LTARGET_BASIC        : return ltarget_basic(dd, args, x);
    case LTARGET_GAMMA        : return ltarget_gamma(dd, args, x);
    case LTARGET_INV_GAMMA    : return ltarget_inv_gamma(dd, args, x);
    case LTARGET_NU           : return ltarget_nu(dd, args, x);
    case LTARGET_XI_LAPLACE   : return ltarget_xi_laplace(dd, args, x);
    case LTARGET_XI_T         : return ltarget_xi_t(dd, args, x);
    case LTARGET_XI_HORSESHOE : return ltarget_xi_horseshoe(dd, args, x);
    default                   : return -CUDART_INF;
  }
}

#endif // TARGETS_H
