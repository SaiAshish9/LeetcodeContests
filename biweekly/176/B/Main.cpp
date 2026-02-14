class Solution {
public:
    int prefixConnected(vector<string>& words, int len) {
        vector<string> tempStore = words;

        unordered_map<string, int> prefixCount;

        for (string &str: tempStore) {
            if (str.size() < len) continue;

            string prefix = str.substr(0, len);
            prefixCount[prefix]++;
        }

        int result = 0;

        for (auto &entry: prefixCount) {
            if (entry.second >= 2) {
                result++;
            }
        }

        return result;
        
    }
};