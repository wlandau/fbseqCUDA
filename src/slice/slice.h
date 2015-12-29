#ifndef SLICE_SLICE_H
#define SLICE_SLICE_H

__device__ args_t slice(chain_t *dd, args_t args){

  double iter, sum_length, x;
  double lu = ltarget(dd, args, args.x0) + log(runiform(dd, args.idx, 0.0, 1.0));
  double L = args.x0 - runiform(dd, args.idx, 0.0, args.width);
  double R = L + args.width;

  int su = (int) trunc(runiform(dd, args.idx, 0.0, MAX_STEPS + 1.0 - 1e-12));
  int stepsL = su;
  int stepsR = MAX_STEPS - su;

  while ((lu < ltarget(dd, args, L)) && (stepsL > 0)) {
    L = L - args.width;
    stepsL = stepsL - 1;
  }

  while ((lu < ltarget(dd, args, R)) & (stepsR > 0)) {
    R = R + args.width;
    stepsR = stepsR - 1;
  }

  do {
    x = runiform(dd, args.idx, L, R);
    if (x > args.x0)
      R = x;
    else
      L = x;
  } while(ltarget(dd, args, x) < lu);
  args.x = x;

  if(dd->adapt){
    iter = dd->m + 1.0;
    args.sumDiff += iter * fabs(args.x - args.x0);
    if(iter > MIN_ADAPT){
      sum_length = 0.5 * iter * (iter + 1.0);
      args.width = args.sumDiff / sum_length;
    }
  }

  return args;
}

#endif // SLICE_SLICE_H
