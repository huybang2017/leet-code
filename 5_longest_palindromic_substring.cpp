#include "framework/lc.h"
using namespace std;

// ─── Solution ──────────────────────────────────────────────────────────────
class Solution
{
public:
    string longestPalindrome(string s)
    {
        string ans = "";
        for (size_t i = 0; i < s.size(); i++)
        {
            string s1 = expand(s, i, i);
            string s2 = expand(s, i, i + 1);
            if (s1.size() > ans.size()) ans = s1;
            if (s2.size() > ans.size()) ans = s2;
        }
        return ans;
    }
    string expand(string &s, int left, size_t right)
    {
        while (left >= 0 && right < s.size() && s[left] == s[right])
        {
            left--;
            right++;
        }
        return s.substr(left + 1, right - left - 1);
    }
};

// ─── Test Cases ────────────────────────────────────────────────────────────
int main()
{
    Solution sol;
    string s_test1 = "babab";
    string expected1 = "babab";
    string s_test2 = "dbbd";
    string expected2 = "dbbd";
    lc::test::check("test 1", sol.longestPalindrome(s_test1), expected1);
    lc::test::check("test 2", sol.longestPalindrome(s_test2), expected2);
    lc::test::summary();
    return 0;
}
