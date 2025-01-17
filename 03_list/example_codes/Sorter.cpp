#include "List.hpp"

#include <cstdlib>

// 统一入口
template <typename T>
void List<T>::sort(ListNodePosi(T) p, int n) {
  switch (std::rand() % 3) {
    case 1:
      insertionSort(p, n);
      break;
    case 2:
      selectionSort(p, n);
      break;
    default:
      mergeSort(p, n);
      break;
  }
}

// 插入排序
template <typename T>
void List<T>::insertionSort(ListNodePosi(T) p, int n) {
  for (int r = 0; r < n; ++r) {
    insertBack(search(p->data, r, p), p->data);
    p = p->succ;
    remove(p->pred);
  }
}

// 选择排序
template <typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n) {
  ListNodePosi(T) max = p;
  for (ListNodePosi(T) cur = p; 1 < n; --n)
    if ((cur = cur->succ)->data >= max->data)
      max = cur;

  return max;
}

template <typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n) {
  ListNodePosi(T) head = p->pred;
  ListNodePosi(T) tail = p;
  for (int i = 0; i < n; ++i)
    tail = tail->succ;
  while (1 < n) {
    ListNodePosi(T) max = selectMax(head->succ, n);
    insertFront(tail, remove(max));
    tail = tail->pred;
    --n;
  }
}

// 归并排序
template<typename T>
void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m) {
  ListNodePosi(T) pp = p->pred;
  while (0 < m)
    if ((0 < n) && (p->data <= q->data)) {
      if (q == (p = p->succ))
        break;
      --n;
    }
    else {
      insertFront(p, L.remove((q = q->succ)->pred));
      --m;
    }

  p = pp->succ;
}

template<typename T>
void List<T>::mergeSort(ListNodePosi(T)& p, int n) {
  if (n < 2)
    return;

  int m = n >> 1;
  ListNodePosi(T) q = p;
  for (int i = 0; i < m; ++i)
    q = q->succ;

  mergeSort(p, m);
  mergeSort(q, n - m);
  merge(p, m, *this, q, n - m);
}