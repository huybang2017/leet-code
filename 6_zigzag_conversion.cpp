#include "framework/lc.h"
using namespace std;

// ─── Solution ──────────────────────────────────────────────────────────────
class Solution
{
public:
    string convert(string s, int numRows)
    {
        if (numRows == 1)
            return s;
        vector<string> zigzagString(numRows);
        int currentRow = 0;
        bool directionGoDown = false;
        string result;
        for (char c : s)
        {
            zigzagString[currentRow] += c;
            if (currentRow == 0 || currentRow == numRows - 1)
            {
                directionGoDown = !directionGoDown;
            }
            currentRow += directionGoDown ? 1 : -1;
        }
        for (string row : zigzagString)
        {
            result += row;
        }
        return result;
    }
};

// ─── Test Cases ────────────────────────────────────────────────────────────
int main()
{
    Solution sol;
    string s_test1 = "PAYPALISHIRING";
    int numRows_test1 = 3;
    string expected1 = "PAHNAPLSIIGYIR";
    lc::test::check("test 1", sol.convert(s_test1, numRows_test1), expected1);

    string s_test2 = "PAYPALISHIRING";
    int numRows_test2 = 4;
    string expected2 = "PINALSIGYAHRPI";
    lc::test::check("test 2", sol.convert(s_test2, numRows_test2), expected2);

    string s_test3 = "A";
    int numRows_test3 = 1;
    string expected3 = "A";
    lc::test::check("test 3", sol.convert(s_test3, numRows_test3), expected3);

    lc::test::summary();
    return 0;
}
