#include <iostream>
#include <string>
// #include "specker_game.cpp"
#include <math.h>

using namespace std;


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
	public:
		GreedyPlayer (const string &n) : Player(n){
			Type = new string;
			*Type = "Greedy";
		};
		
		const string & getType() const{ 
			return *Type;
		}

		Move play (const State &s){
			int max = 0, point_max = 0, heap;
			heap = s.getHeaps();
			for(int i = 0; i < heap; i++){
				if(s.getCoins(i) > max) {
					max = s.getCoins(i);
					point_max = i;
				}
			}
			Move move(point_max,max,0,0);
			return move;			
		}
	
};

class SpartanPlayer : public Player {
	public:
		SpartanPlayer (const string &n) : Player(n){
			Type = new string ;
			*Type = "Spartan";
		}
		
		const string & getType() const{ 
			return *Type;
		}

		Move play (const State &s){
			int max = 0, point_max = 0, heap;
			heap = s.getHeaps();
			for(int i = 0; i < heap; i++){
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
	public:
		SneakyPlayer (const string &n) : Player(n){
			Type = new string;
			*Type = "Sneaky";
		};
		
		const string & getType() const{ 
			return *Type;
		}

		Move play (const State &s){
			int min , heap, point_min, coins;
			point_min = 0;
			min = s.getCoins(0);
			heap = s.getHeaps();
			for(int i = 1; i < heap; i++){	
				coins = s.getCoins(i);
				if (coins !=0 ){
					if (min > coins || min == 0) {
						min = coins;
						point_min = i;
					}
				}
			}	
									
			Move move(point_min,min,0,0);
			return move;			
			
		}
};
class RighteousPlayer : public Player{
	public:
		RighteousPlayer (const string &n) : Player(n){
			Type = new string;
			*Type = "Righteous";
		};
		
		const string & getType() const{ 
			return *Type;
}

		Move play (const State &s){
			int max, point_max = 0, min , heap, point_min = 0, tmp;
			heap = s.getHeaps();
			max = s.getCoins(0);
			min = s.getCoins(0);
			
			for(int i = 1; i < heap; i++){
				tmp = s.getCoins(i);
				if (min > tmp) {
					min = tmp;
					point_min = i;
				}

				if (max < tmp){
					max = tmp;
					point_max = i;
				}
			}
			int half = round(max/2.0);
			Move move(point_max,half,point_min,half-1);
			return move;			
		}
	
};

// int main(){
	
// 	cout <<round(17/2.0)<<endl;	
	
// }


