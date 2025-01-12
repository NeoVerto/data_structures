#include "Vector.hpp"

#include <algorithm>
#include <cstdlib>

// 统一入口
template <typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
  switch (std::rand() % 5) {
    case 1:
      bubbleSort(lo, hi);
      break;
    case 2:
      selectionSort(lo, hi);
      break;
    case 3:
      mergeSort(lo, hi);
      break;
    case 4:
      heapSort(lo, hi);
      break;
    default:
      quicksort(lo, hi);
      break;
  }
}

// 起泡排序
template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
  bool sorted = true; // 整体有序标志
  while (++lo < hi)   // 自左向右, 逐一检查各对相邻元素
    if (_elem[lo - 1] > _elem[lo]) {        // 若逆序, 则
      sorted = false;                       // 尚未整体有序, 并需要
      std::swap(_elem[lo - 1], _elem[lo]);  // 通过交换使局部有序
    }
  return sorted;  // 返回有序标志
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
  while (!bubble(lo, hi--));
}

// 归并排序
template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
  T* beMerged = _elem + lo;     // 合并后的向量 beMerged[0, hi - lo) = _elem[lo, hi).

  int size_front = mi - lo;
  T* front = new T[size_front]; // 前子向量 front[0, size_front) = _elem[lo, mi)
  for (Rank i = 0; i < size_front; front[i] = beMerged[i++]);

  int size_back = hi - mi;
  T* back = _elem + mi;         // 后子向量 back[0, size_back) = _elem[mi, hi)

  for (Rank i = 0, f = 0, b = 0; (f < size_front) || (b < size_back);) {  // 将 front[f] 或 back[b] 中的小者续至 beMerged 末尾
    if ((f < size_front) && (b >= size_back  || (front[f] <= back[b])))
      beMerged[i++] = front[f++];
    if ((b < size_back)  && (f >= size_front || (back[b]  < front[f])))
      beMerged[i++] = back[b++];
  }

  delete[] front;
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
  if (hi - lo < 2)  // 单元素区间自然有序, 否则 ...
    return;
  int mi = (lo + hi) >> 1;  // 以中点为界
  mergeSort(lo, mi);
  mergeSort(mi, hi);
  merge(lo, mi, hi);
}