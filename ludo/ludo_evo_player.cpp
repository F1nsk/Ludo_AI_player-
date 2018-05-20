#include "ludo_evo_player.h"

ludo_evo_player::ludo_evo_player():
    pos_start_of_turn(16),
    pos_end_of_turn(16),
    dice_roll(0)
{








}


int ludo_evo_player::make_decision(){
    if(dice_roll == 6){
        for(int i = 0; i < 4; ++i){
            if(pos_start_of_turn[i]<0){
                return i;
            }
        }
        for(int i = 0; i < 4; ++i){
            if(pos_start_of_turn[i]>=0 && pos_start_of_turn[i] != 99){
                return i;
            }
        }
    } else {
        for(int i = 0; i < 4; ++i){
            if(pos_start_of_turn[i]>=0 && pos_start_of_turn[i] != 99){
                return i;
            }
        }
        for(int i = 0; i < 4; ++i){ //maybe they are all locked in
            if(pos_start_of_turn[i]<0){
                return i;
            }
        }
    }
    return -1;
}










void ludo_evo_player::start_turn(positions_and_dice relative)
{
    pos_start_of_turn = relative.pos;
    dice_roll = relative.dice;
    int decision = make_decision();
    emit select_piece(decision);



}


void ludo_evo_player::post_game_analysis(std::vector<int> relative_pos)
{
    pos_end_of_turn = relative_pos;
    bool game_complete = true;
    for(int i = 0; i < 4; ++i){
        if(pos_end_of_turn[i] < 99){
            game_complete = false;
        }
    }
    emit turn_complete(game_complete);
}


void ludo_evo_player::getPlayersPos() 
{
	
}



  
bool ludo_evo_player::isEnemyBehind(currentPos)
{
}


bool ludo_evo_player::isInGoal(currentPos) 
{
	
}


bool ludo_evo_player::canIdefend(currentPos)
{
	
}

bool ludo_evo_player::canIenterBoard()
{
	
}

bool ludo_evo_player::posibleToKill()
{
}

bool ludo_evo_player::isPositionBlocked()
{
}
 
vector<vector<bool>  ludo_evo_player::possibleMoveToMake()
{
}
   



