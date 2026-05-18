#include "framework/lc.h"
using namespace std;

// ─── Solution ──────────────────────────────────────────────────────────────
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        string result = "";
        string flag = "";
        for(size_t  i = 0; i < s.length() - 1; i++){
            flag.push_back(s[i]);
            for(size_t j = i+1;j < s.length() - 1;j++){
                if(s[i] != s[j]){
                    flag.push_back(s[j]);
                }else{
                    break;
                }
            }
            if(result.length() < flag.length()){
                result = flag;
                flag = "";
            }else{
                flag = "";
            }
        }
        return result.length();
    }
};

// ─── Test Cases ────────────────────────────────────────────────────────────
int main() {
    Solution sol;
    string s = "abcabcbb";
    int expected = 3;
    lc::test::check("Tên test", sol.lengthOfLongestSubstring(s), expected);
    // lc::test::check_float("Float test", sol.lengthOfLongestSubstring(s), 1.5);

    lc::test::summary();
    return 0;
}
