#include "List.hpp"
// 默认构造方法
template <typename T>
void List<T>::init() {
  header = new ListNode<T>;
  trailer = new ListNode<T>;

  header->succ = trailer;
  header->pred = nullptr;

  trailer->pred = header;
  trailer->succ = nullptr;

  _size = 0;
}

// 由秩到位置的转换
template <typename T>
T& List<T>::operator[](Rank r) const {
  ListNodePosi(T) p = first();
  while (0 < r--)
    p = p->succ;
  return p->data;
}

// 无序查找
template <typename T>
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const {
  while (0 < n--)
    if (e == (p = p->pred)->data)
      return p;
  return nullptr;
}

// 插入
template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const& e) {
  ++_size;
  return header->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const& e) {
  ++_size;
  return trailer->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertFront(ListNodePosi(T) p, T const& e) {
  ++_size;
  return p->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertBack(ListNodePosi(T) p, T const& e) {
  ++_size;
  return p->insertAsSucc(e);
}

// 前插入
template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e) {
  ListNodePosi(T) x = new ListNode(e, pred, this);  // 创建新节点
  pred->succ = x;
  pred = x;

  return x;
}

// 后插入
template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e) {
  ListNodePosi(T) x = new ListNode(e, this, succ);  // 创建新节点
  succ->pred = x;
  succ = x;

  return x;
}

// copyNodes()
template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n) {
  init();
  while (n--) {
    insertAsLast(p->data);
    p = p->succ;
  }
}

// 基于复制的构造
template <typename T>
List<T>::List(ListNodePosi(T) p, int n) { copyNodes(p, n); }

template <typename T>
List<T>::List(List<T> const& L) { copyNodes(L.first(), L.size()); }

template <typename T>
List<T>::List(List<T> const& L, int r, int n) { copyNodes(L[r], n); }

// 删除
template <typename T>
T List<T>::remove(ListNodePosi(T) p) {
  T e = p->data;

  p->pred->succ = p->succ;
  p->succ->pred = p->pred;
  delete p;
  --_size;

  return e;
}

// 析构函数
template <typename T>
int List<T>::clear() {
  int oldSize = _size;
  while (0 < _size)
    remove(header->succ);
  return oldSize;
}

template <typename T>
List<T>::~List() {
  clear();
  delete header;
  delete trailer;
}

// 唯一化
template <typename T>
int List<T>::deduplicate() {
  if (_size < 2)
    return 0;

  int oldSize = _size;
  ListNodePosi(T) p = header;
  Rank r = 0;

  while (trailer != (p = p->succ)) {
    ListNodePosi(T) q = find(p->data, r, p);
    q ? remove(q) : r++;
  }

  return oldSize - _size;
}

// 遍历算法
template <typename T>
void List<T>::traverse(void (*visit)(T &)) {
  for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
    visit(p->data);
}

template <typename T>
template <typename VST>
void List<T>::traverse(VST & visit) {
  for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
    visit(p->data);
}