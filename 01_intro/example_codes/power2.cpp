#include <cstdint>

using std::int64_t;

inline int64_t sqr(int64_t a) { return a * a; }

// 幂函数 2^n 算法 (优化递归版), n >= 0
int64_t power2(int n) {
  if (0 == n) // 递归基
    return 1;
  // 视 n 的奇偶性分别递归
  return (n & 1) ? sqr(power2(n >> 1)) << 1 : sqr(power2(n >> 1));
}