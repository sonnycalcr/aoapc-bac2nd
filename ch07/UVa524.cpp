#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

// 一种简单的判断素数的方法
int is_prime(int x) {
  for (int i = 2; i * i <= x; i++)
    if (x % i == 0)
      return 0;
  return 1;
}

// n: 题目给定的 n
// A: 存放所求的序列
// isp: 素数表
// vis: 记录是否已经被访问过的表
int n, A[50], isp[50], vis[50];

/*
  从 1 开始，依次去搜索每个位置上的可能性

  cur: 当前的位置
*/
void dfs(int cur) {
  if (cur == n && isp[A[0] + A[n - 1]]) { // 递归边界
    for (int i = 0; i < n; i++) {
      if (i != 0)
        printf(" ");
      printf("%d", A[i]);
    }
    printf("\n");
  } else
    for (int i = 2; i <= n; i++)
      if (!vis[i] && isp[i + A[cur - 1]]) { // 判断当前的数字是否可行，不行的就跳过，相当于是剪枝了
        A[cur] = i;
        vis[i] = 1;   // 标记已经访问过
        dfs(cur + 1); // 递归处理下一个位置
        vis[i] = 0;   // 还原
      }
}

int main() {
  string relativePathToCurrentCFile = "./data/UVa524/input1.txt";
  // relativePathToCurrentCFile = "./data/UVa210/input3.txt";
  freopen(string("./ch07" + relativePathToCurrentCFile.substr(1, relativePathToCurrentCFile.size() - 1)).c_str(), "r", stdin);

  int kase = 0;
  while (scanf("%d", &n) == 1 && n > 0) { // 读取 n
    if (kase > 0)                         // 两个 case 之间要有空行分隔
      printf("\n");
    printf("Case %d:\n", ++kase);
    for (int i = 2; i <= n * 2; i++) // 生成素数表，加快后续判断
      isp[i] = is_prime(i);
    memset(vis, 0, sizeof(vis));
    A[0] = 1; // 第一个位置只能是 1
    dfs(1);   // 从 1 开始进行深度优先搜索
  }
  return 0;
}
