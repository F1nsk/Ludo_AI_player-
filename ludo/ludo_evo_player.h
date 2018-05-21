#ifndef LUDO_EVO_PLAYER_H
#define LUDO_EVO_PLAYER_H

#include <QObject>
#include <iostream>
#include <random>
#include "positions_and_dice.h"
#include <vector>  



struct possibleMoves
{
    int pieceNumber;   // posible moves for the peice with this index
    // the following parameteres describe wether it is possible to certian moves, is set to 'true' the move is possible and if set to 'false' the move is not possible
    bool killFoe; 	  //
    bool moveforward;
    bool moveToGlobe;
    //bool EnemyIsClose;
    bool defend;
    bool leaveHouse;
    bool moveToGoal;
    bool moveInGoal;
    bool moveToStar;
    bool finishPiece;



};

struct chrom // the chromoson
{
    int numberOfWins = 0;
    float weightKillFoe = 0.00;
    float weightMoveForward = 0.00;
    float weightMoveToGlobe = 0.00;
    float weightDefend = 0.00;
    float weightLeaveHouse = 0.00;
    float weightMoveToGoal = 0.00;
    float weightMoveInGoal = 0.00;
    float weightMoveToStar = 0.00;
    float weightFinishPiece = 0.00;




};
class ludo_evo_player: public QObject
{




    Q_OBJECT
private:



    std::vector<chrom> population;

    std::vector<int> pos_start_of_turn;
    std::vector<int> pos_end_of_turn;
    int mycolor;
    int dice_roll =0;
   // float weights[];
    int make_decision();
    int currentPos;
    int nextPos;
    const int goalStretch = 51;
    const int goal = 99;
    const int GOAL = 56;
    const int home = -1;
    std::vector<int> MyPiecesPos;                   //container for my pieces
    std::vector<int> EnemyPiecesPos;//container for enemy pieces
    std::vector<float> playerOne;
    std::vector<float> playerTwo;
    std::vector<float> playerThree;
    std::vector<float> playFour;
    std::vector<float> scoreKeeper;
	
    
    // ************************************************************************************************
    // functions  to explore the board 
    // ************************************************************************************************
    bool isEnemyBehind(int peiceNumber);  // check is enemy player is within striking range 
    bool isInGoal(int peiceNumber); // is play in goal stretch 
    bool canIdefend(int peiceNumber);  //
    bool canIenterBoard(int peiceNumber); //
    bool posibleToKill(int peiceNumber); 
    bool isPositionBlocked(int peiceNumber); // check if two players are already on the spot 
    void getPlayersPos(); 
    bool moveToFinish(int peiceNumber); 
    bool moveInFinish(int peiceNumber);
    bool leaveHomePossible(int peiceNumber);
    bool oppenentOnfield(int position);
    bool friendlyOnfield(int position);
    bool posibleToMoveForward(int peiceNumber); 
    bool posibleToMoveToGlobe(int peiceNumber); 
    bool posibleToMoveToStar(int peiceNumber);
    bool isGlobe(int position);
    bool endPiece(int pieceIndex);
    bool isStar(int pieceIndex);
    possibleMoves exploration(int pieceNumber); // this function finds all the possibel moves and  updates the possibilities list
    // ************************************************************************************************
    // debug
    // ************************************************************************************************
    void debugPrint(possibleMoves debug);
   
    // ************************************************************************************************
    // Genetic algorithm  function
    // ************************************************************************************************
    void randomizeWeight();
    float findHighScoreMove(possibleMoves player);
	// ************************************************************************************************
	// actions 
	// ************************************************************************************************
	//~ void killEnemy(); 
	//~ void normalMove(); 
	//~ void defendFriend();
	//~ void MoveOutofhome(); 
	//~ void moveToStar(); 
	//~ void moveToGlobe();  
	//~ void moveTosafeZone(); 
	
	
	
    //game states as funtions








public:
    ludo_evo_player();

signals:
    void select_piece(int);
    void turn_complete(bool);
public slots:
    void start_turn(positions_and_dice relative);
    void post_game_analysis(std::vector<int> relative_pos);

};

#endif // LUDO_EVO_PLAYER_H
