#ifndef SAMPLER_TARGETS_DERIV1_H
#define SAMPLER_TARGETS_DERIV1_H

__device__ double ltarget_beta_deriv1(chain_t *dd, args_t args, double x){
  int j;
  double ret = 0.0, z = (x - args.C);
  ret = args.A - 2.0 * args.B*z;
  for(j = 0; j < args.designUniqueN; ++j)
    ret -= exp(dd->D[I(j, args.idx)]*x) * dd->aux[I(j, args.idx)]
         * dd->D[I(j, args.idx)];
  if(isnan(ret))
    ret = 0.0;
  return ret;
}

__device__ double ltarget_epsilon_deriv1(chain_t *dd, args_t args, double x){
  double ret = 0.0;
  double z = (x - args.C);
  ret = args.A - 2.0 * args.B*z - args.D*exp(x);
  if(isnan(ret))
    ret = 0.0;
  return ret;
}

__device__ double ltarget_xi_laplace_deriv1(chain_t *dd, args_t args, double x){
  double ret = 0.0;
  if(x > 0.0)
    ret = -0.5 / x + args.A / (x*x) - args.B;
  if(isnan(ret))
    ret = 0.0;
  return ret;
}

__device__ double ltarget_xi_t_deriv1(chain_t *dd, args_t args, double x){
  double ret = 0.0;
  if(x > 0.0)
    ret = -args.A / x + args.B / (x*x);
  if(isnan(ret))
    ret = 0.0;
  return ret;
}

__device__ double ltarget_xi_horseshoe_deriv1(chain_t *dd, args_t args, double x){
  double ret = 0.0;
  if(x > 0.0)
    ret = -1.0/x - 1.0/(1.0 + x) + args.A / (x*x);
  if(isnan(ret))
    ret = 0.0;
  return ret;
}

__device__ double ltarget_deriv1(chain_t *dd, args_t args, double x){
  switch(args.target_type){
    case LTARGET_BETA         : return ltarget_beta_deriv1(dd, args, x);
    case LTARGET_EPSILON      : return ltarget_epsilon_deriv1(dd, args, x);
    case LTARGET_NU           : return ltarget_nu_deriv1(dd, args, x);
    case LTARGET_XI_LAPLACE   : return ltarget_xi_laplace_deriv1(dd, args, x);
    case LTARGET_XI_T         : return ltarget_xi_t_deriv1(dd, args, x);
    case LTARGET_XI_HORSESHOE : return ltarget_xi_horseshoe_deriv1(dd, args, x);
    default                   : return -CUDART_INF;
  }
}

#endif // SAMPLER_TARGETS_DERIV1_H
