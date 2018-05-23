#include "dialog.h"
#include <QApplication>
#include "game.h"
#include <vector>
#include "ludo_player.h"
#include "ludo_player_random.h"
#include "ludo_evo_player.h"
#include "positions_and_dice.h"

Q_DECLARE_METATYPE( positions_and_dice )

int main(int argc, char *argv[]){
    bool debug = 1;
    QApplication a(argc, argv);
    qRegisterMetaType<positions_and_dice>();

    //instanciate the players here
    //ludo_player p1, p2;
    ludo_evo_player p1;
    if(debug) std::cout << "ludo player created"<< std::endl;
    ludo_player_random p2, p3, p4;
    if(debug) std::cout << "all players created" << std::endl;
    ludo_evo_player * p1Ptr = &p1;
    ludo_player_random    * p2Ptr = &p2;
    ludo_player_random    * p3Ptr = &p3;
    ludo_player_random    * p4Ptr = &p4;
    if(debug) std::cout << "Pointers to players created" << std::endl;

    game g;
    g.setGameDelay(000); //if you want to see the game, set a delay
    if(debug) std::cout << "Game start" << std::endl;


    /*//Add a GUI <-- remove the '/' to uncomment block
    Dialog w;
    QObject::connect(&g,SIGNAL(update_graphics(std::vector<int>)),&w,SLOT(update_graphics(std::vector<int>)));
    QObject::connect(&g,SIGNAL(set_color(int)),                   &w,SLOT(get_color(int)));
    QObject::connect(&g,SIGNAL(set_dice_result(int)),             &w,SLOT(get_dice_result(int)));
    QObject::connect(&g,SIGNAL(declare_winner(int)),              &w,SLOT(get_winner()));
    QObject::connect(&g,SIGNAL(close()),&a,SLOT(quit()));
    w.show();
    if(debug) cout << "Dialog is open" << endl;
    /*/ //Or don't add the GUI
    QObject::connect(&g,SIGNAL(close()),&a,SLOT(quit()));
    //*/
    g.add_players(p1Ptr, p2Ptr, p3Ptr, p4Ptr);
    g.init_games();
    if(debug) std::cout << "Game is init" << std::endl;
    QApplication * aPtr;
    aPtr = &a;

    g.runUserDef(aPtr);
    g.start();
    a.exec();
//    g.reset();

    return 0;
}
