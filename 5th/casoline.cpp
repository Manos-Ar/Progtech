#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <set>
#include <queue>
#include <functional>

using namespace std;

auto mycomparator(const pair<int,int>& p1, const pair<int,int>& p2){
    return p1.second < p2.second;
}


class Graph{
    public:
        Graph(int n,int m):N(n),M(m),adj(N){};
        void add_edge(int u, int v, int l){
            adj[u].push_back(make_pair(v,l));
        }
        void add_Q(int q){
            Q=q;
        }
        void add_goals(int a, int b, int c){
            goals.push_back(make_tuple(a,b,c));
        }

        void run(){
            for(int i=0; i<Q; i++){
                cout<<"goal "<<i<<" starts\n";
                results.push_back(dijkstra(i));
            }
        }

        void print(){
            int count=0,fills;
            // vector<int> *path;
            for(int i=0; i<Q; i++){
                if(results[i]){
                    cout<<"POSSIBLE: ";
                    fills=valid_results[count].first;
                    // path=&valid_results[count].second;
                    cout<<fills<<" fill(s),";
                    for(int j=valid_results[count].second.size()-1;j>=0; j--)
                        cout<<" "<<valid_results[count].second[j];
                    cout<<endl;
                }
                else
                    cout<<"IMPOSSIBLE\n";
            }
        }

        bool dijkstra(int g){
            int a,b,c, fuel,fuel_remain,parent_node,target_node,distance,count;
            vector<int> parent(N,-1);
            vector<int> fills(N,-1);
            set<int> close;
            pair<int,int> temp{0,0};

            a=get<0>(goals[g]);
            b=get<1>(goals[g]);
            c=get<2>(goals[g]);
            close.insert(a);
            fills[a]=0;

            priority_queue<pair<int,int>,vector<pair<int,int>>,std::function<bool(pair<int,int>, pair<int,int>)>> queue(mycomparator);
            for(unsigned int i=0; i<adj[a].size(); i++){
                distance=adj[a][i].second;
                fuel=c-distance;
                target_node=adj[a][i].first;
                if(fuel>0){
                    queue.push(make_pair(target_node,fuel));
                    parent[target_node]=a;
                    fills[target_node]=0;
                    close.insert(target_node);
                }
            }
            if(queue.size()==0){
                return false;
            }
            while(close.size()!=(unsigned int)N || queue.size()==0){
                
                temp=queue.top();
                parent_node=temp.first;
                fuel=temp.second;
                count=fills[parent_node];

                for(unsigned int i=0; i<adj[parent_node].size();i++){
                    target_node=adj[parent_node][i].first;
                    distance=adj[parent_node][i].second;
                    fuel_remain=fuel-distance;

                    if(close.find(target_node)==close.end())
                        continue;

                    if(fuel_remain>0){
                        queue.push(make_pair(target_node,fuel_remain));
                        parent[target_node]=parent_node;
                        fills[target_node]=count;
                        close.insert(target_node);
                    }
                    else if(c-distance>0){
                        fuel_remain=c-distance;
                        queue.push(make_pair(target_node,fuel_remain));
                        parent[target_node]=parent_node;
                        fills[target_node]=count+1;
                        close.insert(target_node);
                    }
                }
            }

            if(parent[b]==-1){
                return false;
            }
            else{
                vector<int> path;
                count=fills[b];
                parent_node=parent[b];
                path.push_back(parent_node);
                while(parent_node!=a){
                    parent_node=parent[parent_node];
                    path.push_back(parent_node);
                }
                valid_results.push_back(make_pair(count,path));
            }
            return true;
        }

    private:
        int N,M,Q;
        vector<vector<pair<int,int>>> adj;
        vector<tuple<int,int,int>> goals;
        vector<pair<int,vector<int>>> valid_results;
        vector<bool> results;
};

int main(){
    int N,M,a,b,c,Q;
    cin >>N>>M;
    Graph graph(N,M);
    for(int i=0; i<M; i++){
        cin >>a>>b>>c;
        graph.add_edge(a,b,c);
    }
    cin >>Q;
    graph.add_Q(Q);
    for(int i=0; i<Q; i++){
        cin >>a>>b>>c;
        graph.add_goals(a,b,c);
    }
    cout<<"read\n";
    graph.run();
    graph.print();
}