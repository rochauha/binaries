#include <iostream>
#include <cassert>
#include "hip/hip_runtime.h"

__global__ void add1(int *arr) {

  int tId = hipThreadIdx_x;
  if (tId >= 32)
    return;
  arr[tId] = arr[tId] + 1;

}

int main() {
  size_t size = 32 * sizeof(int);
  int *hostMem = (int *)malloc(size);
  for (int i = 0; i < 32; ++i) {
    hostMem[i] = 5;
  }

  int *deviceMem;
  std::cerr << "before malloc\n";
  assert(hipMalloc((void **)&deviceMem, size) == hipSuccess);
  std::cerr << "after malloc\n";

  assert(hipMemcpy(deviceMem, hostMem, size, hipMemcpyHostToDevice) == hipSuccess);
  std::cerr << "after copy\n";
  int threadsPerBlock = 32;
  int blocksPerGrid = 1;
  std::cerr << "before launch\n";
  hipLaunchKernelGGL(add1, blocksPerGrid, threadsPerBlock, 0, hipStreamDefault, deviceMem);

  std::cerr << "after launch\n";

  assert(hipMemcpy(hostMem , deviceMem, size, hipMemcpyDeviceToHost) == hipSuccess);

  for (int i = 0; i < 32; ++i) {
    std::cout << hostMem[i];
  }
  std::cout << "\n";
}
