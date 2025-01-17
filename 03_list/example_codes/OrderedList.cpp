#include "List.hpp"

// 有序向量唯一化
template <typename T>
int List<T>::uniquify() {
  if (_size < 2)
    return 0;

  int oldSize = _size;
  ListNodePosi(T) p;
  ListNodePosi(T) q;
  for (p = header, q = p->succ; trailer != q; p = q, q = q->succ)
    if (p->data == q->data) {
      remove(q);
      q = p;
    }

  return oldSize - _size;
}

// 查找
template <typename T>
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const {
  while (0 <= n--)
    if (((p = p->pred)->data) <= e))
      break;

  return p;
}