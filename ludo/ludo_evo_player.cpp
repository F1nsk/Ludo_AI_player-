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

bool ludo_evo_player::posibleToMoveForward(int peiceNumber) 
{
  if (pos_start_of_turn[pieceIndex] == 99)
        return false;
    if (pos_start_of_turn[pieceIndex] == -1)
        return false;
    if (pos_start_of_turn[pieceIndex] + dice_roll > 51)
        return false;
    return true;
	
}



  
bool ludo_evo_player::isEnemyBehind(int peiceNumber)
{
}


bool ludo_evo_player::isInGoal(int peiceNumber) 
{
	
}


bool ludo_evo_player::canIdefend(int peiceNumber)
{
	int end_pos = dice_roll + pos_start_of_turn[peiceNumber];
    if (end_pos > 51)
        return false;
    int noFriends = friendlyOnfield(end_pos);
    if (noFriends == 1)
        return true;
    return false;
}

bool ludo_evo_player::canIenterBoard(int peiceNumber)
{
	
}

bool ludo_evo_player::posibleToKill(int peiceNumber)
{
	  int end_pos = dice_roll + pos_start_of_turn[peiceNumber];
     if (end_pos > 51)
     
         return false;
     int noEnemies = oppenentOnfield(end_pos);
     if (noEnemies == 1)
         if (!(isGlobe(end_pos)))
            return true;
     return false;
	
	
	
}

bool ludo_evo_player::isPositionBlocked(int peiceNumber)
{
	
	
	
	
}
 


bool ludo_evo_player::moveToFinish(int peiceNumber)
{
	  int end_pos = dice_roll + pos_start_of_turn[peiceNumber];
    if (pos_start_of_turn[pieceIndex] > 51)
        return false;
    if (end_pos > 51)
        return true;
    return false;
}
	
	
	
	
}

bool ludo_evo_player::moveInFinish(int peiceNumber)
{
	  if (pos_start_of_turn[pieceIndex] > 51)
    {
        if (pos_start_of_turn[peiceNumber]+dice_roll == 56 )
            return false;
        if (pos_start_of_turn[peiceNumber]+dice_roll < 56)
            return true;
    }
    return false;
	
	
	
}


bool ludo_evo_player::leaveHomePossible(int peiceNumber)
{
	if (pos_start_of_turn[peiceNumber] == -1 && dice_roll == 6)
        return true;
    return false;
}
    
    
 bool ludo_evo_player::oppenentOnfield(int position)
 {
	 int counter = 0;
    bool skip = false;
    for (int i = 4; i < pos_start_of_turn.size(); i++)
    {
            if (pos_start_of_turn[i] == position)
                counter++;
    }
    return counter;


}



bool ludo_evo_player::friendlyOnfield(int position)
{
	 int counter = 0;
    for (int i = 0; i < 4; i++)
    {
        if (pos_start_of_turn[i] == position)
            counter++;
    }
    return counter;
}

    
    
bool ludo_evo_player:: posibleToMoveToGlobe(int peiceNumber)
{
	if (pos_start_of_turn[pieceIndex] == 99)
        return false;
    if (pos_start_of_turn[pieceIndex] == -1)
        return false;
    if (pos_start_of_turn[pieceIndex] + dice_roll > 51)
        return false;
    return true;

	
}


bool ludo_evo_player::isGlobe(int postion)
{
	
	if(postion < 52){     
        if(postion == 8 || postion == 8+13 || postion == 8+26)
        {           
			 return true;
        }
    }
    return false;


} 


void ludo_evo_player::randomizeWeight()
{
	for(int i =0; i < genes_weights.length(); i++)
	{
		genes_weights[i] = random(0,10); 
	} 
	
	
	
}




    
