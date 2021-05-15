#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
static const int N = 100;
static vector<int> G[N]; // 邻接表
static bool visit[N] = {false}; // 访问数组

void DFS(int v) {
    visit[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
        if (!visit[G[v][i]])
            DFS(G[v][i]);
    }
}

void BFS(int v) {
    queue<int> Q;
    visit[v] = true;
    Q.push(v);
    while (!Q.empty()) {
        int k = Q.front();
        Q.pop();
        for (int i = 0; i < G[k].size(); i++) {
            if (!visit[G[k][i]]) {
                visit[G[k][i]] = true;
                Q.push(G[k][i]);
            }
        }
    }
}

int isConnected(int n) {
    int v = 0;
    while (v < 1 || v > 5) {
        printf("please input a valid start index: 1~5\n");
        scanf("%d", &v);
    }
    //DFS(v);
    BFS(v);
    for (int i = 1; i <= n; ++i) { // 假设结点从1开始编号
        if(!visit[i])
            return 0; // 不连通
    }
    return 1; // 连通
}

int main() {
    int n, m; // 顶点数,边数
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) { // 构建无向图的邻接表
        int a, b;
        scanf("%d%d", &a, &b); // 输入边的两个顶点
        G[a].push_back(b); // 边a->b
        G[b].push_back(a); // 边b->a
    }
    memset(visit, 0, sizeof(visit));
    printf("%d\n", isConnected(n));
    return 0;
}
