#ifndef SAMPLER_SLICE_STEP_H
#define SAMPLER_SLICE_STEP_H

args_t slice_step(chain_t *dd, args_t args){

  double iter, sum_length, x;
  double lu = ltarget(dd, args, args.x0) + log(runiform(dd, args.idx, 0.0, 1.0));
  double L = args.x0 - runiform(dd, args.idx, 0.0, args.tune);
  double R = L + args.tune;

  int su = (int) trunc(runiform(dd, args.idx, 0.0, MAX_STEPS + 0.999999));
  int stepsL = su;
  int stepsR = MAX_STEPS - su;

  while ((lu < ltarget(dd, args, L)) && (stepsL > 0)) {
    L = L - args.tune;
    stepsL = stepsL - 1;
  }

  while ((lu < ltarget(dd, args, R)) & (stepsR > 0)) {
    R = R + args.tune;
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
    args.tuneAux += iter * fabs(args.x - args.x0);
    if(iter > MIN_ADAPT){
      sum_length = 0.5 * iter * (iter + 1.0);
      args.tune = args.tuneAux / sum_length;
    }
  }

  return args;
}

#endif // SAMPLER_SLICE_STEP_H
