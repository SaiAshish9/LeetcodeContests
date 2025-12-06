#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        for (int i = 3; 1LL * i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }
    
    bool completePrime(int num) {
        string s = to_string(num);
        int len = s.size();
        for (int i = 1; i <= len; i++) {
            int prefix = stoi(s.substr(0, i));
            if (!isPrime(prefix)) return false;
        }
        for (int i = 0; i < len; i++) {
            int suffix = stoi(s.substr(i));
            if (!isPrime(suffix)) return false;
        }
        return true;
    }
};
