#ifndef SAMPLER_METROPOLIS_H
#define SAMPLER_METROPOLIS_H

__device__ args_t metropolis(chain_t *dd, args_t args){
  int accept;

printf("hi\n");

  double x, lp, lu;
  x = rt(dd, args.idx, args.x0, args.tune, 5);
  lp = MIN(0.0, ltarget(dd, args, x) - ltarget(dd, args, args.x0));
  lu = log(runiform(dd, args.idx, 0.0, 1.0));
  accept = lu < lp;
  if(accept){
    args.x = x;
    if(dd->adapt){
      args.tune *= 1.1;
    } else {
      args.tuneAux++;
    }
  } else {
    args.x = args.x0;
    if(dd->adapt) args.tune /= 1.1;
  }
  return args;
}

#endif // SAMPLER_METROPOLIS_H
