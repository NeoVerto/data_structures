// 数组求和算法 (迭代版)
int sumI(int A[], int n) {
  int sum = 0;                // 初始化累计器
  for (int i = 0; i < n; ++i) // 对全部共 $n$ 个元素, 逐一
    sum += A[i];              // 累计
  return sum;                 // 返回累计值
}