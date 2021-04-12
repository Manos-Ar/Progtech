#include <iostream>
#include <string>
#include <stdexcept>
// #include "specker_game.cpp"
// #include "specker_players.cpp"
#include <list>


using namespace std;


class Game{
    public:
        Game(int heaps, int players){
            Heaps = heaps;
            Players = players;
            heaps_end = 0;
            players_end = 0;
            arry_heaps = new int [Heaps];
            array_players = new Player * [Players];
        }

        void addHeap(int coins) throw(logic_error){
            if (heaps_end == Heaps)
                throw logic_error ("Too many heaps");
            if (coins<0)
                throw logic_error("Negatine coins");
            
            arry_heaps[heaps_end++] = coins;   
        }

        void addPlayer(Player *player) throw(logic_error){

            if (players_end == Players)
                throw logic_error ("Too many players");

            array_players[players_end++] = player;

        }

        void play(ostream &out) throw(logic_error){

            State state(Heaps,arry_heaps,Players);
            int index=0;
            while(!state.winning()){
                out<<"State: "<<state<<endl;
                Move move = array_players[index]->play(state);
                out<<*array_players[index]<<" ";
                out<<move<<endl;
                state.next(move);
                index = (index+1)%Players;
            }
            out<<"State: "<<state<<endl;
            if (index==0)
                index = Players-1;
            else
                index--;
            out<<*(array_players[index])<<" wins\n";
            cout;
        }

        // void show(){
        //     for(int i=0; i<heaps_end; i++){
        //         cout<<arry_heaps[i]<<" ";
        //     }
        //     cout<<endl;

        //     for(int i=0; i<players_end; i++){
        //         cout<<*array_players[i]<<endl;
        //     }
        // }

        int getPlayers(){
            return players_end;
        }

        const Player *getPlayer(int p) const throw(logic_error){
            if(p<0 || p>=players_end)
                throw logic_error("Invalid index of player");
            else
                return array_players[p];
        }

    private:
        int Heaps, Players, heaps_end, players_end;
        int* arry_heaps;
        Player** array_players;
};


// int main(){
//     Game game(3,4);
//     game.addHeap(10);
//     game.addHeap(20);
//     game.addHeap(17);
//     // game.addHeap(0);
//     // game.addHeap(0);
//     cout<<game.getPlayers()<<endl;
//     game.addPlayer(new SneakyPlayer("Tom"));
//     game.addPlayer(new SpartanPlayer("Mary"));
//     cout<<game.getPlayers()<<endl;
//     game.addPlayer(new GreedyPlayer("Alan"));
//     game.addPlayer(new RighteousPlayer("Robin"));
//     // game.addPlayer(new GreedyPlayer("Mary"));
//     // game.show();
//     game.play(cout);
//     cout<<game.getPlayers()<<endl;
//     cout<<*(game.getPlayer(0))<<endl;
// }