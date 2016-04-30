#ifndef SAMPLER_SAMPLER_H
#define SAMPLER_SAMPLER_H

#define DEFAULT 1
#define SLICE_STEP 2

args_t sampler_wrap(chain_t *dd, args_t args){
  switch(args.sampler){
    case SLICE_STEP : return slice_step(dd, args);
    default         : return slice_step(dd, args);
  }
}

#endif // SAMPLER_SAMPLER_H
