# LeetCode C++ Framework

Bộ khung chạy test case local cho LeetCode bằng C++.

## Yêu cầu

- **g++** với hỗ trợ C++17 (MinGW-w64 trên Windows)
- **PowerShell** hoặc **Command Prompt (cmd)** — dùng được cả hai

Kiểm tra g++ đã cài chưa:
```
g++ --version
```

---

## Bắt đầu nhanh

### 1. Tạo file bài mới

```powershell
./new.ps1 1_two_sum
```

Lệnh này copy `template.cpp` thành `1_two_sum.cpp` và tự mở editor.

### 2. Viết solution + test

```cpp
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
      lc::test::check("Basic",     sol.twoSum(nums, 9), {0, 1}); }

    { vector<int> nums = {3, 3};
      lc::test::check("Duplicate", sol.twoSum(nums, 6), {0, 1}); }

    lc::test::summary();
    return 0;
}
```

### 3. Chạy

**PowerShell:**
```powershell
./run.ps1 1_two_sum   # chạy theo tên
./run.ps1 1           # chạy theo số bài (tìm 1_*.cpp)
./run.ps1             # chạy file .cpp mới nhất
```

**Command Prompt (cmd):**
```cmd
run 1_two_sum
run 1
run
```

Output:
```
Compiling 1_two_sum.cpp ...
Running...

[PASS] Basic
[PASS] Duplicate

─────────────────────────────
Result: 2 passed
─────────────────────────────
```

Nếu fail:
```
[FAIL] Basic
       expected: [0, 1]
       got:      [1, 0]
```

---

## Cấu trúc thư mục

```
leetcode/
├── framework/
│   └── lc.h          # header duy nhất, include vào mọi bài
├── template.cpp      # template khi tạo bài mới
├── run.ps1           # compile & chạy (PowerShell)
├── run.bat           # compile & chạy (cmd)
├── new.ps1           # tạo file mới (PowerShell)
├── new.bat           # tạo file mới (cmd)
└── 1_two_sum.cpp     # ví dụ
```

---

## Dùng PowerShell hay cmd?

Cả hai đều hỗ trợ đầy đủ, cú pháp khác nhau chút:

| Thao tác | PowerShell | cmd |
|---|---|---|
| Tạo bài mới | `./new.ps1 146_lru_cache` | `new 146_lru_cache` |
| Chạy theo tên | `./run.ps1 146_lru_cache` | `run 146_lru_cache` |
| Chạy theo số | `./run.ps1 146` | `run 146` |
| Chạy bài mới nhất | `./run.ps1` | `run` |

> **Lưu ý về màu sắc:** Màu ANSI hiển thị đúng trong **Windows Terminal** và **VS Code terminal**. Trong cmd cổ điển (conhost) màu có thể không hiển thị nhưng output vẫn đọc được.

---

## API Reference

### Test Runner

```cpp
lc::test::check("tên test", got, expected);
```

So sánh `got` và `expected`. Hỗ trợ mọi kiểu: `int`, `bool`, `string`, `vector<int>`, `vector<vector<int>>`, `pair<int,int>`, `ListNode*`, `TreeNode*`.

```cpp
lc::test::check_float("tên test", got, expected);          // eps mặc định 1e-5
lc::test::check_float("tên test", got, expected, 1e-3);    // eps tuỳ chỉnh
```

Dùng cho bài trả về `double` / `float`.

```cpp
lc::test::summary();
```

In tổng số pass/fail. **Luôn gọi cuối `main()`**.

---

### Linked List

```cpp
// Tạo list từ initializer list
ListNode* head = lc::make_list({1, 2, 3, 4, 5});
// → 1 -> 2 -> 3 -> 4 -> 5

// Chuyển về vector để so sánh
vector<int> result = lc::list_to_vec(head);

// So sánh kết quả trả về ListNode*
lc::test::check("Reverse", lc::list_to_vec(sol.reverseList(head)), {5,4,3,2,1});
```

**Mẫu test bài Linked List:**
```cpp
int main() {
    Solution sol;

    { auto head = lc::make_list({1,2,3,4,5});
      lc::test::check("Odd length", lc::list_to_vec(sol.reverseList(head)), {5,4,3,2,1}); }

    { auto head = lc::make_list({1,2});
      lc::test::check("Two nodes", lc::list_to_vec(sol.reverseList(head)), {2,1}); }

    lc::test::summary();
}
```

---

### Binary Tree

```cpp
// N là hằng số null, dùng khi node không tồn tại
// Layout: level-order (BFS), giống LeetCode
TreeNode* root = lc::make_tree({3, 9, 20, N, N, 15, 7});
//       3
//      / \
//     9  20
//       /  \
//      15   7

// Chuyển về vector để so sánh (level-order, bỏ null cuối)
vector<int> result = lc::tree_to_vec(root);
// → {3, 9, 20, N, N, 15, 7}

// So sánh cây
lc::test::check("Invert tree",
    lc::tree_to_vec(sol.invertTree(root)),
    lc::tree_to_vec(lc::make_tree({3,20,9,7,15})));
```

**Cách đọc level-order:** đọc từ trái sang phải, từng tầng một. `N` là node bị thiếu.

```
make_tree({1, 2, 3, N, 5})

       1
      / \
     2   3
      \
       5
```

---

### Utility

```cpp
// Sắp xếp vector trước khi so sánh (khi thứ tự không quan trọng)
lc::test::check("Two Sum",
    lc::sorted(sol.twoSum(nums, 9)),
    lc::sorted(vector<int>{0, 1}));

// Sắp xếp vector 2D (VD: bài tìm tất cả tổ hợp)
lc::test::check("Subsets",
    lc::sorted2d(sol.subsets(nums)),
    lc::sorted2d(expected));

// In bất kỳ kiểu ra string (debug)
cout << lc::str(vec);          // [1, 2, 3]
cout << lc::str(head);         // [1 -> 2 -> 3]
cout << lc::str(root);         // [3, 9, 20, null, null, 15, 7]
cout << lc::str(make_pair(1,2)); // (1, 2)
```

---

## Ví dụ theo dạng bài

### Array / String

```cpp
int main() {
    Solution sol;

    lc::test::check("Example 1", sol.maxProfit({7,1,5,3,6,4}), 5);
    lc::test::check("Example 2", sol.maxProfit({7,6,4,3,1}),   0);
    lc::test::check("Edge: empty", sol.maxProfit({}),           0);

    lc::test::summary();
}
```

### Bài trả về vector không quan tâm thứ tự

```cpp
int main() {
    Solution sol;

    // dùng sorted() khi output có thể có nhiều thứ tự đúng
    lc::test::check("Example 1",
        lc::sorted(sol.twoSum({2,7,11,15}, 9)),
        lc::sorted(vector<int>{0,1}));

    lc::test::summary();
}
```

### Bài trả về double

```cpp
int main() {
    Solution sol;

    lc::test::check_float("Example 1", sol.findMedian({1,3},   {2}),   2.0);
    lc::test::check_float("Example 2", sol.findMedian({1,2},   {3,4}), 2.5);

    lc::test::summary();
}
```

### Bài modify in-place

```cpp
int main() {
    Solution sol;

    { vector<int> nums = {1,1,2};
      int k = sol.removeDuplicates(nums);
      lc::test::check("Length", k, 2);
      lc::test::check("Values", vector<int>(nums.begin(), nums.begin()+k), {1,2}); }

    lc::test::summary();
}
```

---

## Lưu ý

- Luôn đặt `using namespace std;` **sau** `#include "framework/lc.h"` (không phải trước).
- Mỗi test case nên wrap trong `{ }` để tránh xung đột biến cùng tên.
- `lc::test::summary()` phải là dòng cuối cùng trong `main()`.
- File `.exe` sau khi compile nằm cùng thư mục — có thể bỏ qua trong `.gitignore`.

```gitignore
*.exe
*.o
```
