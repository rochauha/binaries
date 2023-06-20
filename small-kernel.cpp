#include <iostream>
#include "hip/hip_runtime.h"

__global__ void add1(int *arr) {

  int tId = hipThreadIdx_x;
  arr[tId] = arr[tId] + 1;

}

int main() {
  std::cout << "yo\n";
}
