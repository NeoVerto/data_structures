#include <cstdint>

using std::int64_t;

// 计算 Fibonacci 数列的第 n 项 (二分递归版)
int64_t fib(int n) {
  return (2 > n) ?
        (int64_t)n  // 若到达递归基, 直接取值
        : fib(n - 1) + fib(n - 2);  // 否则, 递归计算前两项, 其和为正解.
}