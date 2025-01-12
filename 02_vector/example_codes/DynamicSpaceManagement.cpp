#include "Vector.hpp"

// 扩容算法
template <typename T>
void Vector<T>::expand() {
  if (_size < _capacity)  // 尚未满员时, 不必扩容
    return;
  if (_capacity < DEFAULT_CAPACITY) // 不低于最小容量
    _capacity = DEFAULT_CAPACITY;

  T* oldElem = _elem;
  _elem = new T[_capacity <<= 1];
  for (int i = 0; i < _size; ++i) // 复制原向量内容 (T 为基本类型, 或已重载赋值操作符 '=')
    _elem[i] = oldElem[i];
  delete[] oldElem; // 释放原空间
}

// 缩容算法
template <typename T>
void Vector<T>::shrink() {
  if (_capacity < DEFAULT_CAPACITY << 1)  // 不至于收缩到 DEFAULT_CAPACITY 以下
    return;
  if (_size << 2 > _capacity) // 以 25 % 为界
    return;

  T* oldElem = _elem;
  _elem = new T[_capacity >>= 1]; // 容量减半
  for (int i = 0; i < _size; ++i) // 复制原向量内容
    _elem[i] = oldElem[i];
  delete[] oldElem;
}