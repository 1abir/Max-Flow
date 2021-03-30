//
// Created by abirm on 12/8/2018.
//

#include <iostream>
#include <stdio.h>

#define INF 11111
using namespace std;
enum Color {
    WHITE, GRAY, BLACK
};

class Queue {
public:
    int head, tail;
    int *q;

    Color *color;

    explicit Queue(int n) : head(0), tail(0) {
        q = new int[n + 2];
        color = new Color[n];
    }

    void enqueue(int x) {
        q[tail] = x;
        tail++;
        color[x] = GRAY;
    }

    int dequeue() {
        int x = q[head];
        head++;
        color[x] = BLACK;
        return x;
    }
};

class MaxFlow {
public:
    int n;
    int e;
    int **capacity;
    int **flow;
    int *parent;


    MaxFlow(int n, int e) : n(n), e(e) {
        capacity = new int *[n];
        flow = new int *[n];
        parent = new int[n];
        for (int i = 0; i < n; ++i) {
            capacity[i] = new int[n];
            flow[i] = new int[n];
            for (int j = 0; j < n; ++j) {
                capacity[i][j] = 0;
                flow[i][j] = 0;
            }
        }
    }

    int bfs(int source, int sink) {
        Queue queue(n);
        for (int i = 0; i < n; i++) {
            queue.color[i] = WHITE;
        }
        queue.enqueue(source);
        parent[source] = -1;
        while (queue.head != queue.tail) {
            int u = queue.dequeue();
            for (int j = 0; j < n; j++) {
                if (queue.color[j] == WHITE && capacity[u][j] - flow[u][j] > 0) {
                    queue.enqueue(j);
                    parent[j] = u;
                }
            }
        }
        return queue.color[sink] == BLACK;
    }

    int max_flow(int source, int sink) {
        int max_flow = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                flow[i][j] = 0;
            }
        }
        while (bfs(source, sink)) {
            int minResidualCapacity = INF;
            for (int i = sink; parent[i] != (-1); i = parent[i]) {
                minResidualCapacity = min(minResidualCapacity, capacity[parent[i]][i] - flow[parent[i]][i]);
            }
            for (int j = sink; parent[j] != (-1); j = parent[j]) {
                flow[parent[j]][j] += minResidualCapacity;
                flow[j][parent[j]] -= minResidualCapacity;
            }
            max_flow += minResidualCapacity;
        }
        return max_flow;
    }
};

int main() {
    int n, e;
    freopen("maxInp.txt", "r", stdin);
    freopen("maxFloeOutput.txt", "w", stdout);
    cin >> n >> e;
    MaxFlow maxFlow(n, e);
    int a, b, c;
    for (int i = 0; i < e; i++) {
        cin >> a >> b >> c;
        maxFlow.capacity[a][b] += c;
    }
    int source, sink;
    cin >> source >> sink;
    cout << "Max Flow : " << maxFlow.max_flow(source, sink);
    return 0;
}
