#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

class Node{
    public:
        int name;
        int size=0;

        Node(){}
        Node(int n):name(n){}

        bool empty(){
            return adj.empty();
        }

        int first_adj(){
            return adj.begin()->first;
        }

        void add_edge(int v){
            auto it = adj.find(v);
            if(it != adj.end()){
                adj[v]++;   
            }
            else
                adj[v]=1;
            size++;
        }

        void remove_edge(int v){
            auto it = adj.find(v);
            if(it != adj.end()){
                if(it->second==1)
                    adj.erase(it);
                else
                    it->second--;
            }
        }


    private:
        unordered_map<int,int> adj;

};

class Graph{
    public:
        Graph(int n, int m):N(n),M(m),count_odd(0){
            for(int i=0; i<N; i++)
                nodes.push_back(Node(i));
        }

        void add_edge(int u, int v){
            nodes[u].add_edge(v);
            nodes[v].add_edge(u);
        }

        void remove_edge(int u, int v){
            nodes[u].remove_edge(v);
            nodes[v].remove_edge(u);
        }

        void check_odd(){
            for(int i=0; i<N; i++)
                if(nodes[i].size%2 == 1){
                    count_odd++;
                    odd=i;
                }
        }

        bool euler_path(){
            if(count_odd==0 || count_odd==2)
                return true;
            return false;
        }

        bool euler_cycle(){
            if (count_odd==0)
                return true;
            return false;
        }

        pair<int,int> find_path(){
            stack<Node*> st;
            int start=-1, finish;

            st.push(&nodes[odd]);
            Node* temp;
            while(!st.empty()){
                temp=st.top();
                finish = temp->name;

                if(temp->empty()){
                    if(start==-1)
                        start=temp->name;
                    st.pop();
                    }
                else{
                    st.push(&nodes[temp->first_adj()]);
                    remove_edge(temp->name,temp->first_adj());
                }
            }
            return (start<finish)? pair<int,int>(start,finish) : pair<int,int>(finish,start);     
        }

        void run(){
            check_odd();
            if(euler_cycle())
                cout<<"CYCLE\n";
            else if(euler_path()){
                pair<int,int> path=find_path();
                cout<<"PATH "<<path.first<<" "<<path.second<<endl;
            }
            else 
                cout<<"IMPOSSIBLE\n";
        }

    private:
        int count_odd, odd;

        int N,M;
        vector<Node> nodes;
};

int main(){
    int n,m,u,v;
    cin >>n>>m;
    Graph graph(n,m);
    for(int i=0; i<m;i++){
        cin >>u>>v;
        graph.add_edge(u,v);
    }
    graph.run();
}