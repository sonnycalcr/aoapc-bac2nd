#include <cstdio>
#include <cctype>
#include <stack>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Matrix {
  int a, b;
  Matrix(int a = 0, int b = 0) : a(a), b(b) {}
} m[26];

stack<Matrix> s;

int main(int argc, char *argv[]) {
  // 重定向标准输入到文件
  string relativePathToCurrentCppFile = "./data/UVa442/input1.txt";
  // relativePathToCurrentCppFile = "./data/UVa12569/input2.txt";
  // 因为我们是在根目录下执行编译出来的可执行文件的
  ifstream inputFile("./ch06" + relativePathToCurrentCppFile.substr(1, relativePathToCurrentCppFile.size() - 1));
  if (!inputFile.is_open()) {
    cerr << "Failed to open input data file." << endl;
    return 2;
  }
  streambuf *cinbuf = cin.rdbuf(); // save original buf
  cin.rdbuf(inputFile.rdbuf());

  int n;
  // 读入第一部分
  cin >> n;
  for (int i = 0; i < n; i++) {
    string name;
    cin >> name;
    int k = name[0] - 'A';
    cin >> m[k].a >> m[k].b;
  }
  // 处理第二部分的每一个表达式
  string expr;
  while (cin >> expr) {
    int len = expr.length();
    bool error = false;
    int ans = 0;
    for (int i = 0; i < len; i++) {
      if (isalpha(expr[i]))
        s.push(m[expr[i] - 'A']);
      else if (expr[i] == ')') {
        Matrix m2 = s.top();
        s.pop();
        Matrix m1 = s.top();
        s.pop();
        if (m1.b != m2.a) {
          error = true;
          break;
        }
        ans += m1.a * m2.a * m2.b;
        s.push(Matrix(m1.a, m2.b));
      }
    }
    if (error)
      cout << "error\n";
    else
      cout << ans << "\n";
  }

  // 恢复标准输入
  cin.rdbuf(cinbuf);
  return 0;
}
