#' @title Function \code{RgetDevice}
#' @description Get the index of the current GPU.
#' 
#' @export
#' @return Number of CUDA-capable GPUs.
RgetDevice = function(){
  .Call("RgetDevice", PACKAGE = "heterosisCUDA")
}

#' @title Function \code{RgetDeviceCount}
#' @description Get the number of CUDA-capable GPUs.
#' 
#' @export
#' @return Number of CUDA-capable GPUs.
RgetDeviceCount = function(){
  .Call("RgetDeviceCount", PACKAGE = "heterosisCUDA")
}

#' @title Function \code{RsetDevice}
#' @description Set the GPU for running the current MCMC chain.
#' 
#' @export
#' @return Integer index of the current CUDA-capable GPU, which is >= 0 and 
#' < number of devices.
#' @param device Index of the GPU to use. Must be an integer from 0 to number of GPUs - 1.
RsetDevice = function(device){
  .Call("RsetDevice", PACKAGE = "heterosisCUDA", device)
}

#' @title Function \code{heterosisCUDA}
#' @description Calls the C++/CUDA code behind the \code{run_mcmc()} function
#' in the \code{heterosis} package.
#' 
#' @export
#' @return a \code{Chain} object with updated parameter values. You can feed
#' this object back into another call to \code{heterosis} to continue the chain
#' from where you left off.
#'
#' @param chain object of type \code{Chain}. This \code{chain} argument could be
#' a newly created \code{Chain} object from \code{Chain(...)}. Alternatively,
#' if \code{chain} is the output from a previous call to \code{heterosis(...)},
#' then the function will continue the MCMC from where it left off.
heterosisCUDA = function(chain){
  Chain(.Call("heterosisCUDA", PACKAGE = "heterosisCUDA", s4list(chain)))
}
