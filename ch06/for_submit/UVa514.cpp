// UVa514 Rails
#include <cstdio>
#include <stack>

using namespace std;
const int MAXN = 1000 + 10;

int n, target[MAXN];

int main() {
    while (scanf("%d", &n) == 1) {
        if (n == 0) {
            break;
        }
        while (true) {
            scanf("%d", &target[1]);
            if (target[1] == 0) {
                printf("\n");
                break;
            }
            for (int i = 2; i <= n; i++)
                scanf("%d", &target[i]);

            stack<int> s;
            int A = 1, B = 1;
            int ok = 1;
            while (B <= n) {
                if (A == target[B]) {
                    A++;
                    B++;
                } else if (!s.empty() && s.top() == target[B]) {
                    s.pop();
                    B++;
                } else if (A <= n)
                    s.push(A++);
                else {
                    ok = 0;
                    break;
                }
            }
            printf("%s\n", ok ? "Yes" : "No");
        }
    }

    return 0;
}

// Accepted Time 100ms Length 1041 Lang C++11 5.3.0 Submitted 2024-09-20 20:56:30
