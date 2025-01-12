#include "Vector.hpp"

#include <algorithm>
#include <cstdlib>

template <typename T>
T& Vector<T>::operator[](Rank r) const {
  return _elem[r];
}

// 置乱算法
template <typename T>
void permute(Vector<T>& V) {
  for (int i = V.size(); i > 0; --i)
    std::swap(V[i - 1], V[std::rand() % i]);
}

// 等概率随机置乱向量区间 [lo, hi)
template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
  T* V = _elem + lo;  // 将子向量 _elem[lo, hi) 视作另一向量 V[0, hi - lo)
  for (Rank i = hi - lo; i > 0; --i)  // 自后向前
    std::swap(V[i - 1], V[std::rand() % i]);  // 将 V[i - 1] 与 V[0, i) 中某一元素随机交换.
}

// 无序向量的顺序查找: 返回最后一个元素 e 的位置; 失败时, 返回 lo - 1
template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {  // assert: 0 <= lo < hi <= _size
  while ((lo < hi--) && e != _elem[hi]) // 从后向前, 顺序查找
    ;
  return hi;  // 若 hi < lo, 则意味着失败; 否则 hi 即命中元素的秩.
}

// 将 e 作为秩为 r 的元素插入
template <typename T>
Rank Vector<T>::insert(Rank r, const T &e) {  // assert: 0 <= r <= size;
  expand(); // 若有必要, 扩容

  for (int i = _size; i > r; --i) // 自后向前, 后继元素顺次后移一个单元
    _elem[i] = _elem[i - 1];
  _elem[r] = e;                   // 置入新元素并
  ++_size;                        // 更新容量

  return r; // 返回秩
}

// 删除区间 [lo, hi)
template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
  if (lo == hi)       // 单独处理退化情况, 如 remove(0, 0)
    return 0;

  while (hi < _size)  // [hi, _size) 顺次前移 hi - lo 个单元
    _elem[lo++] = _elem[hi++];
  _size = lo;         // 更新规模, 直接丢弃尾部 [lo, _size = hi) 区间.

  shrink();           // 若有必要, 缩容

  return hi - lo;     // 返回被删除元素的数目
}

// 删除向量中秩为 r 的元素, 0 <= r < size
template <typename T>
T Vector<T>::remove(Rank r) {
  T e = _elem[r];   // 备份被删除元素
  remove(r, r + 1); // 调用区间删除算法, 等效于对区间 [r, r + 1) 的删除

  return e;         // 返回被删除元素
}

// 删除无序向量中重复元素 (高效版)
template <typename T>
int Vector<T>::deduplicate() {
  int oldSize = _size;            // 记录原规模

  Rank i = 1;                     // 从 _elem[1] 开始
  while (i < _size)               // 自前向后逐一考察各元素
    (find(_elem[i], 0, i) < 0) ?  // 在其前缀中寻找与之雷同者 (至多一个)
    ++i                         // 若无雷同则继续考察其后继, 否则
                               : remove(i);                // 删除雷同者

  return oldSize - _size;
}

// 遍历 (函数指针机制)
template <typename T>
void Vector<T>::traverse(void (*visit)(T &)) {
  for (int i = 0; i < _size; ++i)
    visit(_elem[i]);
}

// 遍历 (函数对象机制)
template <typename T>
template <typename VST>
void Vector<T>::traverse(VST &) {
  for (int i = 0; i < _size; ++i)
    visit(_elem[i]);
}