#ifndef SLICE_HORSESHOE_H
#define SLICE_HORSESHOE_H

/* Taken from James Scott (2020)
 * "Parameter expansion in local-shrinkage models"
 * on arXiv
 * See the beginning of Section 2.2.
 */

__device__ double exp_cdf(double x, double rate){
  return 1.0 - exp(-rate*x);
}

__device__ double exp_invcdf(double u, double rate){
  double tol = 1e-12;
  return -log(1.0 - u - tol)/(rate + tol);
}

__device__ args_t slice_horseshoe(chain_t *dd, args_t args){
  double eta = 1.0/args.x0;
  double u = runiform(dd, args.idx, 0.0, 1.0/(1.0 + eta));
  double upper = exp_cdf((1.0 - u)/u, args.A);
  double u2 = runiform(dd, args.idx, 0.0, upper);
  eta = exp_invcdf(u2, args.A);
  args.x = 1.0/eta;
  if(!isfinite(args.x)) args.x = args.x0;
  return args;
}

#endif // SLICE_HORSESHOE_H
