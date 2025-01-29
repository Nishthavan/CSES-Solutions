#include<iostream>
#include<climits>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;

int main(){
    int comp, conn;
    cin>>comp>>conn;
    comp++;
    vector<vector<int> > graph(comp, vector<int>());
    vector<vector<ll> > flows(comp, vector<ll>(comp, 0));
    for(int i=0; i<conn; i++){
        int x, y, z; cin>>x>>y>>z;
        graph[x].push_back(y);
        graph[y].push_back(x);
        flows[x][y] += z;
    }
    vector<int> parentConn(comp, -1);
    auto getFlow = [&]() -> ll{
        for(int i=0; i<comp; i++){ parentConn[i] = -1;}
        parentConn[1] = INT_MIN;
        queue<pair<int, ll>> bfs;
        bfs.push({1, LLONG_MAX});
        while(!bfs.empty()){
            auto [node, speed] = bfs.front(); bfs.pop();
            for(auto nghb: graph[node]){
                if(parentConn[nghb] == -1 && flows[node][nghb]){
                    parentConn[nghb] = node;
                    ll newspeed = min(speed, flows[node][nghb]);
                    if(nghb == comp - 1) return newspeed;
                    bfs.push({nghb, newspeed});
                }
            }
        }
        return 0LL;
    };
    ll maxSpeed = 0, currSpeed = 0;
    while((currSpeed = getFlow())){
        maxSpeed += currSpeed;
        int curr = comp - 1;
        while(curr != 1){
            int parent = parentConn[curr];
            flows[parent][curr] -= currSpeed;
            flows[curr][parent] += currSpeed;
            curr = parent;
        }
    }
    cout<<maxSpeed;
    return 0;
}
