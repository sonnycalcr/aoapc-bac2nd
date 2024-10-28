#include <cstdio>
#include <string>

using namespace std;

char s[] = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";

int main(int argc, char *argv[]) {
  // 重定向输入数据，省去我们手动输入的繁琐
  string relativePathToCurrentCFile = "./data/UVa10082/input1.txt";
  freopen(string("./ch03" + relativePathToCurrentCFile.substr(1, relativePathToCurrentCFile.size() - 1)).c_str(), "r", stdin);

  int i, c;
  while ((c = getchar()) != EOF) {
    for (i = 1; s[i] && s[i] != c; i++)
      ;
    if (s[i])
      putchar(s[i - 1]);
    else 
      putchar(c);
  }
  return 0;
}
