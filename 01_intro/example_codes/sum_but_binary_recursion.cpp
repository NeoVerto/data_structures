// 数组求和算法 (二分递归版, 入口为 sum(A, 0, n - 1))
int sum(int A[], int lo, int hi) {
  if (lo == hi)   // 如遇递归基, 则
    return A[lo]; // 直接返回该元素
  else {          // 否则 (一般情况下 lo < hi),
    int mi = (lo + hi) >> 1;  // 以居中单元为界, 将原区间一分为二
    return sum(A, lo, mi) + sum(A, mi + 1, hi); // 递归对各子数组求和, 然后合计
  }
}