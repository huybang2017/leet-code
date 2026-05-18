#pragma once

// windows.h phải đến TRƯỚC bits/stdc++.h, và không dùng using namespace std trong header
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif

#include <bits/stdc++.h>

// ─── ANSI Colors ───────────────────────────────────────────────────────────
#define LC_GREEN  "\033[92m"
#define LC_RED    "\033[91m"
#define LC_YELLOW "\033[93m"
#define LC_CYAN   "\033[96m"
#define LC_BOLD   "\033[1m"
#define LC_DIM    "\033[2m"
#define LC_RESET  "\033[0m"

// ─── LeetCode Data Structures ──────────────────────────────────────────────
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = 0) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* n) : val(x), next(n) {}
};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x = 0) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), left(l), right(r) {}
};

// Null marker cho make_tree: make_tree({1, 2, N, 3})
const int N = INT_MIN;

namespace lc {

// ─── Stringify ─────────────────────────────────────────────────────────────
inline std::string str(int x)                { return std::to_string(x); }
inline std::string str(long long x)          { return std::to_string(x); }
inline std::string str(double x)             { std::ostringstream s; s << x; return s.str(); }
inline std::string str(bool x)               { return x ? "true" : "false"; }
inline std::string str(char x)               { return std::string(1, x); }
inline std::string str(const std::string& x) { return "\"" + x + "\""; }

template<typename T>
std::string str(const std::vector<T>& v) {
    std::string s = "[";
    for (int i = 0; i < (int)v.size(); i++) {
        if (i) s += ", ";
        s += str(v[i]);
    }
    return s + "]";
}

template<typename A, typename B>
std::string str(const std::pair<A, B>& p) {
    return "(" + str(p.first) + ", " + str(p.second) + ")";
}

inline std::string str(ListNode* head) {
    if (!head) return "[]";
    std::string s;
    while (head) {
        if (!s.empty()) s += " -> ";
        s += std::to_string(head->val);
        head = head->next;
    }
    return "[" + s + "]";
}

inline std::string str(TreeNode* root) {
    if (!root) return "[]";
    std::string s = "[";
    std::queue<TreeNode*> q;
    q.push(root);
    int pending = 0;
    bool first = true;
    while (!q.empty()) {
        auto node = q.front(); q.pop();
        if (!node) { pending++; continue; }
        while (pending-- > 0) { if (!first) s += ", "; s += "null"; first = false; }
        pending = 0;
        if (!first) s += ", ";
        s += std::to_string(node->val);
        first = false;
        q.push(node->left);
        q.push(node->right);
    }
    return s + "]";
}

// ─── List helpers ──────────────────────────────────────────────────────────
inline ListNode* make_list(std::initializer_list<int> vals) {
    ListNode dummy;
    ListNode* cur = &dummy;
    for (int v : vals) { cur->next = new ListNode(v); cur = cur->next; }
    return dummy.next;
}

inline std::vector<int> list_to_vec(ListNode* head) {
    std::vector<int> res;
    while (head) { res.push_back(head->val); head = head->next; }
    return res;
}

// ─── Tree helpers ──────────────────────────────────────────────────────────
// Level-order, dùng N (=INT_MIN) cho node null
// VD: make_tree({3, 9, 20, N, N, 15, 7})
inline TreeNode* make_tree(std::vector<int> vals) {
    if (vals.empty() || vals[0] == N) return nullptr;
    std::queue<TreeNode*> q;
    auto root = new TreeNode(vals[0]);
    q.push(root);
    for (int i = 1; i < (int)vals.size(); ) {
        auto node = q.front(); q.pop();
        if (i < (int)vals.size() && vals[i] != N) {
            node->left = new TreeNode(vals[i]);
            q.push(node->left);
        }
        i++;
        if (i < (int)vals.size() && vals[i] != N) {
            node->right = new TreeNode(vals[i]);
            q.push(node->right);
        }
        i++;
    }
    return root;
}

inline std::vector<int> tree_to_vec(TreeNode* root) {
    std::vector<int> res;
    if (!root) return res;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        auto node = q.front(); q.pop();
        if (!node) { res.push_back(N); continue; }
        res.push_back(node->val);
        q.push(node->left);
        q.push(node->right);
    }
    while (!res.empty() && res.back() == N) res.pop_back();
    return res;
}

// ─── Utility ───────────────────────────────────────────────────────────────
template<typename T>
std::vector<T> sorted(std::vector<T> v) { std::sort(v.begin(), v.end()); return v; }

template<typename T>
std::vector<std::vector<T>> sorted2d(std::vector<std::vector<T>> v) {
    for (auto& row : v) std::sort(row.begin(), row.end());
    std::sort(v.begin(), v.end());
    return v;
}

// ─── Test Runner ───────────────────────────────────────────────────────────
namespace test {
    static int _pass = 0, _fail = 0;

    inline void _enable_color() {
#ifdef _WIN32
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode = 0;
        GetConsoleMode(h, &mode);
        SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
    }

    template<typename T>
    void check(const std::string& name, T got, T expected) {
        static bool _init = (_enable_color(), true);
        (void)_init;
        if (got == expected) {
            std::cout << LC_GREEN "[PASS]" LC_RESET " " << name << "\n";
            _pass++;
        } else {
            std::cout << LC_RED "[FAIL]" LC_RESET " " << name << "\n"
                      << "       " LC_YELLOW "expected:" LC_RESET " " << str(expected) << "\n"
                      << "       " LC_YELLOW "got:     " LC_RESET " " << str(got) << "\n";
            _fail++;
        }
    }

    inline void check_float(const std::string& name, double got, double expected, double eps = 1e-5) {
        if (std::abs(got - expected) <= eps) {
            std::cout << LC_GREEN "[PASS]" LC_RESET " " << name << "\n";
            _pass++;
        } else {
            std::cout << LC_RED "[FAIL]" LC_RESET " " << name << "\n"
                      << "       " LC_YELLOW "expected:" LC_RESET " " << expected << "\n"
                      << "       " LC_YELLOW "got:     " LC_RESET " " << got << "\n";
            _fail++;
        }
    }

    inline void summary() {
        std::cout << LC_DIM "\n─────────────────────────────\n" LC_RESET;
        if (_fail == 0)
            std::cout << LC_BOLD "Result: " LC_GREEN << _pass << " passed" LC_RESET "\n";
        else
            std::cout << LC_BOLD "Result: " LC_GREEN << _pass << " passed" LC_RESET
                      << "  " LC_RED << _fail << " failed" LC_RESET "\n";
        std::cout << LC_DIM "─────────────────────────────\n" LC_RESET;
    }
}

} // namespace lc
