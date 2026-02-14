class Solution {
public:
    long long rob(vector<int>& nums, vector<int>& colors) {
        int n = nums.size();

        if (n == 0) return 0;
        if (n == 1) return nums[0];

        long long prev2 = 0;
        long long prev1 = nums[0];

        for (int i = 1; i < n; i++) {
            long long take;

            if (colors[i] != colors[i-1]) {
                take = prev1;
            } else {
                take = prev2;
            }

            take += nums[i];
            
            long long curr = max(prev1, take);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};