#include <iostream>
#include <string>
//#include <stdexcept>

using namespace std;
/*
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
	
};*/


class Player{
	protected:
			string *Name,*Type;
			string get() const{
				return *Name;
			} 

	public :
			
			Player(const string &n){
				Name = new string;
				*Name = n;
			}

			virtual ~Player(){
				delete Name;
				delete Type;
						
			}

			virtual const string & getType() const = 0;

			virtual Move play(const State &s) = 0;
			friend ostream & operator << (ostream &out, const Player &player){
				out<<player.getType() << " player " << player.get();
				return out;
}
};


class GreedyPlayer : public Player{
/*	private : 
		string type;*/
	public:
		GreedyPlayer (const string &n) : Player(n){
			Type = new string;
			*Type = "Greedy";
		};
		
		const string & getType() const{ 
			return *Type;
}

		Move play (const State &s){
			int max = 0, point_max = 0;
			for(int i = 0; i < s.getHeaps(); i++){
				if(s.getCoins(i) > max) {
				max = s.getCoins(i);
				point_max = i;
			}
		}
			Move move(point_max,s.getCoins(point_max),0,0);
			return move;			
}
	
};

class SpartanPlayer : public Player {
/*	private : 
		string type;*/
	public:
		SpartanPlayer (const string &n) : Player(n){
			Type = new string ;
			*Type = "Spartan";
		}
		
		const string & getType() const{ 
			return *Type;
}

		Move play (const State &s){
			int max = 0, point_max = 0;
			for(int i = 0; i < s.getHeaps(); i++){
				if(s.getCoins(i) > max) {
				max = s.getCoins(i);
				point_max = i;
			}
		}
			Move move(point_max,1,0,0);
			return move;			
			
}
	
};
class SneakyPlayer : public Player{
/*	private : 
		string type;*/
	public:
		SneakyPlayer (const string &n) : Player(n){
			Type = new string;
			*Type = "Sneaky";
		};
		
		const string & getType() const{ 
			return *Type;
}

		Move play (const State &s){
			int min , flug = 0, point_min = 0;
			for(int i = 0; i < s.getHeaps(); i++)
				if (flug == 0){				
					if (s.getCoins(i) != 0){ 
						flug = 1;
						min = s.getCoins(i);
						point_min = i;
					}
				}
				else 
					if (s.getCoins(i) != 0)
						if (s.getCoins(i) < min) {
							min = s.getCoins(i);
							point_min = i;
						}
									
			Move move(point_min,s.getCoins(point_min),0,0);
			return move;			
			
}
	
};class RighteousPlayer : public Player{
/*	private : 
		string type;*/
	public:
		RighteousPlayer (const string &n) : Player(n){
			Type = new string;
			*Type = "Righteous";
		};
		
		const string & getType() const{ 
			return *Type;
}

		Move play (const State &s){
			int max = 0, point_max = 0, min , flug = 0, point_min = 0;
			for(int i = 0; i < s.getHeaps(); i++){
				if(s.getCoins(i) > max) {		// max find
					max = s.getCoins(i);
					point_max = i;
				}
				if (flug == 0){				//min find
					if (s.getCoins(i) != 0){ 
						flug = 1;
						min = s.getCoins(i);
						point_min = i;
					}
				}
				else 
					if (s.getCoins(i) != 0)
						if (s.getCoins(i) < min) {
							min = s.getCoins(i);
							point_min = i;
						}
							
}
			Move move(point_max,s.getCoins(point_max)/2,point_min,s.getCoins(point_min)/2 - 1);
			return move;			
			
}
	
};

/*
int main(){
	
	GreedyPlayer g("manos");
	cout <<g;
	
	
	
}*/


