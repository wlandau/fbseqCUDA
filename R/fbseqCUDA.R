#' @title Function \code{RgetDevice}
#' @description Get the index of the current GPU.
#' 
#' @export
#' @return Number of CUDA-capable GPUs.
RgetDevice = function(){
  .Call("RgetDevice", PACKAGE = "fbseqCUDA")
}

#' @title Function \code{RgetDeviceCount}
#' @description Get the number of CUDA-capable GPUs.
#' 
#' @export
#' @return Number of CUDA-capable GPUs.
RgetDeviceCount = function(){
  .Call("RgetDeviceCount", PACKAGE = "fbseqCUDA")
}

#' @title Function \code{RsetDevice}
#' @description Set the GPU for running the current MCMC chain.
#' 
#' @export
#' @return Integer index of the current CUDA-capable GPU, which is >= 0 and 
#' < number of devices.
#' @param device Index of the GPU to use. Must be an integer from 0 to number of GPUs - 1.
RsetDevice = function(device){
  .Call("RsetDevice", PACKAGE = "fbseqCUDA", device)
}

#' @title Function \code{fbseqCUDA}
#' @description Calls the C++/CUDA code behind the \code{fbseq()} function
#' in the \code{fbseq} package.
#' 
#' @export
#' @return a \code{Chain} object with updated parameter values. You can feed
#' this object back into another call to \code{fbseq} to continue the chain
#' from where you left off.
#'
#' @param chain object of type \code{Chain}. This \code{chain} argument could be
#' a newly created \code{Chain} object from \code{Chain(...)}. Alternatively,
#' if \code{chain} is the output from a previous call to \code{fbseq(...)},
#' then the function will continue the MCMC from where it left off.
fbseqCUDA = function(chain){
  Chain(slots = .Call("fbseqCUDA", PACKAGE = "fbseqCUDA", s4list(chain)))
}
