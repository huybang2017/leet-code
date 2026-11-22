#include "framework/lc.h"
using namespace std;

// ─── Solution ──────────────────────────────────────────────────────────────
class Solution {
public:
    int myAtoi(string s) {
        boost::trim(s);
    }
};

// ─── Test Cases ────────────────────────────────────────────────────────────
int main() {
    Solution sol;

    // Basic
    lc::test::check("Basic positive", sol.myAtoi("42"), 42);
    lc::test::check("Basic negative", sol.myAtoi("-42"), -42);
    lc::test::check("Leading spaces", sol.myAtoi("   42"), 42);
    lc::test::check("Leading spaces negative", sol.myAtoi("   -42"), -42);

    // Sign
    lc::test::check("Plus sign", sol.myAtoi("+42"), 42);
    lc::test::check("Minus sign", sol.myAtoi("-42"), -42);
    lc::test::check("Plus with spaces", sol.myAtoi("   +42"), 42);
    lc::test::check("Minus with spaces", sol.myAtoi("   -42"), -42);

    // Characters after number
    lc::test::check("Number followed by text", sol.myAtoi("4193 with words"), 4193);
    lc::test::check("Text after negative number", sol.myAtoi("-4193 with words"), -4193);
    lc::test::check("Number followed by letters", sol.myAtoi("42abc"), 42);

    // Invalid input
    lc::test::check("Text only", sol.myAtoi("words and 987"), 0);
    lc::test::check("Text before number", sol.myAtoi("abc42"), 0);
    lc::test::check("Empty string", sol.myAtoi(""), 0);
    lc::test::check("Only spaces", sol.myAtoi("     "), 0);

    // Invalid sign usage
    lc::test::check("Plus minus", sol.myAtoi("+-12"), 0);
    lc::test::check("Minus plus", sol.myAtoi("-+12"), 0);
    lc::test::check("Multiple plus", sol.myAtoi("++12"), 0);
    lc::test::check("Multiple minus", sol.myAtoi("--12"), 0);

    // Leading zeros
    lc::test::check("Leading zeros", sol.myAtoi("00042"), 42);
    lc::test::check("Negative leading zeros", sol.myAtoi("-00042"), -42);
    lc::test::check("Plus leading zeros", sol.myAtoi("+00042"), 42);

    // Zero
    lc::test::check("Zero", sol.myAtoi("0"), 0);
    lc::test::check("Negative zero", sol.myAtoi("-0"), 0);
    lc::test::check("Positive zero", sol.myAtoi("+0"), 0);
    lc::test::check("Zero with text", sol.myAtoi("0abc"), 0);

    // INT_MAX boundary
    lc::test::check(
        "INT_MAX",
        sol.myAtoi("2147483647"),
        2147483647
    );

    lc::test::check(
        "INT_MAX overflow",
        sol.myAtoi("2147483648"),
        2147483647
    );

    lc::test::check(
        "Large positive overflow",
        sol.myAtoi("999999999999999999999"),
        2147483647
    );

    // INT_MIN boundary
    lc::test::check(
        "INT_MIN",
        sol.myAtoi("-2147483648"),
        -2147483648
    );

    lc::test::check(
        "INT_MIN underflow",
        sol.myAtoi("-2147483649"),
        -2147483648
    );

    lc::test::check(
        "Large negative overflow",
        sol.myAtoi("-999999999999999999999"),
        -2147483648
    );

    // Spaces around / after number
    lc::test::check(
        "Trailing spaces",
        sol.myAtoi("42   "),
        42
    );

    lc::test::check(
        "Spaces after negative",
        sol.myAtoi("-42   "),
        -42
    );

    // Decimal / special characters
    lc::test::check(
        "Decimal",
        sol.myAtoi("42.5"),
        42
    );

    lc::test::check(
        "Special character",
        sol.myAtoi("42#123"),
        42
    );

    lc::test::check(
        "Tab before number",
        sol.myAtoi("\t42"),
        0
    );

    // Important LeetCode edge cases
    lc::test::check(
        "Whitespace then sign then text",
        sol.myAtoi("   -words"),
        0
    );

    lc::test::check(
        "Whitespace sign no number",
        sol.myAtoi("   +"),
        0
    );

    lc::test::check(
        "Whitespace negative no number",
        sol.myAtoi("   -"),
        0
    );

    lc::test::check(
        "Sign followed by spaces",
        sol.myAtoi("+ 42"),
        0
    );

    lc::test::check(
        "Number then sign",
        sol.myAtoi("42+12"),
        42
    );

    lc::test::summary();
    return 0;
}