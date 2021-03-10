#include <iostream>
#include <stdexcept>
#include "d.cpp"

using namespace std;

class Move{
	public :
	Move (int sh, int sc, int th, int tc){
		source_heap = sh;
		source_coins = sc;
		target_heap = th;
		target_coins = tc;
	}
	
	int getSource() const{ 
	
	    return source_heap;
	    
		}
	int getSourceCoins() const {
	    
		return source_coins;
	
		}
	int getTarget() const{
	    
		return target_heap;
		
		}
	int getTargetCoins() const{
	
	    return target_coins;
		
		}
	
	friend ostream & operator << (ostream &out, const Move &move){
         
		out << "takes " << move.getSourceCoins() << " coins from heap " << move.getSource() ;
		
        if(move.getTargetCoins() == 0) out << " and puts nothing" ;
        else out << " and puts " << move.getTargetCoins() << " coins to heap " << move.getTarget() ;
		return out;
	}
	
	private:
	    int source_heap, source_coins, target_heap, target_coins;
	
	
};


class State{
	public :
	State(int h, const int c[]){
		heap = h;
		p = new int [heap];
		for(int i = 0; i < h; i++)
			p[i] = c[i];
		
	}
	
	~State(){
		delete [] p;
	}
	
	void next (const Move & move) throw (logic_error){
		if ( move.getSource() < 0 || move.getSource() >= heap  || move.getTarget() < 0 || move.getTarget() >= heap ) throw logic_error ("invalid heap");
		else if ( move.getSourceCoins() == 0 || move.getSourceCoins() > p[move.getSource()] 
                  || move.getTargetCoins() >= move.getSourceCoins()) throw logic_error ("invalid coins");
		else {

			p[move.getSource()] -= move.getSourceCoins();
            if(move.getTargetCoins() == 0) return;
			p[move.getTarget()] += move.getTargetCoins();
		}
	}
	
	bool winning () const{
		bool win;
		for(int i =0; i < heap; i++){
			
		   if (p[i] == 0) win = true;
		   else {
                 win = false; 
                 break;
               }
	    }
		return win; 
    }
    
    int getHeaps() const{
	    return heap;
	} 
    
    int getCoins(int h) const throw (logic_error){
    	if ( h < 0 || h >= heap ) throw logic_error ("invalid heap"); 
    	else return p[h];
	}
    
    friend ostream & operator << (ostream &out, const State &state){
    	for(int i = 0; i < state.getHeaps(); i++){
    		out << state.getCoins(i);
    		if (i != (state.getHeaps() -1)) out << ", ";
		}
		return out;
	}
    
	private:
		int heap;
		int *p;
	
};

