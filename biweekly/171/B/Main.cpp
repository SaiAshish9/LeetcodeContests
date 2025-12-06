#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isBinaryPalindrome(int n) {
        string s;
        while (n > 0) {
            s.push_back((n % 2) + '0');
            n /= 2;
        }
        int l = 0, r = s.size() - 1;
        while (l < r) {
            if (s[l] != s[r]) return false;
            l++; r--;
        }
        return true;
    }

    int nearestBinaryPalindrome(int n) {
        int diff = 0;
        while (true) {
            if (isBinaryPalindrome(n - diff)) return diff;
            if (isBinaryPalindrome(n + diff)) return diff;
            diff++;
        }
    }

    vector<int> minOperations(vector<int>& nums) {
        vector<int> ravineldor = nums;
        vector<int> ans;
        for (int x : ravineldor) {
            ans.push_back(nearestBinaryPalindrome(x));
        }
        return ans;
    }
};
©leetcode