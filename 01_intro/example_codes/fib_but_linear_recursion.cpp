#include <cstdint>

using std::int64_t;

// 计算 Fibonacci 数列第 n 项 (线性递归版): 入口形式 fib(n, prev)
int64_t fib(int n, int64_t& prev) {
  if (0 == n) { // 若到达递归基, 则
    prev = 1;   // 直接取值: fib(-1) = 1, fib(0) = 0;
    return 0;
  }
  else {        // 否则
    int64_t prevPrev; // 递归计算前两项
    prev =  fib(n - 1, prevPrev);
    return prev + prevPrev; // 其和即为正解.
  }
}