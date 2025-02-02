#include "Vector.hpp"

template <typename T>
void Vector<T>::copyFrom(const T *A, Rank lo, Rank hi) {
  _elem = new T[_capacity = 2 * (hi - lo)]; // 分配空间
  _size = 0;                                // 规模清零

  while (lo < hi)             // A[lo, hi) 内的元素逐一
    _elem[_size++] = A[lo++]; // 复制至 _elem[0, hi - lo)
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V) {
  if (_elem)
    delete[] _elem; // 释放原有内容
  copyFrom(V._elem, 0, V.size()); // 整体复制
  return *this;
}