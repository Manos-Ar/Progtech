#include <iostream>  
//#include <stdio.h>  
#include <cmath>  
using namespace std;  

class Polynomial {  
	protected :  
		class Term{  
			protected:  
				int coefficient, exponent;  
				Term *next;  
				Term (int exp, int coef, Term *n) {  
					exponent=exp;  
					coefficient=coef;  
					next=n;  
				}  
				friend class Polynomial;  
		};  
	private :   
		Term *head;  
		Term *tail;  
		void copyl(const Polynomial &l){  
			for(Term *p=l.head; p!=NULL;p=p->next )            
				push_backl(p->coefficient,p->exponent);  
		}  
		void push_backl(const int &coe,const int &expo){  
			Term *temp= new Term(expo,coe,NULL);  
			if(tail!=NULL) tail->next=temp;  
			else head=temp;  
			tail=temp;  
		}  
		void purge(){  
			Term *p=head;  
			while(p!=NULL){  
				Term *d=p;  
				p=p->next;  
				delete d;   
			}  
		}  
		int return_expo(const Term *p){  
			return p->exponent;  
		}  
		int return_coefficient(const Term *p){  
			return p->coefficient;  
		}  
		Term * return_next(const Term *sofaki){  
			return sofaki->next;  
		}      
	public :  
		Polynomial ():head(NULL),tail(NULL){}  
		Polynomial (const Polynomial &p):head(NULL),tail(NULL){  
			copyl(p);  
		}  
		~Polynomial(){  
			purge();  
		}  
		Polynomial & operator = (const Polynomial &p){  
			purge();  
			head=tail=NULL;  
			copyl(p);  
			return *this;  
		}  


		void addTerm(int expon, int coeff){
			if(coeff==0) return;
			Term *temp = head,*temp1;
			int flug=0;
			while(temp!=NULL){
				if(expon > temp->exponent && temp==head) {
					Term *node = new Term(expon,coeff,temp);
					head = node;
					flug = 1; break;
				}
				else if(expon==temp->exponent && temp==head){
					temp->coefficient += coeff;
					flug = 1; break;	
				}
				else if(expon == temp->exponent) {
					temp->coefficient += coeff;
					flug = 1; break;
				}
				else if(expon> temp->exponent){
					Term *node = new Term(expon,coeff,temp);
					temp1->next = node;
					flug = 1; break;
				}
				else{	//expo < temp->exponent
					temp1=temp;
					temp = temp->next;
					flug = 0;
				}
			}
			if(flug == 0){
				push_backl(coeff,expon);
			}
			temp=head;
			temp1=NULL;
			Term *temp2;
			while(temp!=NULL){
				if(temp->coefficient==0 && temp==head && tail==temp){
					head=temp->next;
					tail=temp->next;
					Term *temp3=temp;
					temp=temp->next;
					//cout << "Deleting (" << temp3->exponent << ", " << temp3->coefficient << ")\n";
					delete(temp3);
				}
				else if(temp->coefficient==0 && temp==head){
					head=temp->next;
					Term *temp3=temp;
					temp=temp->next;
					//cout << "Deleting (" << temp3->exponent << ", " << temp3->coefficient << ")\n";
					delete(temp3);
				}
				else if(temp->coefficient==0){
					temp1->next=temp->next;
					if (temp==tail) tail = temp1;
					Term *temp3=temp;
					temp=temp->next;
					//cout << "Deleting (" << temp3->exponent << ", " << temp3->coefficient << ")\n";
					delete (temp3);
				}
				else{
					temp2=temp1;                               
					temp1=temp;
					temp=temp->next;
				}
			}
			//if(head=NULL) tail=head;
			if(temp1!=NULL){
				if(temp1->coefficient==0){
					temp2->next=NULL;
					tail=temp2;
					delete (temp1);
				}
			}
		}

		double evaluate(double x){  
			double result=0;  
			Term *temp = head;  
			while(temp!=NULL){  
				result += temp->coefficient * pow(x,temp->exponent);  
				temp=temp->next;  
			}  
			return result;  
		}  

		friend Polynomial operator + (Polynomial &p, Polynomial &q){  
			Polynomial a;  
			Term *temp_p = p.head;  
			Term *temp_q = q.head;  
			while(temp_p!=NULL){  
				a.addTerm(a.return_expo(temp_p),a.return_coefficient(temp_p));  
				temp_p=a.return_next(temp_p);  
			}  
			while(temp_q!=NULL){  
				a.addTerm(a.return_expo(temp_q),a.return_coefficient(temp_q));  
				temp_q=a.return_next(temp_q);  
			}  
			return a;  
		}  
		friend Polynomial operator * (Polynomial &p, Polynomial &q){  
			Polynomial a;
			Term *temp_p = p.head;  
			Term *temp_q = q.head;  
			while(temp_p!=NULL){  
				int expo=p.return_expo(temp_p),coeff=p.return_coefficient(temp_p);  
				while(temp_q!=NULL){  
					a.addTerm(expo+q.return_expo(temp_q),coeff*q.return_coefficient(temp_q));  
					//cout << "Adding (" << expo+q.return_expo(temp_q) << ", " << coeff*q.return_coefficient(temp_q) << ")\n";
					temp_q=q.return_next(temp_q);  
				}  
				temp_q=q.head;  
				temp_p=p.return_next(temp_p);  
			}  
			return a;  
		}  

		friend ostream & operator <<(ostream &out, const Polynomial &q){  
			Polynomial a(q);  
			Term *temp=q.head;   
			int flag1=0,flag2=0;  
			if(temp==NULL) out<<"0";
			while(temp!=NULL){  
				if(flag1==0){  
					if(a.return_coefficient(temp)<0) out<<"- ";  
					flag1=1;  
				}  

				if(flag2==1 ){  
					if(a.return_coefficient(temp)>0) out<<" + ";  
					else out<<" - ";  
				}  
				if(abs(a.return_expo(temp))==0) {  
					out<<abs(a.return_coefficient(temp));  
					break;  
				}  
				else if(abs(a.return_expo(temp))==1){  
					if(abs(a.return_coefficient(temp))==1) out<<"x";  
					else out<<abs(a.return_coefficient(temp))<<"x";  
				}  
				else{  
					if (abs(a.return_coefficient(temp))==1) out<<"x^"<<a.return_expo(temp);  
					else out<<abs(a.return_coefficient(temp))<<"x^"<<a.return_expo(temp);  
				}  
				temp=a.return_next(temp);  
				flag2=1;  
			}  
			//out<<endl;  
			return out;  
		}  /*
		void print(){
			Term *temp=head; 
			int size=0; 
            while(temp!=NULL){
            	temp=temp->next;
               	size++;}
			cout<<"size:"<<size<<endl;
          }   
		void return_top(){
			cout<<head->exponent<<" "<<head->coefficient<<endl;
		}
		void return_back(){
			cout<<tail->exponent<<" "<<tail->coefficient<<endl;
		}*/
};/*
int main(){ 
	Polynomial a; 
	a.addTerm(1,1);
	cout<<a<<endl;
	a.print();
	a.addTerm(1,-1);
		cout<<a<<endl;
	a.print();
	a.addTerm(2,-2);
		cout<<a<<endl;
	a.print();
	a.addTerm(2,1);
		cout<<a<<endl;
	a.print();

}*/
