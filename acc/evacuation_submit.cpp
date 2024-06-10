#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

#define ARRAY_SIZE 201
const int MAX_DATA = 0x7fffffff;
int capacity[ARRAY_SIZE][ARRAY_SIZE];
int flow[ARRAY_SIZE];
int pre[ARRAY_SIZE];
int n, m;
queue<int> myQueue;

int BFS(int src, int des) {
    while (!myQueue.empty())
        myQueue.pop();

    memset(pre, -1, sizeof(pre));
    pre[src] = 0;
    flow[src] = MAX_DATA;
    myQueue.push(src);

    while (!myQueue.empty()) {
        int index = myQueue.front();
        myQueue.pop();

        if (index == des)
            break;

        for (int i = 1; i <= m; ++i) {
            if (i != src && capacity[index][i] > 0 && pre[i] == -1) {
                pre[i] = index;
                flow[i] = min(capacity[index][i], flow[index]);
                myQueue.push(i);
            }
        }
    }

    return (pre[des] == -1) ? -1 : flow[des];
}

int maxFlow(int src, int des) {
    int increment, totalFlow = 0;

    while ((increment = BFS(src, des)) != -1) {
        int k = des;
        while (k != src) {
            int last = pre[k];
            capacity[last][k] -= increment;
            capacity[k][last] += increment;
            k = last;
        }
        totalFlow += increment;
    }

    return totalFlow;
}

int main() {
    int start, end, ci;

    while (cin >> m >> n) {
        memset(capacity, 0, sizeof(capacity));
        memset(flow, 0, sizeof(flow));

        for (int i = 0; i < n; ++i) {
            cin >> start >> end >> ci;
            if (start != end) {
                capacity[start][end] += ci;
            }
        }

        cout << maxFlow(1, m) << endl;
    }

    return 0;
}
