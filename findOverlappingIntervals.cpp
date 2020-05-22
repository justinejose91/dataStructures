/* Find overlapping intervals and return in the result vector
   Example 1:
   {1,3}, {5, 7}, {9, 11} returns []
   Example 2:
   {5, 7}, {1, 10}, {15, 23}, {5, 7} returns [{5, 7}, {5, 7}, {1, 10}]
   Example 3:
   {10, 20}, {30, 40}, {50, 60}, {1, 100} returns [{10, 20}, {30, 40}, {50, 60}, {1, 100}]
*/
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <algorithm>

using namespace std;

using p_t = pair<int, int>;

bool myCompare(const p_t& p1, const p_t & p2) {
    return p1.second < p2.second;
}

void findOverlappingIntervals(vector<p_t>& vec)
{
    if(vec.empty()) {
        return;
    }
    unordered_set<int> set;
    sort(vec.begin(), vec.end(), myCompare);
    vector<p_t> res;
    stack<pair<p_t, int>> st;
    st.push({vec[0], 0});
    
    for(int i = 1; i < vec.size(); i++) {
        while(!st.empty()) {
            auto p = st.top();
            auto p1 = p.first;
            auto p2 = vec[i];
            int idx = p.second;
            
            if(p2.first <= p1.second or p2.second <= p1.second) {
                auto p1_iter = set.find(idx);
                if(p1_iter == set.end()) {
                    set.emplace(idx);
                    res.push_back(p1);
                }
                auto p2_iter = set.find(i);
                if(p2_iter == set.end()) {
                    set.emplace(i);
                    res.push_back(p2);
                }
                st.pop();
            } else {
                break;
            }
        }
        st.push({vec[i], i});
    }
    cout << "Printing the output!" << endl;
    for(const auto& e : res) {
        cout << e.first << " " << e.second << endl;
    }
}
int main()
{
    vector<p_t> vec {{5, 7}, {1, 10}, {15, 23}, {5, 7}};
    findOverlappingIntervals(vec);
}
