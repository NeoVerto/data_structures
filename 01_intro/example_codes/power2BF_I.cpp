#include <cstdint>

using std::int64_t;

// 幂函数 2^n 算法 (蛮力迭代版), n >= 0
int64_t power2BF_I(int n) {
  int64_t pow = 1;  // 累积器初始化为 2^0
  while (0 < n--)   // 迭代 n 轮, 每轮
    pow <<= 1;      // 将累积器翻倍
  return pow;       // 返回累积器
}