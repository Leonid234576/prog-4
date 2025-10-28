#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev;
    long long cap;
};

class Dinic {
    int n;
    vector<vector<Edge>> adj;
    vector<int> level, ptr;
    const long long INF = 1e18;

public:
    Dinic(int n) : n(n) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int u, int v, long long cap) {
        adj[u].push_back({v, (int)adj[v].size(), cap});
        adj[v].push_back({u, (int)adj[u].size() - 1, 0});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    long long dfs(int u, int t, long long flow) {
        if (u == t || flow == 0) return flow;
        for (int &i = ptr[u]; i < (int)adj[u].size(); i++) {
            Edge &e = adj[u][i];
            if (level[e.to] == level[u] + 1 && e.cap > 0) {
                long long pushed = dfs(e.to, t, min(flow, e.cap));
                if (pushed > 0) {
                    e.cap -= pushed;
                    adj[e.to][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    long long max_flow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, t, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    Dinic dinic(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        long long cap;
        cin >> u >> v >> cap;
        u--; v--; 
        dinic.add_edge(u, v, cap);
    }

    int s, t;
    cin >> s >> t;
    s--; t--; 

    cout << dinic.max_flow(s, t) << "\n";

    return 0;
}
