// 数组求和算法 (线性递归版)
int sum(int A[], int n) {
  if (n < 1)                          // 平凡情况, 递归基
    return 0;                         // 直接 (非递归式) 计算
  else                                // 一般情况
    return sum(A, n - 1) + A[n - 1];  // 递归: 前 n - 1 项和 + 第 n - 1 项.
}