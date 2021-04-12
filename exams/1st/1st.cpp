#include <iostream>
#include <map>
#include <string>
#include <set>
#include <vector>

using namespace std;


int main(){
    int N, D, d, mx,max_num;
    string value;
    cin >>N>>D;

    vector<set<std::string>> dict(D);

    for (int i=0; i<N; i++){
        cin >>d>>value;
        dict[d-1].insert(value);
    }
    mx = dict[0].size();
    max_num=1;
    for(int i=1; i<D; i++){
        if((int)dict[i].size()>mx){
            mx = dict.size();
            max_num = i+1;
        }
    }

    map<std::string,int> count;

    for(auto it=dict[0].begin(); it!=dict[0].end(); it++){
        count.insert(pair<string,int>(*it,1));
    }
    for(int i=1; i<D; i++){
        for(auto it=dict[i].begin(); it!=dict[i].end(); it++){
            auto pos = count.find(*it);
            if(pos != count.end()){
                pos->second++;
            }
        }
    }

    vector<string> common;
    for(auto it=count.begin(); it!=count.end(); it++){
        if(it->second==D){
            common.push_back(it->first);
        }
    }

    cout<<"largest dictionary is "<<max_num<<" with "<<mx<<" word(s)"<<endl;

    for(auto it=common.begin(); it!=common.end(); it++)
        cout<<*it<<endl;
    
    cout<<common.size()<<" word(s) appear in all dictionaries\n";

}
