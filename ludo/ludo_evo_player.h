#ifndef LUDO_EVO_PLAYER_H
#define LUDO_EVO_PLAYER_H
#include <QObject>
#include <iostream>
#include <random>
#include "positions_and_dice.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <list>



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


struct sorter {
  inline bool operator() (chrom& i, chrom& j) { return (i.numberOfWins<j.numberOfWins);}
};




class ludo_evo_player : public QObject {
    Q_OBJECT
private:

    std::vector<chrom> population;
    std::vector<chrom> parentKeeper;
    int counter = 0;
    int currentWinner = 0;
    int numberOfGamesPlayed = 0;
    std::vector<int> pos_start_of_turn;
    std::vector<int> pos_end_of_turn;
    int dice_roll;
    int make_decision();
    int currentPos;
    int nextPos;
    const int goalStretch = 51;
    const int endOFGoal = 99;
    const int GOAL = 56;
    const int home = -1;
    std::vector<float> scoreKeeper;
    std::vector<chrom> parents;

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
    bool inBase(int peiceIndex);
    possibleMoves exploration(int pieceNumber); // this function finds all the possibel moves and  updates the possibilities list
    // ************************************************************************************************
    // debug
    // ************************************************************************************************
    void debugPrintPossibleMoves(possibleMoves debug);
    void debugPrintChromWeights(chrom debug);
    void debugPrintParents(chrom debug);

    // ************************************************************************************************
    // Genetic algorithm  function
    // ************************************************************************************************
    void randomizeWeight();
    float findHighScoreMove(possibleMoves player);
    float findPlayerWithBestScore(std::vector<float> scores);
    void  findChromWithBestScore();
    chrom timeForNewChildren();
    void rebuildPopulation();




public:
    ludo_evo_player();

signals:
    void select_piece(int);
    void turn_complete(bool);
public slots:
    void start_turn(positions_and_dice relative);
    void post_game_analysis(std::vector<int> relative_pos);
    void gameCounter(int winner);
};

#endif // LUDO_EVO_PLAYER_H
