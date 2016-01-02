#ifndef UTIL_CUDA_USAGE_H
#define UTIL_CUDA_USAGE_H

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

#define IDX ((blockIdx.x * blockDim.x) + threadIdx.x)
#define IDY ((blockIdx.y * blockDim.y) + threadIdx.y)

#define NTHREADSX (blockDim.x * gridDim.x)
#define NTHREADSY (blockDim.y * gridDim.y)

#define BLOCK_N 1 // 16
#define BLOCK_G 1 // 16
#define BLOCK 1 // 512
#define GRID_N 1 // ((li(hh, "N")[0]/ BLOCK_N) + 1)
#define GRID_G 1 // ((li(hh, "G")[0]/ BLOCK_G) + 1)
#define GRID 1 // ((MAX(li(hh, "N")[0], li(hh, "G")[0])/ BLOCK_G) + 1)

#define CUDA_CALL(x) {if((x) != cudaSuccess){ \
  REprintf("CUDA error at %s:%d\n",__FILE__,__LINE__); \
  REprintf("  %s\n", cudaGetErrorString(cudaGetLastError()));}}

#define KERNEL_CHECK { \
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

#endif // UTIL_CUDA_USAGE_H
