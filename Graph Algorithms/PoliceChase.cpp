#include<iostream>
#include<climits>
#include<queue>
#include<unordered_set>
using namespace std;
typedef long long ll;
int main(){
    int nodes, streets;
    cin >> nodes >> streets; nodes++;
    vector<vector<int>> adjList(nodes);
    vector<vector<bool>> flow(nodes, vector<bool>(nodes, false));
    vector<pair<int, int>> edges;
    unordered_set<int> set1 = {1}, set2;
    for(int i = 1; i < nodes; i++) set2.insert(i);
    while(streets--){
        int a, b; cin >> a >> b;
        edges.emplace_back(a, b);
        adjList[a].push_back(b);
        adjList[b].push_back(a);
        flow[a][b] = flow[b][a] = true;
    }
    vector<int> parent(nodes, -1);

    // if a path is possible or not
    auto PathPossible = [&]() -> bool {
        fill(parent.begin(), parent.end(), -1);
        queue<int> bfs({1});
        parent[1] = INT_MIN;
        while(!bfs.empty()){
            int node = bfs.front(); bfs.pop();
            for(int ngb : adjList[node])
                if(parent[ngb] == -1 && flow[node][ngb]){
                    parent[ngb] = node;
                    if(ngb == nodes - 1) return true;
                    bfs.push(ngb);
                }
        }
        return false;
    };

    // What is the max flow ? 
    int minCut = 0;
    while(PathPossible()){
        minCut++;
        for(int curr = nodes - 1; curr != 1; curr = parent[curr])
            flow[parent[curr]][curr] = false, flow[curr][parent[curr]] = true;
    }

    //  Get the Mincut in the graph....
    queue<int> bfs({1});
    while(!bfs.empty()){
        int node = bfs.front(); bfs.pop();
        for(int ngb : adjList[node])
            if(flow[node][ngb] && set2.erase(ngb)) bfs.push(ngb), set1.insert(ngb);
    }
    cout << minCut << endl;
    for(auto &[a, b] : edges)
        if(set1.count(a) != set1.count(b)) cout << a << " " << b << endl;
    
    return 0;
}