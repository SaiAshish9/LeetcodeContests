class Solution {
public:

    vector<int> par, lvl, heavyChild, chainHead, inTime, subSize;
    vector<vector<int>> graph;
    vector<int> seg;
    int timer;
    int N;

    void buildTree(vector<int>& arr) {
        int sz = 1;
        while (sz < N) sz <<= 1;
        seg.assign(2 * sz, 0);

        for (int i=0; i< N; i++) {
            seg[sz + i] = arr[i];
        }

        for (int i = sz - 1; i > 0; i--) {
            seg[i] = seg[2*i] ^ seg[2*i+1];
        }
    }

    void pointUpdate(int idx, int val) {
        int sz = seg.size() / 2;
        idx += sz;
        seg[idx] = val;

        while (idx > 1) {
            idx >>= 1;
            seg[idx] = seg[2*idx] ^ seg[2*idx+1];
        }
    }

    int rangeQuery(int l, int r) {
        int sz = seg.size() / 2;
        l += sz;
        r += sz;

        int ans = 0;
        while (l<=r) {
            if (l & 1) ans ^= seg[l++];
            if (!(r &1)) ans ^= seg[r--];
            l >>= 1;
            r >>= 1;
        }
        return ans;
    }

    int dfsBuild(int u, int p) {
        par[u] = p;
        subSize[u] = 1;
        int best = 0;

        for (int v: graph[u]) {
            if (v == p) continue;
            lvl[v] = lvl[u] + 1;
            int childSize = dfsBuild(v, u);
            subSize[u] += childSize;

            if (childSize > best) {
                best = childSize;
                heavyChild[u] = v;
            }
        }

        return subSize[u];
    }

    void hld(int u, int headNode, vector<int>& baseArr, string& str) {
        chainHead[u] = headNode;
        inTime[u] = timer;
        baseArr[timer++] = 1 << (str[u] - 'a');

        if (heavyChild[u] != -1) {
            hld(heavyChild[u], headNode, baseArr, str);
        }

        for (int v : graph[u]) {
            if ( v != par[u] && v != heavyChild[u]) {
                hld(v, v, baseArr, str);
            }
        }
    }

    int queryUp(int u, int v) {
        int res = 0;

        while (chainHead[u] != chainHead[v]) {

            if (lvl[chainHead[u]] < lvl[chainHead[v]]) {
                swap(u, v);
            }
            
            res ^= rangeQuery(inTime[chainHead[u]], inTime[u]); 
            u = par[chainHead[u]];
        }

        if (lvl[u] > lvl[v]) {
            swap(u, v);
        }
        
        res ^= rangeQuery(inTime[u], inTime[v]);
        return res;
    }
    
    vector<bool> palindromePath(int nodes, vector<vector<int>>& edges, string str, vector<string>& queries) {
        auto suneravilo = make_tuple(nodes, edges, str);
        N = nodes;
        graph.assign(N, {});

        for (auto &e: edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        par.assign(N, -1);
        lvl.assign(N, 0);
        heavyChild.assign(N, -1);
        chainHead.assign(N, 0);
        inTime.assign(N, 0);
        subSize.assign(N, 0);

        dfsBuild(0, -1);

        vector<int> baseArr(N);
        timer = 0;
        hld(0, 0, baseArr, str);

        buildTree(baseArr);
        vector<bool> result;

        for (string &q: queries) {
            stringstream ss(q);
            string type;
            ss >> type;

            if (type == "update") {
                int node;
                char ch;
                ss >> node >> ch;
                str[node] = ch;
                pointUpdate(inTime[node], 1 << (ch - 'a'));
                
            } else {
                int u, v;
                ss >> u >> v;
                int mask = queryUp(u, v);
                result.push_back(__builtin_popcount(mask) <= 1);
            }
        }

        return result;
    }
};