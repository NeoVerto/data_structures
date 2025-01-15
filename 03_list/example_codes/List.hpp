#ifndef LIST_HPP
#define LIST_HPP

#include "ListNode.hpp"

template <typename T>
class List {  // 列表模板类
private:
  int _size;                // 规模
  ListNodePosi(T) header;   // 头哨兵
  ListNodePosi(T) trailer;  // 尾哨兵

protected:
  void init();  // 列表创建时的初始化
  int clear();  // 清除所有节点
  void copyNodes(ListNodePosi(T), int); // 复制列表中自位置 p 起的 n 项

  void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);
  void mergeSort(ListNodePosi(T)&, int);
  void selectionSort(ListNodePosi(T), int);
  void insertionSort(ListNodePosi(T), int);

public:
  // 构造函数
  List() { init(); }                      // 默认构造函数
  List(List<T> const& L);                 // 整体复制列表 L
  List(List<T> const& L, Rank r, int n);  // 复制列表 L 中自第 r 项起的 n 项
  List(ListNodePosi(T) p, int n);         // 复制列表中自位置 p 起的第 n 项

  // 析构函数
  ~List();  // 释放 (包含头, 尾哨兵在内的) 所有节点

  // 只读访问接口
  Rank size() const { return _size; }
  bool empty() const { return _size <= 0; }

  T& operator[](Rank r) const;  // 重载, 支持循秩访问 (效率低)

  ListNodePosi(T) first() const { return header->succ; }  // 首节点位置
  ListNodePosi(T) last() const { return trailer->succ; }  // 末节点位置

  bool vaild(ListNodePosi(T) p) { // 判断位置 p 是否对外合法
    return p && (trailer != p) && (header != p);
  }

  int disordered() const; // 判断列表是否已经排序
 
  // 无序查找
  ListNodePosi(T) find(T const& e) const {
    return finde(e, _size, trailer);
  }
  ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;

  // 有序查找
  ListNodePosi(T) search(T const& e) const {
    return search(e, _size, trailer);
  }
  ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;

  ListNodePosi(T) selectMax() {
    return selectMax(header->succ, _size);
  }
  ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);

  // 可写访问接口
  ListNodePosi(T) insertAsFirst(T const& e);  // 将 e 当作首节点插入
  ListNodePosi(T) insertAsLast(T const& e);   // 将 e 当作末节点插入
  ListNodePosi(T) insertFront(ListNodePosi(T) p, T const& e); // 将 e 当作 p 的前驱插入
  ListNodePosi(T) insertBack(ListNodePosi(T) p, T const& e);  // 将 e 当作 p 的后继插入

  T remove(ListNodePosi(T) p);  // 删除合法位置 p 处的节点, 并返回被删除节点.

  // 排序
  void merge(List<T>& L) {
    merge(first(), _size, L, L.first(), L._size);
  }
  void sort() { sort(first(), _size); }
  void sort(ListNodePosi(T) p, int n);

  int deduplicate();  // 无序去重
  int uniquify();     // 有序去重
  void reverse();     // 前后倒置

  // 遍历
  void traverse(void (*)(T&));  // 遍历, 依次实施 visit 操作 (函数指针, 只读 / 局部性修改)
  template <typename VST>       // 操作器
  void traverse(VST&);          // 遍历, 依次实施 visit 操作 (函数对象, 全局性修改)
};

#endif // LIST_HPP