#include <iostream>
#include <vector>
using namespace std;

int main(){

    int N,M,a,b,node;
    int counter=0;
    cin>>N>>M;
    vector<char> nodes;
    char letter,letter1,letter2;
    vector<vector<int>> adj(N);
    for(int i=0; i<N; i++){
        cin>>letter;
        nodes.push_back(letter);
    }

    for(int i=0; i<M; i++){
        cin>>a>>b;
        adj[a].push_back(b);
    }

    for(int i=0; i<N; i++){
        letter=nodes[i];
        for(unsigned int j=0; j<adj[i].size(); j++){
            node=adj[i][j];
            letter1=nodes[node];
            if(letter!=letter1)
                continue;
            // else{}
            for(unsigned k=0; k<adj[node].size(); k++){
                letter2=nodes[adj[node][k]];
                if(letter==letter2)
                    counter++;
            }
        }
    }

    cout<<counter<<endl;
}