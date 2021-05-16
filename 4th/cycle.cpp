#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Graph{
    public:
        Graph(int V):_V(V){
            adj.resize(V);
        };

        ~Graph(){
            adj.clear();
        }

        void addEdge(int u, int v){
            adj[u].insert(v);
        }

        void order(vector<int> &v, set<int> &s) const{
            auto it=s.begin();
            set<int>::iterator at;
            v.push_back(*it);
            while(!s.empty()){
                if(s.size()==1){
                    break;
                }
                for(at=adj[*it].begin(); at!=adj[*it].end(); ++at){
                    if(s.find(*at)!=s.end()){
                        v.push_back(*at);
                        s.erase(*it);
                        it=at;
                        break;
                    }
                }   
            }
        }

        void remove(vector<int> &path) const{
            int start, flag=0;
            int end;
            for(start=0; start<path.size()-1; start++){
                if(flag==1){
                    start--;
                    break;
                }
                for(end=start+1; end<path.size(); end++){
                    if(adj[path[end]].find(path[start])!=adj[path[end]].end()){
                        flag=1;
                        break;
                    }
                }
            }
            path.erase(path.begin()+end+1,path.end());
            path.erase(path.begin(),path.begin()+start);
        }

        bool cycle( vector<int> &path) const{
            set<int> white;
            set<int> grey;
            set<int> black;
            for(int i=0; i<_V; i++)
                white.insert(i);
            for(int i=0; i<_V; i++){
                if(cycledetect(i,white,grey,black)){
                    order(path,grey);
                    remove(path);
                    return true;
                }
            }

            return false;
        }

        bool cycledetect(int u, set<int> &white, set<int> &grey, set<int> &black) const{
            white.erase(u);
            grey.insert(u);
            for(auto it=adj[u].begin(); it!=adj[u].end(); ++it){
                if(white.find(*it)!=white.end())
                    if(cycledetect(*it,white,grey,black)) {
                        return true;
                    }
                if(grey.find(*it)!=grey.end()){
                    return true;}
            }
            black.insert(u);
            grey.erase(u);

            return false;
        } 
        void print(){
            for(int i=0; i<_V; i++){
                cout<<i<<" : ";
                for(auto it=adj[i].begin(); it!=adj[i].end(); ++it)
                    cout<<(*it)<<" ";
                cout<<endl; 
            }
        }
    private:
        int _V;
        vector<set<int>> adj;
};
#ifndef CONTEST
int main() {
    int V, E;
    cin >> V >> E;
    Graph g(V);
    for (int i = 0; i < E; ++i) { int u, v; cin >> u >> v; g.addEdge(u, v); }
    // g.print();
    vector<int> path;
    bool c = g.cycle(path);
    if (c) {
    cout << "CYCLE: ";
    for (int i = 0; i < path.size(); ++i)
    cout << path[i] << (i == path.size()-1 ? "\n" : " ");
    } else {
    cout << "NO CYCLE" << endl;
    }
}
#endif