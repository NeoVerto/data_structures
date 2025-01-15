#ifndef LISTNODE_HPP
#define LISTNODE_HPP

typedef int Rank;
#define ListNodePosi(T) ListNode<T>*  // 列表节点位置

template <typename T>
struct ListNode { // 列表节点模板类 (双向链表)
  // 成员
  T data;               // 数值
  ListNodePosi(T) pred; // 前驱
  ListNodePosi(T) succ; // 后继

  // 构造函数
  ListNode() {} // 针对 header 和 trailer 的构造
  ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr)
    : data(e), pred(p), succ(s) {}  // 默认构造器

  // 操作接口
  ListNodePosi(T) insertAsPred(T const& e); // 紧靠当前节点之前插入新节点
  ListNodePosi(T) insertAsSucc(T const& e); // 紧随当前节点之后插入新节点
};


#endif // LISTNODE_HPP