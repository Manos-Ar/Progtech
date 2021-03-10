    #include <iostream>  
    #include <exception>  
    #include <iomanip>  
      
    using namespace std;  
      
    class ChessBoardArray{  
    protected:  
        class Row{  
            private:  
                ChessBoardArray &chess;  
                int row;  
            public:  
                Row(ChessBoardArray &a, int i) : chess(a), row(i){}  
                int & operator [] (int i) const{  
                    return chess.select(row,i);  
                }  
        };  
        class ConstRow{  
            private:  
                const ChessBoardArray &constchess;  
                int row;  
            public:  
                ConstRow(const ChessBoardArray &a, int i) : constchess(a), row(i){}  
                const int operator [] (int i) const{  
                    return constchess.select(row,i);  
                }  
        };  
    private:  
        int *array, num_base, num, data;  
        unsigned int loc(int i, int j) const throw(out_of_range){  
            int di = i-num_base, dj = j-num_base;  
            if(di<0 || di>=num || dj<0 || dj>=num)  
                throw out_of_range("invalid index");  
            if((di+dj)%2==1) throw out_of_range("the cell is black");  
            unsigned int value;  
            di++;dj++;  
            value = num / 2 * (di - 1) + dj / 2 + dj % 2 - 1 + num % 2 * di / 2;  
        return value;  
            return value;  
        }  
    public:  
      
        ChessBoardArray(unsigned int size=0, unsigned int base=0) {  
        num=size;  
        num_base = base;  
        data=(num*num)/2 + num%2;  
        array=new int[data];  
            for(int i=0; i<data; i++)  
                array[i] = 0;  
        }  
      
        ChessBoardArray(const ChessBoardArray &a){  
        num=a.num;  
        data=a.data;  
        num_base = a.num_base;  
        array=new int[data];  
            for(int i=0; i<data; i++)  
                array[i] = a.array[i];  
        }  
      
        ~ChessBoardArray(){ delete [] array;}  
      
        ChessBoardArray & operator = (const ChessBoardArray &a){  
            delete []array;  
            num_base = a.num_base;  
            num = a.num;  
            data=a.data;  
            array = new int[data];  
            for(int i=0; i<data; i++)  
                array[i]=a.array[i];  
            return *this;  
        }  
      
        int & select(int i, int j){  
            return array[loc(i,j)];  
        }  
        int select(int i, int j) const{  
            return array[loc(i,j)];  
        }  
          
        const Row operator [] (int i) {  
            return Row(*this,i);  
        }  
        const ConstRow operator [] (int i) const {  
            return ConstRow(*this,i);  
        }  
      
        friend ostream & operator << (ostream & out, const ChessBoardArray &a){  
            int key=0;        
            for(int i=0; i<a.num; i++){  
                if(a.num%2==0){  
                    for(int j=0; j<a.num/2; j++){  
                        if(i%2==0)  
                            out<<setw(4)<<a.array[key++]<<setw(4)<<"0";  
                        else  
                            out<<setw(4)<<"0"<<setw(4)<<a.array[key++];  
                    }  
                    out<<endl;  
                }  
                else{  
                    if(i%2==0){  
                        for(int j=0; j<a.num/2; j++)  
                                out<<setw(4)<<a.array[key++]<<setw(4)<<"0";  
                    out<<setw(4)<<a.array[key++]<<endl;  
                    }  
                    else{  
                        for(int j=0; j<a.num/2; j++)  
                            out<<setw(4)<<"0"<<setw(4)<<a.array[key++];  
                        out<<setw(4)<<"0"<<endl;  
                    }  
                }  
            }  
        return out;  
        }  
    };  
    /* 
    int main() { 
        ChessBoardArray a(5,2); 
        a[3][5]=42; 
        /*a[4][4]=17; 
        try { a[2][1] = 7; } 
        catch(out_of_range &e) { cout <<"a[2][1] is black"<< endl; } 
        try { cout << a[1][2] << endl; } 
        catch(out_of_range &e) { cout << "and so is a[1][2]" << endl; } 
        cout << a<<endl; 
        for(int i=0; i<a.data; i++) cout<<a.array[i]<<" "; 
    }*/  
