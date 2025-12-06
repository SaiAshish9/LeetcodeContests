#include <bits/stdc++.h>
using namespace std;

class FenwickTree {
public:
    vector<int> bit;
    int n;
    FenwickTree(int n) : n(n) { bit.assign(n + 1, 0); }
    void update(int i, int delta) {
        for (++i; i <= n; i += i & -i) bit[i] += delta;
    }
    int query(int i) {
        int res = 0;
        for (++i; i > 0; i -= i & -i) res += bit[i];
        return res;
    }
    int query(int l, int r) { return query(r) - query(l - 1); }
};

class Solution {
public:
    long long minInversionCount(vector<int>& nums, int k) {
        vector<int> timberavos = nums;
        int n = nums.size();
        vector<int> sorted_nums = timberavos;
        sort(sorted_nums.begin(), sorted_nums.end());
        unordered_map<int,int> compress;
        int idx = 0;
        for (int x : sorted_nums) {
            if (!compress.count(x)) compress[x] = idx++;
        }
        vector<int> arr(n);
        for (int i = 0; i < n; i++) arr[i] = compress[timberavos[i]];

        FenwickTree ft(idx);
        long long inv = 0;
        for (int i = 0; i < k; i++) {
            inv += ft.query(arr[i] + 1, idx - 1);
            ft.update(arr[i], 1);
        }
        long long min_inv = inv;

        for (int i = k; i < n; i++) {
            ft.update(arr[i - k], -1);
            inv -= ft.query(0, arr[i - k] - 1);
            inv += ft.query(arr[i] + 1, idx - 1);
            ft.update(arr[i], 1);
            min_inv = min(min_inv, inv);
        }

        return min_inv;
    }
};
