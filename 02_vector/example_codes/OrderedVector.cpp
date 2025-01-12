#include "Vector.hpp"

#include <cstdlib>
#include "Fib.hpp"

// 返回向量中逆序相邻元素对的总数
template <typename T>
int Vector<T>::disordered() const {
  int n = 0;  // 计数器
  for (int i = 1; i < _size; ++i) // 逐一检查 _size - 1 对相邻元素
    if (_elem[i - 1] > _elem[i])  // 逆序则计数
      ++n;

  return n;
}

// 有序向量重复元素剔除算法 (低效版)
//template <typename T>
//int Vector<T>::uniquify() {
//  int oldSize = _size;
//
//  int i = 1;
//  while (i < _size)             // 从前向后, 逐一比对各相邻元素
//    _elem[i - 1] == _elem[i] ?
//    remove(i)                   // 若雷同, 则删除后者; 否则
//    : ++i;                      // 转至后一元素
//
//  return oldSize - _size;       // 向量规模变化量
//}

// 有序向量重复元素剔除算法 (高效版)
template <typename T>
int Vector<T>::uniquify() {
  Rank i = 0, j = 0;
  while (++j < _size)         // 逐一扫描直至末元素
    if (_elem[i] != _elem[j]) // 跳过雷同者
      _elem[++i] = _elem[j];  // 发现不同元素时, 向前移至紧邻于前者右侧

  _size = ++i;                // 直接截除尾部多于元素
  shrink();

  return j - i;               // 返回被删除元素总数
}

// 查找
template <typename T>
Rank Vector<T>::search(const T &e, Rank lo, Rank hi) const {
  return (std::rand() % 2) ?
         binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

// 二分查找算法 (版本 A): 在有序向量的区间 [lo, hi) 内查找元素 e, 0 <= lo <= hi <= _size;
//template <typename T>
//static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {
//  while (lo < hi) {           // 每步迭代要做两次比较判断: 三个分支
//    Rank mi = (lo + hi) >> 1; // 以中点为轴点
//    if (e < A[mi])            // 深入前半段 [lo, mi) 继续查找
//      hi = mi;
//    else if (A[mi] < e)       // 深入后半段 (mi, hi) 继续查找
//      lo = mi + 1;
//    else                      // 在 mi 处命中, 成功查找提前终止
//      return mi;
//  }
//  return -1;  // 查找失败
//} // 多个命中元素无法保证返回秩最大者; 查找失败时, 简单的返回 -1, 而不能指示失败的位置

// 二分查找算法 (版本 B): 在有序向量的区间 [lo, hi) 内查找元素 e, 0 <= lo <= hi <= _size
//template <typename T>
//static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {
//  while (1 < hi - lo) {
//    Rank mi = (lo + hi) >> 1;
//    (e < A[mi]) ? hi = mi : lo = mi;
//  } // 出口时 hi = lo + 1, 查找区间只剩下一个元素 A[lo]
//
//  return (e == A[lo]) ? lo : -1;
//} // 多个命中元素无法保证返回秩最大者; 查找失败时, 简单的返回 -1, 而不能指示失败的位置

// 二分查找算法 (版本 C): 在有序向量的区间 [lo, hi) 内查找元素 e, 0 <= lo <= hi <= _size
template <typename T>
static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {
  while (lo < hi) {
    Rank mi = (lo + hi) >> 1;
    (e < A[mi]) ? hi = mi : lo = mi + 1;
  }

  return --lo;
} // 多个命中元素总保证返回秩最大者; 查找失败时, 能指示失败的位置


// Fibonacci 查找
template <typename T>
static Rank fibSearch(T* A, T const& e, Rank lo, Rank hi) {
  Fib fib(hi - lo);

  while (lo < hi) {
    while (hi - lo < fib.get())
      fib.prev();

    Rank mi = lo + fib.get() - 1;
    if (e < A[mi])
      hi = mi;
    else if (A[mi] < e)
      lo = mi + 1;
    else
      return mi;
  }

  return -1;
}