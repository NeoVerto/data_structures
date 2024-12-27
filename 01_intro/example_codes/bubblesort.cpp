#include <algorithm>
using std::swap;

void bubblesort1A(int A[], int n) {
  bool sorted = false;            // 整体排序标志: 首先假定尚未排序
  while (!sorted) {               // 尚未确认已全局排序前, 逐趟进行扫描交换
    sorted = true;                // 假定已经排序

    for (int i = 1; i < n; ++i) { // 自左向右逐对检查当前范围 A[0, n) 内的各相邻元素
      if (A[i - 1] > A[i]) {      // 一旦 A[i - 1] 与 A[i] 逆序, 则
        swap(A[i - 1], A[i]);     // 交换之, 并
        sorted = false;           // 由于整体有序无法保证, 清除排序标志
      }
    }

    --n;                          // 末元素必然就位, 可缩短排序序列的有效长度.
  } // 借助布尔型标志位 sorted, 可提前退出, 而非总是蛮力地做 n - 1 趟扫描交换
}