#include "framework/lc.h"
using namespace std;

// ─── Solution ──────────────────────────────────────────────────────────────
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> set;
        int left = 0;
        int maxLen = 0;
        for(int right = 0; right < (int)s.length(); right++) {
            while(set.count(s[right])) {
                set.erase(s[left]);
                left++;
            }
            set.insert(s[right]);
            maxLen = max(maxLen, right - left + 1);
        }
        return maxLen;
    }
};

// ─── Test Cases ────────────────────────────────────────────────────────────
int main() {
    Solution sol;
    string s1 = "abcabcbb";
    int expected1 = 3;
    string s2 = "bbbbb";
    int expected2 = 1;
    string s3 = "pwwkew";
    int expected3 = 3;
    lc::test::check("Tên test", sol.lengthOfLongestSubstring(s1), expected1);
    lc::test::check("Tên test", sol.lengthOfLongestSubstring(s2), expected2);
    lc::test::check("Tên test", sol.lengthOfLongestSubstring(s3), expected3);
    // lc::test::check_float("Float test", sol.lengthOfLongestSubstring(s1), 1.5);

    lc::test::summary();
    return 0;
}
