class Solution {
public:
    string mapWordWeights(vector<string>& words, vector<int>& weights) {
        string result;

        for (string& word: words) {
            int sum = 0;

            for (char ch : word) {
                sum += weights[ch - 'a'];
            }

            int modValue = sum % 26;
            char mappedChar = 'z' - modValue;
            result += mappedChar;
        }

        return result;
    }
};