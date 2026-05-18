#include "framework/lc.h"
using namespace std;

// ─── Solution ──────────────────────────────────────────────────────────────
class Solution
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size();
        int n = nums2.size();
        vector<int> merged;
        merged.reserve(m + n);
        double result;
        int i = 0;
        int j = 0;
        while (i < m && j < n)
        {
            if (nums1[i] <= nums2[j])
            {
                merged.push_back(nums1[i]);
                i++;
            }
            else
            {
                merged.push_back(nums2[j]);
                j++;
            }
        }
        while (i < m) {
            merged.push_back(nums1[i]);
            i++;
        }
        while (j < n) {
            merged.push_back(nums2[j]);
            j++;
        }
        int median = (m + n) / 2;
        if ((m + n) % 2 == 0)
        {
            result = (double)(merged[median] + merged[median - 1]) / 2;
        }
        else
        {
            result = merged[median];
        }
        return result;
    }
};

// ─── Test Cases ────────────────────────────────────────────────────────────
int main()
{
    Solution sol;

    vector<int> t1_nums1 = {1, 3};
    vector<int> t1_nums2 = {2};
    lc::test::check("test 1", sol.findMedianSortedArrays(t1_nums1, t1_nums2), 2.00000);

    vector<int> t2_nums1 = {1, 2};
    vector<int> t2_nums2 = {3, 4};
    lc::test::check("test 2", sol.findMedianSortedArrays(t2_nums1, t2_nums2), 2.50000);

    lc::test::summary();
    return 0;
}
