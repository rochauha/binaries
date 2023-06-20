#include <iostream>
#include "hip/hip_runtime.h"

__device__ void addToAns(int *arr, int tId, int *ans) {
  ans += arr[tId];
}

__global__ void addIfEven(int *arr, int *ans) {

  int tId = hipThreadIdx_x;
  if (arr[tId] % 2 == 0)
    arr[tId] = 200 + (arr[tId] * 113);
  else
    arr[tId] = arr[tId] + 1;

  if (tId % 2 == 0)
    addToAns(arr, tId, ans);

   __syncthreads();

  if (*ans == 0) {
    *ans = *ans + 121;
    addToAns(arr, tId, ans);
  }
}

int main() {
  std::cout << "yo\n";
}
