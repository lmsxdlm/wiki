#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;struct ta {int lfanwei;int rfanwei;int shanghai;};
ta TA[10005];
struct ga {int Brontime;int hp;int zuobiao = 0;};
ga GA[10005];
vector<int> st[10005]; int main() {int n, m;for (int i = 0; i < n; i++) {cin >> TA[i].lfanwei >> TA[i].rfanwei >> TA[i].shanghai;}
    for (int i = 0; i < m; i++) {
        cin >> GA[i].Brontime >> GA[i].hp >> GA[i].zuobiao;}int max_time = 20000; for (int t = 0; t <= max_time; t++) {for (int j = 0; j < m; j++) {
            if (GA[j].Brontime <= t && GA[j].hp > 0) {
                GA[j].zuobiao += 1;}}for (int k = 0; k < n; k++) {for (int j = 0; j < m; j++) {if (GA[j].Brontime > t) continue;
                bool in_range = (GA[j].zuobiao >= TA[k].lfanwei && GA[j].zuobiao <= TA[k].rfanwei && GA[j].hp > 0);
                auto it = find(st[k].begin(), st[k].end(), j);if (in_range) {if (it == st[k].end()) {st[k].insert(st[k].begin(), j); 
}} else {if (it != st[k].end()) {st[k].erase(it);}}}}
        for (int k = 0; k < n; k++) {if (!st[k].empty()) {int target_id = st[k][0];GA[target_id].hp -= TA[k].shanghai;}}}return 0;
}