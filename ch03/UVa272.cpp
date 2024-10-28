#include <cstdio>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  // 重定向输入数据，省去我们手动输入的繁琐
  string relativePathToCurrentCFile = "./data/UVa272/input1.txt";
  freopen(string("./ch03" + relativePathToCurrentCFile.substr(1, relativePathToCurrentCFile.size() - 1)).c_str(), "r", stdin);

  int c, q = 1;
  while ((c = getchar()) != EOF) {
    if (c == '"') {
      printf("%s", q ? "``" : "''");
      q = !q;
    } else
      printf("%c", c);
  }
  return 0;
}
