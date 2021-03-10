#include <iostream>
//#include <string>

using namespace std;


template <typename T>
class stack {
	public : 
	        stack(int size){
	        	top = -1;
	        	lenght = size;
	        	p = new T [lenght];
			}
	        stack(const stack &s){
	        	top = s.top;
	        	lenght = s.lenght;
	        	p = new T [lenght];
	        	for (int i =0; i <= top; i++)
	        	    p[i] = s.p[i];
			}
	        ~stack(){
	        	delete [] p;
			}
	        const stack & operator = (const stack &s){
	        	top = s.top;
				lenght = s.lenght;
				delete [] p;
	        	p = new T [lenght];
	        	for (int i =0; i <= top; i++)
	        	    p[i] = s.p[i];    
	        	return *this;
			}
	        
	        bool empty(){
	        	if(top == -1) 
					return true;
	        	else 
					return false;
			}
	        
			void push (const T &x){
	        	p[++top] = x;
			}

	        T pop (){
	        	return p[top--];
			}

	        int size(){
	        	return top + 1;
			}
	        
	        friend ostream & operator << (ostream &out, const stack &s){
	        	out << "[";
	        	for (int i = 0; i<= s.top; i++){
	        	    out<< s.p[i];
				    if(i != s.top) out << ", ";
	            }
	            out << "]";
	        	return out;
			}
	private :
		int lenght;
		int top ;
		T *p; 
		
};

// int main(){
// 	stack<string> a(10), b(3);
// 	a.push("ddd");
// 	a.push("hjhh");
// 	cout << a << a.size()<<endl;
// 	a.pop();
// 	b=a;
// 	cout <<"a: "<< a << "b: "<< b<<endl;
// 	cout<<a.empty()<<" "<<a.size() <<endl;
// 	a.pop();
// 	cout<<a.empty()<< " b: "<<b.empty()<<endl;
// 	cout<<a<<endl;
// }




