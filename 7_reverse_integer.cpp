#include "framework/lc.h"
using namespace std;

// ─── Solution ──────────────────────────────────────────────────────────────
class Solution {
public:
  int reverse(int x) {
    int result = 0;
    while (x != 0) {
      int digit = x % 10;
      if (result > INT_MAX / 10 ||
          (result == INT_MAX / 10 && digit > INT_MAX % 10))
        return 0;
      if (result < INT_MIN / 10 ||
          (result == INT_MIN / 10 && digit < INT_MIN % 10))
        return 0;
      result = result * 10 + digit;
      x /= 10;
    }
    return result;
  }
};
// ─── Test Cases ────────────────────────────────────────────────────────────
int main() {
  Solution sol;
  lc::test::check("test 1", sol.reverse(123), 321);
  lc::test::check("test 2", sol.reverse(-123), -321);
  lc::test::check("test 3", sol.reverse(120), 21);
  lc::test::check("test 4", sol.reverse(0), 0);
  lc::test::check("test 5", sol.reverse(1), 1);
  lc::test::check("test 6", sol.reverse(-1), -1);
  lc::test::check("test 7", sol.reverse(10), 1);
  lc::test::check("test 8", sol.reverse(-10), -1);
  lc::test::check("test 9", sol.reverse(100), 1);
  lc::test::check("test 10", sol.reverse(-100), -1);
  lc::test::check("test 11", sol.reverse(12345), 54321);
  lc::test::check("test 12", sol.reverse(-12345), -54321);
  lc::test::check("test 13", sol.reverse(1534236469), 0);
  lc::test::check("test 14", sol.reverse(2147483647), 0);
  lc::test::check("test 15", sol.reverse(-2147483648), 0);

  lc::test::summary();
  return 0;
}
