#ifndef UTIL_CUDA_USAGE_H
#define UTIL_CUDA_USAGE_H

#define PAR_ROOT_BLOCK 16

#define PAR_BLOCK_N MIN(hd->deviceProp.maxThreadsDim[1], PAR_ROOT_BLOCK)
#define PAR_BLOCK_G MIN(hd->deviceProp.maxThreadsDim[0], PAR_ROOT_BLOCK)
#define PAR_BLOCK   MIN(hd->deviceProp.maxThreadsDim[0], PAR_ROOT_BLOCK * PAR_ROOT_BLOCK)

#define PAR_GRID_N MIN(hd->deviceProp.maxGridSize[1], ((li(hh, "N")[0]/ PAR_BLOCK_N) + 1))
#define PAR_GRID_G MIN(hd->deviceProp.maxGridSize[0], ((li(hh, "G")[0]/ PAR_BLOCK_G) + 1))
#define PAR_GRID   MIN(hd->deviceProp.maxGridSize[0], ((MAX(li(hh, "N")[0], li(hh, "G")[0])/ PAR_BLOCK) + 1))


#define ROOT_BLOCK 1 // 16

#define BLOCK_N 1 // MIN(hd->deviceProp.maxThreadsDim[1], ROOT_BLOCK)
#define BLOCK_G 1 // MIN(hd->deviceProp.maxThreadsDim[0], ROOT_BLOCK)
#define BLOCK   1 // MIN(hd->deviceProp.maxThreadsDim[0], ROOT_BLOCK * ROOT_BLOCK)

#define GRID_N 1 // MIN(hd->deviceProp.maxGridSize[1], ((li(hh, "N")[0]/ BLOCK_N) + 1))
#define GRID_G 1 // MIN(hd->deviceProp.maxGridSize[0], ((li(hh, "G")[0]/ BLOCK_G) + 1))
#define GRID   1 // MIN(hd->deviceProp.maxGridSize[0], ((MAX(li(hh, "N")[0], li(hh, "G")[0])/ BLOCK) + 1))

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

#define IDX ((blockIdx.x * blockDim.x) + threadIdx.x)
#define IDY ((blockIdx.y * blockDim.y) + threadIdx.y)

#define NTHREADSX (blockDim.x * gridDim.x)
#define NTHREADSY (blockDim.y * gridDim.y)

#define CUDA_CALL(x) { \
  REprintf("CUDA_CALL at %s:%i\n", __FILE__, __LINE__); \
  if((x) != cudaSuccess){ \
    REprintf("CUDA error at %s:%d\n",__FILE__,__LINE__); \
    REprintf("  %s\n", cudaGetErrorString(cudaGetLastError()));}}

#define KERNEL_CHECK { \
  REprintf("KERNEL_CHECK at %s:%i\n", __FILE__, __LINE__); \
  cudaError err = cudaGetLastError(); \
  if (cudaSuccess != err) \
    REprintf("cudaCheckError() failed at %s:%i : %s\n", \
            __FILE__, __LINE__, cudaGetErrorString(err)); \
  err = cudaDeviceSynchronize(); \
  if(cudaSuccess != err) \
    REprintf("cudaCheckError() with sync failed at %s:%i : %s\n", \
            __FILE__, __LINE__, cudaGetErrorString(err)); \
}

int getDevice(){
	int device;
	cudaGetDevice(&device);
  return device;
}

int setDevice(int device) {
	int dev, deviceCount;
	cudaGetDeviceCount(&deviceCount);
  if(deviceCount < 1){
    REprintf("No CUDA-capable GPUs detected.");
    return -1;
  }
  if(device < 0 || device >= deviceCount)
    Rprintf("Warning: invalid device index. Setting device = abs(device) mod deviceCount.\n");
  dev = abs(device) % deviceCount;
	CUDA_CALL(cudaSetDevice(dev));
  return dev;
}

extern "C" SEXP RgetDevice(){
	int device = 0;
	cudaGetDevice(&device);

  SEXP result = PROTECT(allocVector(INTSXP, 1));
  INTEGER(result)[0] = device;
  UNPROTECT(1);

  return result;
}

extern "C" SEXP RgetDeviceCount(){
	int count = 0;
	cudaGetDeviceCount(&count);

  SEXP result = PROTECT(allocVector(INTSXP, 1));
  INTEGER(result)[0] = count;
  UNPROTECT(1);

  return result;
}

extern "C" SEXP RsetDevice(SEXP device) {
  SEXP result = PROTECT(allocVector(INTSXP, 1));
	INTEGER(result)[0] = setDevice(INTEGER(device)[0]);
  UNPROTECT(1);
  return result;
}

void device_info(chain_t *hd){
  int dev;
  cudaDeviceProp deviceProp;
  cudaGetDevice(&dev);
  cudaGetDeviceProperties(&deviceProp, dev);
  hd->deviceIndex = dev;
  hd->deviceProp = deviceProp;
}

__global__ void serial_reduce_aux(chain_t *dd){
  int g;
  for(g = 1; g < dd->G; ++g)
    dd->aux[0] = dd->aux[0] + dd->aux[g];
}

#endif // UTIL_CUDA_USAGE_H
