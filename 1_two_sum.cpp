#include "framework/lc.h"
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;
        for (int i = 0; i < (int)nums.size(); i++) {
            int need = target - nums[i];
            if (seen.count(need)) return {seen[need], i};
            seen[nums[i]] = i;
        }
        return {};
    }
};

int main() {
    Solution sol;

    { vector<int> nums = {2, 7, 11, 15};
      lc::test::check("Basic",     sol.twoSum(nums, 9),  {0, 1}); }

    { vector<int> nums = {3, 2, 4};
      lc::test::check("Middle",    sol.twoSum(nums, 6),  {1, 2}); }

    { vector<int> nums = {3, 3};
      lc::test::check("Duplicate", sol.twoSum(nums, 6),  {0, 1}); }

    lc::test::summary();
    return 0;
}
