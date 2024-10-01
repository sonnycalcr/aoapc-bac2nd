// UVa514 Rails
#include <cstdio>
#include <stack>
#include <string>

using namespace std;
const int MAXN = 1000 + 10;

int n, target[MAXN];

int main() {
  // 重定向输入数据，省去我们手动输入的繁琐
  string relativePathToCurrentCFile = "./data/UVa514/input2.txt";
  // relativePathToCurrentCFile = "./data/UVa210/input3.txt";
  freopen(string("./ch06" + relativePathToCurrentCFile.substr(1, relativePathToCurrentCFile.size() - 1)).c_str(), "r", stdin);

  while (scanf("%d", &n) == 1) { // 读取 N
    if (n == 0) {
      break;
    }
    while (true) {
      scanf("%d", &target[1]); // 读取序列的第一个数
      if (target[1] == 0) {    // 如果是 0，那么，说明当前这个样例结束了
        printf("\n");
        break;
      }
      for (int i = 2; i <= n; i++) // 继续读入
        scanf("%d", &target[i]);

      stack<int> s; // 利用 stack 来进行模拟处理
      int A = 1, B = 1;
      int ok = 1;
      while (B <= n) {
        if (A == target[B]) { // 当前的车厢和 target 在 B 这个位置所要求的车厢是相同的，那么不用经过 station 直接进入左边的轨道即可
          A++;
          B++;
        } else if (!s.empty() && s.top() == target[B]) { // 栈的顶部符合条件
          s.pop();
          B++;
        } else if (A <= n) // 目前没有符号条件的，就入栈
          s.push(A++);
        else { // 越界或者非法情况
          ok = 0;
          break;
        }
      }
      printf("%s\n", ok ? "Yes" : "No");
    }
  }

  return 0;
}
