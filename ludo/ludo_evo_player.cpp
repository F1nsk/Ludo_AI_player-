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
    //std::cout << "winner is : " << winner << std::endl;

   if(winner == 0 )
   {
        currentWinner += 1;
        genWins +=1;

   }

    numberOfGamesPlayed  +=1;
    counter  += 1;

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
    population.clear();

//    debugPrintParents(parents[0]);
//    debugPrintParents(parents[1]);






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


void ludo_evo_player::timeForNewChildren()
{


    findChromWithBestScore();
    parentOne =  parents[0];
    parentTwo =  parents[1];
    parents.clear();
    std::cout << "==========parents  ================================================================================== " << std::endl;
    debugPrintChromWeights(parentOne);
    debugPrintChromWeights(parentTwo);


    chrom child;
    child.numberOfWins = 0;
    for(int i = 0; i < number_children ; i ++)
    {

    int midCounter = 0;


    int midPoint = (rand() % 9) + 1; // radom midpoint between 1 and 9


        if( midCounter != midPoint )
        {
           child.weightKillFoe =  parentOne.weightKillFoe;
           midCounter += 1;
        }
        else
        {
            child.weightKillFoe = parentTwo.weightKillFoe;
            midCounter += 1;
        }

        if( midCounter != midPoint )
        {
           child.weightMoveForward =  parentOne.weightMoveForward;
           midCounter += 1;
        }
        else
        {
            child.weightMoveForward = parentTwo.weightMoveForward;
            midCounter += 1;
        }

        if( midCounter != midPoint )
        {
           child.weightMoveToGlobe =  parentOne.weightMoveToGlobe;
           midCounter += 1;
        }
        else
        {
            child.weightMoveToGlobe = parentTwo.weightMoveToGlobe;
            midCounter += 1;
        }

        if( midCounter != midPoint )
        {
           child.weightDefend =  parentOne.weightDefend;
           midCounter += 1;
        }
        else
        {
            child.weightDefend = parentTwo.weightDefend;
            midCounter += 1;
        }

        if( midCounter != midPoint )
        {
           child.weightLeaveHouse =  parentOne.weightLeaveHouse;
           midCounter += 1;
        }
        else
        {
            child.weightLeaveHouse = parentTwo.weightLeaveHouse;
            midCounter += 1;
        }

        if( midCounter != midPoint )
        {
           child.weightMoveToGoal =  parentOne.weightMoveToGoal;
           midCounter += 1;
        }
        else
        {
            child.weightMoveToGoal = parentTwo.weightMoveToGoal;
            midCounter += 1;
        }


        if( midCounter != midPoint )
        {
           child.weightMoveInGoal =  parentOne.weightMoveInGoal;
           midCounter += 1;
        }
        else
        {
            child.weightMoveInGoal = parentTwo.weightMoveInGoal;
            midCounter += 1;
        }



        if( midCounter != midPoint )
        {
           child.weightMoveToStar =  parentOne.weightMoveToStar;
           midCounter += 1;
        }
        else
        {
            child.weightMoveToStar = parentTwo.weightMoveToStar;
            midCounter += 1;
        }


        if( midCounter != midPoint )
        {
           child.weightFinishPiece =  parentOne.weightFinishPiece;
           midCounter += 1;
        }
        else
        {
            child.weightFinishPiece = parentTwo.weightFinishPiece;
            midCounter += 1;
        }



            population.push_back(child);
        }

//    std::cout << "==========wiht mutated pop================================================================================== " << std::endl;
//        debugPrintPopulation(population);
//        std::cout << "============================================================================================ " << std::endl;

    for(int i = 0; i < number_random_children ; i ++)
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

//    std::cout << "==========with mutated pop================================================================================== " << std::endl;
//        debugPrintPopulation(population);
//        std::cout << "============================================================================================ " << std::endl;





}


void ludo_evo_player::rebuildPopulation()
{

     genCounter += 1;
     std::cout << " generation number " << genCounter  << "  number of wins " << genWins << std::endl;

   // std::cout << " here " << std::endl;
     genWins = 0;



    timeForNewChildren();







   // st:cout << " making new pop " << std::endl;



//    std::cout << "==========next pop================================================================================== " << std::endl;
//    debugPrintPopulation(population);
//    std::cout << "============================================================================================ " << std::endl;

}





float ludo_evo_player::findHighScoreMove(possibleMoves player)
{


   static int currentChromoson = 0;
    std::vector<float>  temp;

    float bestMove = 0;

    chrom chromoson;

   if(counter >= number_of_games_with_chrom) //  for changing chromoson
   {
       //debugPrintChromWeights(population[currentChromoson]);
       currentChromoson = currentChromoson + 1;
       population[currentChromoson].numberOfWins = currentWinner;
       currentWinner =0;
       counter = 0;

   }
   if(currentChromoson >= population_size) // loop for changing population
   {
       std::cout << " evolution "<< std::endl;
       rebuildPopulation();
       currentChromoson = 0;



   }
   chromoson  = population[currentChromoson];



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



void ludo_evo_player::debugPrintPopulation(std::vector<chrom> debug)
{
    for(int i = 0; i < debug.size() ; i++ )
    {
    std::cout << debug[i].numberOfWins << "  " <<   debug[i].weightDefend << "  " << debug[i].weightFinishPiece << "  " << debug[i].weightLeaveHouse << "  " << debug[i].weightMoveForward << "  " << debug[i].weightMoveInGoal << "  " << debug[i].weightMoveToGlobe << "  " << debug[i].weightMoveToGoal << "   " <<   debug[i].weightMoveToGoal   << "  " <<  debug[i].weightMoveToStar << std::endl;
    }


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
//    std::cout << "win number " << debug.numberOfWins << std::endl;
//    std::cout << " Weight for defend " << debug.weightDefend << std::endl;
//    std::cout << " Weight for finishPiece " << debug.weightFinishPiece << std::endl;
//    std::cout << " Weight for killFoe " << debug.weightKillFoe << std::endl;
//    std::cout << " Weight for leaveHouse " << debug.weightLeaveHouse<< std::endl;
//    std::cout << " Weight for moveforward " << debug.weightMoveForward << std::endl;
//    std::cout << " Weight for moveInGoal " << debug.weightMoveInGoal << std::endl;
//    std::cout << " Weight for moveToGlobe " << debug.weightMoveToGlobe << std::endl;
//    std::cout << " Weight for moveToGoal " << debug.weightMoveToGoal << std::endl;
//    std::cout << " Weight for moveToStar " << debug.weightMoveToStar << std::endl;

    std::cout << debug.numberOfWins << "  " <<   debug.weightDefend << "  " << debug.weightFinishPiece << "  " << debug.weightLeaveHouse << "  " << debug.weightMoveForward << "  " << debug.weightMoveInGoal << "  " << debug.weightMoveToGlobe << "  " << debug.weightMoveToGoal << "   " <<   debug.weightMoveToGoal   << "  " <<  debug.weightMoveToStar << std::endl;





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



    for(int i = 0; i < population_size ; i ++)
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

//    std::cout << "==========First pop================================================================================== " << std::endl;
//    debugPrintPopulation(population);

//    std::cout << "============================================================================================ " << std::endl;




}



