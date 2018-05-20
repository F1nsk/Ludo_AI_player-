#ifndef LUDO_EVO_PLAYER_H
#define LUDO_EVO_PLAYER_H

#include <QObject>
#include <iostream>
#include <random>
#include "positions_and_dice.h"


class ludo_evo_player: public QObject
{

    Q_OBJECT
private:
	
	struct possibleMoves 
	{
		int pieceNumber   // posible moves for the peice with this index 
		// the following parameteres describe wether it is possible to certian moves, is set to 'true' the move is possible and if set to 'false' the move is not possible 
		bool killFoe 	  //  
		bool moveforward
		bool moveToGlobe
		bool EnemyIsClose 
		bool defend 
		bool 
		
		
	}
	

    std::vector<int> pos_start_of_turn;
    std::vector<int> pos_end_of_turn;
    int dice_roll;
    float weights[];
    int make_decision();
    int currentPos;
    int nextPos;
    const int goalStretch = 51;
    const int goal = 99;
    const int GOAL = 56;
    const int home = -1;
    vector<int> MyPiecesPos;                   //container for my pieces
    vector<int> EnemyPiecesPos;                   //container for enemy pieces
	
    
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
