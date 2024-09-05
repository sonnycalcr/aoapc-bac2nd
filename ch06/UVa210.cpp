#include <cstdio>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <string>
using namespace std;

const int maxlinecnt = 1000; // 最多 1000 行，这是一个大致的数量
const int linecharcnt = 10;  // 每一行的字符串长度不会超过 10(按：这是推断出来的，我们假定程序中没有过多的空格，否则这里就还需要再调整)

deque<int> readyQ;                  // ready 队列
queue<int> blockQ;                  // 存放被阻塞的程序的队列
int n;                              // 会参与并行运行的程序的数量
int quantum;                        // 时间片长度
int c[5];                           // 每个语句所需的运行时间
int var[26];                        // 最多 26 个变量
int ip[maxlinecnt];                 // ip[pid]是程序pid的当前行号。所有程序都存在prog数组，更类似真实的情况，代码也更短
bool locked;                        // 是否已经被锁住
char prog[maxlinecnt][linecharcnt]; // 存储所有程序的指令，每个程序的每条指令都是一行字符串

void run(int pid) {
    int q = quantum;
    while (q > 0) {
        char *p = prog[ip[pid]]; // 取出 pid 号程序中当前该运行的那一行
        switch (p[2]) { // 根据第 3 个字符来判断
        case '=': // 赋值
            var[p[0] - 'a'] = isdigit(p[5]) ? (p[4] - '0') * 10 + p[5] - '0' : p[4] - '0';
            q -= c[0];
            break;
        case 'i': // 打印
            printf("%d: %d\n", pid + 1, var[p[6] - 'a']);
            q -= c[1];
            break;
        case 'c': // lock
            if (locked) {
                blockQ.push(pid); // 放入阻塞队列
                return;
            }
            locked = true;
            q -= c[2];
            break;
        case 'l': // unlock
            locked = false;
            if (!blockQ.empty()) {
                int pid2 = blockQ.front();
                blockQ.pop();
                readyQ.push_front(pid2);
            }
            q -= c[3];
            break;
        case 'd': // end
            return;
        }
        ip[pid]++;
    }
    readyQ.push_back(pid);
}

int main() {
    // 重定向输入数据，省去我们手动输入的繁琐
    string relativePathToCurrentCFile = "./data/UVa210/input1.txt";
    // relativePathToCurrentCFile = "./data/UVa210/input3.txt";
    freopen(string("./ch06" + relativePathToCurrentCFile.substr(1, relativePathToCurrentCFile.size() - 1)).c_str(), "r", stdin);

    int T; // input 数据中 case 的数量
    scanf("%d", &T);
    while (T--) { // 分别处理每一个 case
        scanf("%d %d %d %d %d %d %d\n", &n, &c[0], &c[1], &c[2], &c[3], &c[4], &quantum);
        memset(var, 0, sizeof(var));

        int line = 0;
        for (int i = 0; i < n; i++) {
            fgets(prog[line++], maxlinecnt, stdin); // 按行读取数据
            ip[i] = line - 1;
            while (prog[line - 1][2] != 'd')
                fgets(prog[line++], linecharcnt, stdin);
            readyQ.push_back(i); // 把 id 为 i 的程序入队
        }

        locked = false; // 初始值为 false
        while (!readyQ.empty()) {
            int pid = readyQ.front();
            readyQ.pop_front();
            run(pid);
        }
        if (T)
            printf("\n");
    }
    return 0;
}
