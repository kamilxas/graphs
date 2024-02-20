#include <bits/stdc++.h>

using namespace std;

class Graph {
private:
    int n, m;
    int **matr;
    map<int,vector<pair<int,int>>>mp;
    bool orient = 0, table = 0;
    int *used;
    queue<int> bf;
public:
    Graph(int a, bool r, bool t) : n(a), orient(r), table(t) {
        if(t)
        {
            matr = new int *[n];
            for (int i = 0; i < n; i++) {
                matr[i] = new int[n];
                for (int j = 0; j < n; j++) {
                    matr[i][j] = -1;
                }
            }
        }
    }

    int quick(int a,int b)
    {
        
    }

    void swap()
    {
        if(table)
        {
            mp = *new map<int,vector<pair<int,int>>>;
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n;j++)
                {
                    if(matr[i][j]!=-1)
                    {
                        mp[i].push_back({j,matr[i][j]});
                    }
                }
            }
            delete matr;
        }
        else
        {
            matr = new int *[n];
            for (int i = 0; i < n; i++) {
                matr[i] = new int[n];
                for (int j = 0; j < n; j++) {
                    matr[i][j] = -1;
                }
            }
            for(auto i:mp) {
                for (auto j: i.second) {
                    matr[i.first][j.first]=j.second;
                }
            }
            mp.clear();
        }
    }

    void inser(int a, int b, int w) {
        if(table)
        {
            if (a > n || a < 1 || b > n || b < 1) {
                cout << "Out of size\n";
                return;
            }
            a--;
            b--;
            if (matr[a][b] == -1) {
                matr[a][b] = w;
                if (!orient) {
                    matr[b][a] = w;
                }
                m++;
            }
        }
        else
        {
            if (a > n || a < 1 || b > n || b < 1) {
                cout << "Out of size\n";
                return;
            }
            a--;
            b--;
            mp[a].push_back({b,w});
            if (!orient) {
                mp[b].push_back({a,w});
            }
            m++;
        }
    }

    void bfs(int now) {
        used = new int[n]{};
        now--;
        bf.push(now);
        cout << "Queue of bfs search: ";
        while (!bf.empty()) {
            int now = bf.front();
            cout << now + 1 << " ";
            bf.pop();
            used[now] = 2;
            if(table)
            {
                for (int i = 0; i < n; i++) {
                    if (matr[now][i] != -1 && !used[i]) {
                        used[i] = 1;
                        bf.push(i);
                    }
                }
            }
            else {
                for(auto i:mp[now])
                {
                    if(!used[i.first])
                    {
                        used[i.first] = 1;
                        bf.push(i.first);
                    }
                }
            }
        }
        cout << endl;
        delete used;
    }

    void dfs(int now) {
        used = new int[n]{};
        cout << "Queue of dfs search: ";
        dfs1(now - 1);
        cout << endl;
        delete used;
    }

    void dfs1(int now) {
        cout << now + 1 << " ";
        used[now] = 1;
        if(table) {
            for (int i = 0; i < n; i++) {
                if (matr[now][i] != -1 && !used[i]) {
                    dfs1(i);
                }
            }
        }
        else {
            for(auto i:mp[now])
            {
                if(!used[i.first])
                {
                    dfs1(i.first);
                }
            }
        }
    }

    void print() {
        if(table) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << matr[i][j] << " ";
                }
                cout << endl;
            }
        }
        else
        {
            for(int i=0;i<n;i++)
            {
                cout<<i+1<<endl;
                if(!mp[i].empty())
                {
                    for(auto j:mp[i])
                    {
                        cout<<j.first+1<<" ";
                    }
                    cout<<endl;
                }
            }
        }
    }
};

int main() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter orientation: ";
    bool k;
    cin >> k;
    cout << "Table(1) or list(0): ";
    bool t;
    cin >> t;
    Graph g(n, k, t);
    cout << "Enter number of edges: ";
    int q;
    cin >> q;
    cout << "Enter edges: \n";
    for (int i = 0; i < q; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g.inser(a, b, c);
    }
    cout << "Enter start position: ";
    cin >> n;
    g.dfs(n);
    g.bfs(n);
    return 0;
}
