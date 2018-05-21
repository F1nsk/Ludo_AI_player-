#include "ludo_evo_player.h"

ludo_evo_player::ludo_evo_player():
    pos_start_of_turn(16),
    pos_end_of_turn(16),
    dice_roll(0)

{

}


int ludo_evo_player::make_decision()
{
   int temp = 0;
   possibleMoves p1 = exploration(0);
   possibleMoves p2 = exploration(1);
   possibleMoves p3 = exploration(2);
   possibleMoves p4 = exploration(3);
   float scoreOne =  findHighScoreMove(p1);
   float scoreTwo = findHighScoreMove(p2);
   float scoreThree = findHighScoreMove(p3);
   float scoreFour = findHighScoreMove(p4);

   scoreKeeper = {scoreOne, scoreTwo, scoreThree, scoreFour};


//   for(int i = 0; i < scoreKeeper.size(); i++)
//   {
//       if(scoreKeeper[i] > temp)
//       {
//           temp = scoreKeeper[i];
//       }
//   }


   std::cout << "high score is " << temp << std::endl;





    return -1;

   // skal returne melle 0 og 3, også kalre spillet resten.

}

float ludo_evo_player::findHighScoreMove(possibleMoves player)
{
    std::vector<float>  temp;
    float tmp = 0;
    chrom chromoson;
    possibleMoves tempPlayer;
    player = tempPlayer;
          if (tempPlayer.killFoe == true)
            {

            temp.push_back(chromoson.weightKillFoe);
            }

         if(tempPlayer.moveforward == true)
            {
                temp.push_back(chromoson.weightMoveForward);
            }

         if(tempPlayer.moveToGlobe == true)
            {
                temp.push_back(chromoson.weightMoveToGlobe);
            }
         if(tempPlayer.defend == true)
            {
                temp.push_back(chromoson.weightDefend);
            }

        if(tempPlayer.leaveHouse == true)
            {
                temp.push_back(chromoson.weightLeaveHouse);
            }

        if(tempPlayer.moveToGoal == true)
            {
                temp.push_back(chromoson.weightMoveToGlobe);
            }
        if(tempPlayer.moveInGoal == true)
            {
                temp.push_back(chromoson.weightMoveInGoal);
            }
        if(tempPlayer.moveToStar == true)
            {
                temp.push_back(chromoson.weightMoveToStar);
            }
        if(tempPlayer.finishPiece == true)
            {
                temp.push_back(chromoson.weightFinishPiece);
            }


       for (int i; i < temp.size(); i ++)
       {
           if( temp[i] > tmp)
           {
               tmp = temp[i];
           }

       }



        return tmp;

}








void ludo_evo_player::debugPrint(possibleMoves debug)
{
    std::cout << "piece " << debug.pieceNumber << std::endl;
    std::cout << "defend " << debug.defend << std::endl;
    std::cout << "finishPiece " << debug.finishPiece << std::endl;
    std::cout << "killFoe " << debug.killFoe << std::endl;
    std::cout << "leaveHouse " << debug.leaveHouse<< std::endl;
    std::cout << "moveforward " << debug.moveforward << std::endl;
    std::cout << "moveInGoal " << debug.moveInGoal << std::endl;
    std::cout << "moveToGlobe " << debug.moveToGlobe << std::endl;
    std::cout << "moveToGoal " << debug.moveToGoal << std::endl;
    std::cout << "moveToStar " << debug.moveToStar << std::endl;

}



possibleMoves ludo_evo_player::exploration(int pieceNumber)
{
    int index = pieceNumber;
    //int endPosition = dice_roll + pos_start_of_turn[index];
    possibleMoves currentPlayer;
    currentPlayer.pieceNumber = pieceNumber;
    currentPlayer.moveforward = posibleToMoveForward(index);
    currentPlayer.killFoe = posibleToKill(index);
    currentPlayer.defend = canIdefend(index);
    currentPlayer.finishPiece = endPiece(index);
    currentPlayer.moveInGoal = moveInFinish(index);
    currentPlayer.moveToGlobe = posibleToMoveToGlobe(index);
    currentPlayer.leaveHouse = leaveHomePossible(index);
    currentPlayer.moveToStar = posibleToMoveToStar(index);

    return currentPlayer;

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




bool ludo_evo_player::posibleToMoveForward(int peiceNumber) 
{
  if (pos_start_of_turn[peiceNumber] == 99)
        return false;
    if (pos_start_of_turn[peiceNumber] == -1)
        return false;
    if (pos_start_of_turn[peiceNumber] + dice_roll > 51)
        return false;
    return true;
	
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
    if(pos_start_of_turn[peiceNumber] == -1 && dice_roll == 6)
    {
        return true;
    }
     return false;

	
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

 


bool ludo_evo_player::moveToFinish(int peiceNumber)
{
	  int end_pos = dice_roll + pos_start_of_turn[peiceNumber];
    if (pos_start_of_turn[peiceNumber] > 51)
        return false;
    if (end_pos > 51)
        return true;
    return false;
}
	
	
	
	


bool ludo_evo_player::moveInFinish(int peiceNumber)
{
      if (pos_start_of_turn[peiceNumber] > 51)
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
    //bool skip = false;
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
    int end_pos = dice_roll + pos_start_of_turn[peiceNumber];
        if (end_pos > 51)
            return false;
        if (isGlobe(end_pos))
            return true;
        return false;

	
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


bool ludo_evo_player::endPiece(int pieceIndex)
{
    if(pos_start_of_turn[pieceIndex]+dice_roll == 56)
    {
        return true;
    }
    return false;
}


bool ludo_evo_player::isStar(int pieceIndex)
{
    if(pos_start_of_turn[pieceIndex] + dice_roll == 5 || pos_start_of_turn[pieceIndex] + dice_roll == 18 || pos_start_of_turn[pieceIndex] + dice_roll == 31 )
    {
        return true;
    }
    return false;


}


bool ludo_evo_player::posibleToMoveToStar(int peiceNumber)
{
    int end_pos = dice_roll + pos_start_of_turn[peiceNumber];
       if (end_pos > 51)
           return false;
       bool star = isStar(end_pos);
       //Check for block at the next star3
       if (star)
           end_pos = end_pos + 13;
       if (end_pos > 51)
           return false;
       int noEnemies = oppenentOnfield(end_pos);
       if (noEnemies > 0)
           return false;

       if (star)
           return true;
       return false;



}








void ludo_evo_player::randomizeWeight()
{



    for(int i = 0; i < 100; i ++)
    {

        chrom index;
        index.weightKillFoe= rand() % 100;
        index.weightMoveForward = rand() % 100;
        index.weightMoveToGlobe = rand() % 100;
        index.weightDefend = rand() % 100;
        index.weightLeaveHouse = rand() % 100;
        index.weightMoveToGoal = rand() % 100;
        index.weightMoveInGoal = rand() % 100;
        index.weightMoveToStar = rand() % 100;
        index.weightFinishPiece = rand() % 100;

        population.push_back(index);

    }
	


}





    
