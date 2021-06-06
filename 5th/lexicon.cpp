#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node{

    Node(const string &w, int c=1):word(w),count(c),left(nullptr),right(nullptr){};

    string word;
    int count;
    Node *left,*right;
};

class lexicon{
    public:
        lexicon(): root(nullptr){};
        ~lexicon(){
        };

        void insert(const string &s){
            Node *node_1,*node_2,*parent;
            string s1;
            int comp, flag;

            node_1 = root;

            if(root==nullptr){
                node_2 = new Node(s); 
                root=node_2;
                return;
            }

            while(true){
                
                if(node_1==nullptr){
                    node_2 = new Node(s); 
                    if(flag)
                        parent->right=node_2;
                    else
                        parent->left=node_2;
                    return;
                }

                s1 = node_1->word;
                comp = s1.compare(s);
                parent=node_1;

                if(comp==0){
                    node_1->count++;
                    return;
                }
                else if(comp<0){
                    flag=1;
                    node_1=node_1->right;
                }
                else if(comp>0){
                    flag=0;
                    node_1=node_1->left;
                }

            }
        };

        int lookup(const string &s) const{
            Node *node;
            int comp;
            string s1;

            node=root;

            while(true){
                if(node==nullptr)
                    return 0;
                
                s1 = node->word;
                comp = s1.compare(s);

                if(comp==0)
                    return node->count;
                else if(comp<0)
                    node=node->right;
                else if(comp>0)
                    node=node->left;
            }
        };

        int depth(const string &s) const{
            Node *node;
            int comp, count;
            string s1;

            node=root;
            count=0;
            
            while(true){
                if(node==nullptr)
                    return -1;
                
                s1 = node->word;
                comp = s1.compare(s);

                if(comp==0)
                    return count;
                else if(comp<0)
                    node=node->right;
                else if(comp>0)
                    node=node->left;
                
                count++;
            }
        };

        void replace(const string &s1, const string &s2){
            Node *node;
            int count,comp;
            string s;

            if(lookup(s1)==0)
                return;

            // cout<<"look up ok"<<endl;
            count=remove(s1);
            // cout<<"remove ok\n";
            insert(s2);
            if(count==1)
                return;

            node=root;

            while(true){

                comp = node->word.compare(s2);

                if(comp==0){
                    node->count+=count-1;
                    return;
                }
                else if(comp<0)
                    node=node->right;
                else if(comp>0)
                    node=node->left;
            }
        };

        int remove(const string &s){
            Node *node=root, *original_parent, *replace_node;
            string s1;
            int comp, flag, count;

            while(true){
                s1 = node->word;
                comp=s1.compare(s);

                if(comp==0){
                    // cout<<"find node to remove\n";
                    if(node==root){
                        // cout<<"removes root\n";
                        if(node->left==nullptr && node->right==nullptr)
                            replace_node=nullptr;
                        else if(node->left==nullptr || node->right==nullptr)
                            replace_node = (node->left==nullptr)? node->right:node->left;
                        else{
                            replace_node=replace_max_node(node->left);
                            replace_node->right=node->right;
                            if(replace_node!=node->left)
                                replace_node->left=node->left;
                            }
                        
                        root=replace_node;
                        count=node->count;
                        delete node;
                        return count;
                    }
                    else{

                        if(node->left==nullptr && node->right==nullptr)
                            replace_node=nullptr;
                        else if(node->left==nullptr || node->right==nullptr)
                            replace_node = (node->left==nullptr)? node->right:node->left;
                        else{
                            replace_node = replace_max_node(node->left);
                            replace_node->right = node->right;
                            if(replace_node!=node->left)
                                replace_node->left=node->left;
                            }
                        // cout<<"flag: "<<flag<<endl;
                        if(flag==1)
                                original_parent->right=replace_node;
                        else
                            original_parent->left=replace_node;
                        
                        count=node->count;
                        delete node;
                        return count;
                    }
                }
                else if(comp<0){
                    // cout<<"went right\n";
                    flag=1;
                    original_parent=node;
                    node=node->right;
                }
                else if(comp>0){
                    // cout<<"went left\n";
                    flag=0;
                    original_parent=node;
                    node=node->left;
                }
            }
        }

        Node* replace_max_node(Node *node){
            Node *parent=node;

            if(node->left==nullptr && node->right==nullptr)
                return node;
            else if(node->right==nullptr)
                return node->left;


            while(node->right!=nullptr){
                parent=node;
                node=node->right;
            }

            if(node->left!=nullptr)
                parent->right=node->left;
            else 
                parent->right=nullptr;

            return node;
        }

        friend ostream & operator << (ostream &out, const lexicon &l){
            l.print(out,l.root);
            return out;
        };

        ostream & print(ostream &out, const Node *node) const{
            if(node!=nullptr){
                print(out,node->left);
                out<<node->word<<" "<<node->count<<endl;
                print(out,node->right);
            }
            return out;
        } 

    private:
        Node *root;
};


#ifndef CONTEST
int main(){  
    int count=0;
    lexicon l;  
    l.insert("the");  
    l.insert("boy");  
    l.insert("and");  
    l.insert("the");  
    l.insert("wolf");
    cout << l;  
    cout << "The word 'and' is found " << l.lookup("and") << " time(s)" <<" at depth " << l.depth("and")<< endl;  
    cout << "The word 'boy' is found " << l.lookup("boy") << " time(s)" <<" at depth " << l.depth("boy")<< endl;  
    cout << "The word 'the' is found " << l.lookup("the") << " time(s)" <<" at depth " << l.depth("the")<< endl;  
    cout << "The word 'wolf' is found " << l.lookup("wolf") << " time(s)" <<" at depth " << l.depth("wolf")<< endl;  
    cout << "The word 'dummy' is found " << l.lookup("wolf") << " time(s)" <<" at depth " << l.depth("dummy")<< endl;  
    cout<<"replace "<<count++<<endl;
    l.replace("and", "dummy");  
    cout << "The word 'wolf' is found " << l.lookup("wolf") << " time(s)" <<" at depth " << l.depth("wolf")<< endl;
    cout << "The word 'dummy' is found " << l.lookup("dummy") << " time(s)" <<" at depth " << l.depth("dummy")<< endl;
    cout<<"replace "<<count++<<endl;
    l.replace("boy", "dummy");  
    cout<<l;
    cout << "The word 'wolf' is found " << l.lookup("wolf") << " time(s)" <<" at depth " << l.depth("wolf")<< endl;
    cout << "The word 'dummy' is found " << l.lookup("dummy") << " time(s)" <<" at depth " << l.depth("dummy")<< endl;
    cout<<"replace "<<count++<<endl;
    l.replace("the", "dummy");  
    cout << "The word 'wolf' is found " << l.lookup("wolf") << " time(s)" <<" at depth " << l.depth("wolf")<< endl;
    cout << "The word 'dummy' is found " << l.lookup("dummy") << " time(s)" <<" at depth " << l.depth("dummy")<< endl;
    cout<<"replace "<<count++<<endl;
    cout<<l;
    l.replace("wolf", "dummy");  
    cout << "The word 'wolf' is found " << l.lookup("wolf") << " time(s)" <<" at depth " << l.depth("wolf")<< endl;
    cout << l;  
}  

#endif