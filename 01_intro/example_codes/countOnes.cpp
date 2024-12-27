// 统计整数 n 的二进制展开中数位 1 的总数
int countOnes(unsigned int n) {
  int ones = 0;       // 计数器复位
  while (0 < n) {     // 在 n 缩减至 0 之前, 反复地
    ones += (1 & n);  // 检查最低位, 若为 1 则计数
    n >>= 1;          // 右移 1 位
  }
  return ones;        // 返回计数
} // 等效于 glibc 的内置函数 int __builtin_popcount(unsigned int n)