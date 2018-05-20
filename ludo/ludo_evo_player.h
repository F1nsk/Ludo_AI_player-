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
    
    // ************************************************************************************************
    // functions  to explore the board 
    // ************************************************************************************************
    bool isEnemyBehind(currentPos);  // check is enemy player is within striking range 
    bool isInGoal(currentPos); // is play in goal stretch 
    bool canIdefend(currentPos);  //
    bool canIenterBoard(); //
    bool posibleToKill(); 
    bool isPositionBlocked(); // check if two players are already on the spot 
   
   
   
	// ************************************************************************************************
	// actions 
	// ************************************************************************************************
	void killEnemy(); 
	void normalMove(); 
	void defendFriend();
	void MoveOutofhome(); 
	void moveToStar(); 
	void moveToGlobe();  
	void moveTosafeZone(); 
	
	
	
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
