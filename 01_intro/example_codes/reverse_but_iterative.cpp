#include <algorithm>

using std::swap;

// // 数组倒置 (直接改造而得到的迭代版)
// void reverse(int* A, int lo, int hi) {
// next: // 算法起始位置添加跳转标志
//   if (lo < hi) {
//     swap(A[lo], A[hi]);
//     ++lo; --hi; // 收缩待倒置区间
//     goto next;  // 跳转到算法体的起始位置, 迭代地倒置 A(lo, hi)
//   } // else 隐含了迭代的终止.
// }

// 数组倒置 (规范整理后的迭代版)
void reverse(int* A, int lo, int hi) {
  while (lo < hi) // 用 while 替换跳转标志与 if, 完全等效.
    swap(A[++lo], A[--hi]);
}

void reverse(int* A, int n) { reverse(A, 0, n - 1); }