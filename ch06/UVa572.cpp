#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

const int maxn = 100 + 5;

char pic[maxn][maxn];
int m, n, idx[maxn][maxn];

void dfs(int r, int c, int id) {
  if (r < 0 || r >= m || c < 0 || c >= n) // 越界了
    return;
  if (idx[r][c] > 0 || pic[r][c] != '@') // 已经被访问过了，或者没有石油
    return;
  idx[r][c] = id; // 标记为已经访问过
  for (int dr = -1; dr <= 1; dr++) // direction of row
    for (int dc = -1; dc <= 1; dc++) // direction of column
      if (dr != 0 || dc != 0)
        dfs(r + dr, c + dc, id);
}

int main() {
  // 重定向标准输入到文件
  string relativePathToCurrentCFile = "./data/UVa572/input1.txt";
  freopen(string("./ch06" + relativePathToCurrentCFile.substr(1, relativePathToCurrentCFile.size() - 1)).c_str(), "r", stdin);

  while (scanf("%d%d", &m, &n) == 2 && m && n) { // 读取数据
    for (int i = 0; i < m; i++)
      scanf("%s", pic[i]);
    memset(idx, 0, sizeof(idx)); // 给 idx 置 0
    int cnt = 0;
    // 对二维数组中的每个 item 进行处理
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)
        if (idx[i][j] == 0 && pic[i][j] == '@') // 当前坐标没有被标记过，并且有石油
          dfs(i, j, ++cnt);
    printf("%d\n", cnt);
  }
  return 0;
}

