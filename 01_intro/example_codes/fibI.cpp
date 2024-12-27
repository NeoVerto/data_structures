#include <cstdint>

using std::int64_t;

// 计算 Fibonacci 数列的第 n 项 (迭代版)
int64_t fibI(int n) {
  int64_t f = 0, g = 1; // 初始化: fib(0) = 0, fib(1) = 1;
  while (0 < n--) { // 依据原始定义, 通过 n 次加法与减法计算 fib(n)
    g += f;
    f = g - f;
  }
  return f;
}