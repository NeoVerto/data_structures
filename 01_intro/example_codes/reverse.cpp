#include <algorithm>

using std::swap;

// 数组倒置 (多递归基递归版)
void reverse(int* A, int lo, int hi) {
  if (lo < hi) {
    swap(A[lo], A[hi]);         // 交换 A[lo] 和 A[hi]
    reverse(A, lo + 1, hi - 1); // 递归倒置 A(lo, hi)
  } // else 隐含了两种递归基: lo == hi, lo > hi.
}

void reverse(int* A, int n) { reverse(A, 0, n - 1); }