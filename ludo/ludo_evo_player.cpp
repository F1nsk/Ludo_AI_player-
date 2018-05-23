#include "ludo_evo_player.h"
#include <random>

ludo_evo_player::ludo_evo_player():
    pos_start_of_turn(16),
    pos_end_of_turn(16),
    dice_roll(0)
{
    randomizeWeight();
}

float ludo_evo_player::findPlayerWithBestScore(std::vector<float> scores)
{
    float bestScore;
    for (int i = 0; i < scores.size(); i++)
        {
       // std::cout<< "Best score of piece " << i << " valued at: " << scoreVector[i] << "\n";
            if (scores[i] > bestScore)
                bestScore = scores[i];
        }

    return bestScore;


}

void ludo_evo_player::gameCounter(int winner)
{
    std::cout << "winner is : " << winner << std::endl;

   if(winner == 0 )
   {
        currentWinner = currentWinner + 1;
   }

    numberOfGamesPlayed = numberOfGamesPlayed +1;
    counter = counter + 1;

}

int ludo_evo_player::make_decision()
{
       float temp = 0;
       possibleMoves p1 = exploration(0);
       possibleMoves p2 = exploration(1);
       possibleMoves p3 = exploration(2);
       possibleMoves p4 = exploration(3);
       float scoreOne =  findHighScoreMove(p1);
       float scoreTwo = findHighScoreMove(p2);
       float scoreThree = findHighScoreMove(p3);
       float scoreFour = findHighScoreMove(p4);
    //    std::cout << " tmp "  << scoreThreer << std::endl
       scoreKeeper = {scoreOne, scoreTwo, scoreThree, scoreFour};


      temp = findPlayerWithBestScore(scoreKeeper);

      if(scoreOne == temp)
      {
          return 0;
      }
      if (scoreTwo == temp)
      {

          return 1;
      }
      if (scoreThree == temp)
      {
          return 2;
      }
      if (scoreFour == temp )
      {
          return 3;
      }




    return -1;

 }

bool ludo_evo_player::inBase(int peiceIndex)
{
    if(pos_start_of_turn[peiceIndex] == 99)
    {
        return true;

    }

    return false;

}

void ludo_evo_player::findChromWithBestScore()
{



    std::sort (population.begin(), population.end(), sorter());


    parents.push_back(population[99]);
    parents.push_back(population[98]);

    debugPrintParents(parents[0]);
    debugPrintParents(parents[1]);






}

void ludo_evo_player::debugPrintParents(chrom debug)
{

    std::cout << "win number " << debug.numberOfWins << std::endl;
    std::cout << " Weight for defend " << debug.weightDefend << std::endl;
    std::cout << " Weight for finishPiece " << debug.weightFinishPiece << std::endl;
    std::cout << " Weight for killFoe " << debug.weightKillFoe << std::endl;
    std::cout << " Weight for leaveHouse " << debug.weightLeaveHouse<< std::endl;
    std::cout << " Weight for moveforward " << debug.weightMoveForward << std::endl;
    std::cout << " Weight for moveInGoal " << debug.weightMoveInGoal << std::endl;
    std::cout << " Weight for moveToGlobe " << debug.weightMoveToGlobe << std::endl;
    std::cout << " Weight for moveToGoal " << debug.weightMoveToGoal << std::endl;
    std::cout << " Weight for moveToStar " << debug.weightMoveToStar << std::endl;





}





float ludo_evo_player::findHighScoreMove(possibleMoves player)
{


   static int currentChromoson = 0;
    std::vector<float>  temp;

    float bestMove = 0;

    chrom chromoson;

   if(counter >= 10)
   {
       currentChromoson = currentChromoson + 1;
       std::cout << " we changed Chrom to " << currentChromoson  << std::endl;
       counter = 0;

   }
   chromoson  = population[currentChromoson];
   population[currentChromoson].numberOfWins = currentWinner;


   // debugPrintChromWeights(chromoson);
   possibleMoves tempPlayer;
   tempPlayer = player;

         if (tempPlayer.killFoe == true && inBase(player.pieceNumber) != true )
            {

            temp.push_back(chromoson.weightKillFoe);
            }

         if(tempPlayer.moveforward == true && inBase(player.pieceNumber) != true)
            {
                temp.push_back(chromoson.weightMoveForward);
            }

         if(tempPlayer.moveToGlobe == true && inBase(player.pieceNumber) != true)
            {
                temp.push_back(chromoson.weightMoveToGlobe);
            }
         if(tempPlayer.defend == true && inBase(player.pieceNumber) != true)
            {
                temp.push_back(chromoson.weightDefend);
            }

        if(tempPlayer.leaveHouse == true && inBase(player.pieceNumber) != true)
            {
                temp.push_back(chromoson.weightLeaveHouse);
            }

        if(tempPlayer.moveToGoal == true && inBase(player.pieceNumber) != true)
            {
                temp.push_back(chromoson.weightMoveToGlobe);
            }
        if(tempPlayer.moveInGoal == true && inBase(player.pieceNumber) != true)
            {
                temp.push_back(chromoson.weightMoveInGoal);
            }
        if(tempPlayer.moveToStar == true && inBase(player.pieceNumber) != true)
            {
                temp.push_back(chromoson.weightMoveToStar);
            }
        if(tempPlayer.finishPiece == true && inBase(player.pieceNumber) != true)
            {
                temp.push_back(chromoson.weightFinishPiece);
            }

        for (int i = 0; i < temp.size(); i++)
          {
              if (temp[i] > bestMove)
                  bestMove = temp[i];

          }



       return bestMove;






}








void ludo_evo_player::debugPrintPossibleMoves(possibleMoves debug)
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


void ludo_evo_player::debugPrintChromWeights(chrom debug)
{
    std::cout << "win number " << debug.numberOfWins << std::endl;
    std::cout << " Weight for defend " << debug.weightDefend << std::endl;
    std::cout << " Weight for finishPiece " << debug.weightFinishPiece << std::endl;
    std::cout << " Weight for killFoe " << debug.weightKillFoe << std::endl;
    std::cout << " Weight for leaveHouse " << debug.weightLeaveHouse<< std::endl;
    std::cout << " Weight for moveforward " << debug.weightMoveForward << std::endl;
    std::cout << " Weight for moveInGoal " << debug.weightMoveInGoal << std::endl;
    std::cout << " Weight for moveToGlobe " << debug.weightMoveToGlobe << std::endl;
    std::cout << " Weight for moveToGoal " << debug.weightMoveToGoal << std::endl;
    std::cout << " Weight for moveToStar " << debug.weightMoveToStar << std::endl;






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
     int tempcounter = 0;
    //bool skip = false;
    for (int i = 4; i < pos_start_of_turn.size(); i++)
    {
            if (pos_start_of_turn[i] == position)
                tempcounter++;
    }
    return tempcounter;


}



bool ludo_evo_player::friendlyOnfield(int position)
{
     int tempcounter = 0;
    for (int i = 0; i < 4; i++)
    {
        if (pos_start_of_turn[i] == position)
            tempcounter++;
    }
    return tempcounter;
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



