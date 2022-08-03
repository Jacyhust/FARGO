#pragma once
// Test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <map>
using namespace std;

namespace nowcoder_2_longestRoute
{
    class Solution {
    public:
        /**
         * 返回最终结果
         * @param n int整型 城市数量
         * @param u int整型vector
         * @param v int整型vector
         * @param w int整型vector
         * @return long长整型
         */
        struct pairs
        {
            int to;
            int cost;
        };
        vector<int> dist;
        vector<bool> vis;
        vector<vector<pairs>> link;
        long long solve(int n, vector<int>& u, vector<int>& v, vector<int>& w) {
            // write code here
            dist.resize(n + 1);
            vis.resize(n + 1);
            int res = 0;
            pairs p0;
            link.resize(n + 1);
            for (int i = 0; i < n - 1; ++i) {
                p0.cost = w[i];
                p0.to = u[i];
                link[v[i]].push_back(p0);
                p0.to = v[i];
                link[u[i]].push_back(p0);
            }

            for (int i = 1; i < n + 1; ++i) {
                for (int k = 0; k < n + 1; ++k) {
                    dist[k] = 0;
                    vis[k] = false;
                }
                dfs(i);
                for (int j = 1; j < n + 1; ++j) {
                    res = max(res, dist[j]);
                }
            }
            return res;
        }

        void dfs(int i) {
            vis[i] = true;
            for (int j = 0; j < link[i].size(); ++j) {

                int w = link[i][j].to;
                if (vis[w]) continue;
                dist[w] = max(dist[w], dist[i] + link[i][j].cost);
                dfs(w);
            }
        }
    };

    void test()
    {
        int n = 7;
        vector<int> u = { 2, 3, 5, 4, 5, 5 }, v = { 5, 2, 1, 6, 7, 4 }, w = { 15, 6, 14, 4, 1, 6 };
        Solution s;
        cout << s.solve(n, u, v, w) << endl;
    }
}

int main1()
{
    nowcoder_2_longestRoute::test();
    std::cout << "Hello World!\n";
}

