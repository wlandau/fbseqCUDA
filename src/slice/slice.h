#ifndef SLICE_H
#define SLICE_H

__device__ double slice(chain_t *dd, args_t args){
  int stepsL = args.max_steps,
      stepsR = args.max_steps;
      
  double x,
         lu = ltarget(dd, args, args.x0) + log(runiform(dd, args.idx, 0.0, 1.0)),
         L = args.x0 - runiform(dd, args.idx, 0.0, args.step_width),
         R = L + args.step_width;

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
