#include "ludo_evo_player.h"

ludo_evo_player::ludo_evo_player():
    pos_start_of_turn(16),
    pos_end_of_turn(16),
    dice_roll(0)
{








}


int ludo_evo_player::make_decision()
{

    for (int i = 0; i < 4; i++)
    {
        int currentPos = pos_start_of_turn[i];
        int nextPos =  currentPos + dice_roll;






    }
    return nextPos;


}






void ludo_evo_player::start_turn(positions_and_dice relative)
{
    pos_start_of_turn = relative.pos;
    dice_roll = relative.dice;
    int decision = make_decision();
    emit select_piece(decision);



}





