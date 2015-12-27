#ifndef SLICE_H
#define SLICE_H

__device__ double slice(chain_t *dd, args_t args){

  double x;
  double lu = ltarget(dd, args, args.x0) + log(runiform(dd, args.idx, 0.0, 1.0));
  double L = args.x0 - runiform(dd, args.idx, 0.0, args.step_width);
  double R = L + args.step_width;

  int su = (int) trunc(runiform(dd, args.idx, 0.0, args.max_steps + 1.0 - 1e-12));
  int stepsL = su;
  int stepsR = args.max_steps - su;

  while ((lu < ltarget(dd, args, L)) && (stepsL > 0)) {
    L = L - args.step_width;
    stepsL = stepsL - 1;
  }

  while ((lu < ltarget(dd, args, R)) & (stepsR > 0)) {
    R = R + args.step_width;
    stepsR = stepsR - 1;
  }

  do {
    x = runiform(dd, args.idx, L, R);
    if (x > args.x0)
      R = x;
    else
      L = x;
  } while(ltarget(dd, args, x) < lu);
  return x;
}

#endif // SLICE_H
