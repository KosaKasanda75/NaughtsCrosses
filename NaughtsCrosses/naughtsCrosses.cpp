//
//  naughtsCrosses.cpp
//  NaughtsCrosses
//
//  Created by Kosa Kasanda on 08.09.23.
//

#include <iostream>
#include <stdio.h>
#include <string>
#include <ncurses.h>

#include "naughtsCrosses.hpp"
#include "NC.h"



void naughtsCrosses(){
    
    NC game1;
    
    while (game1.getmv() != 'x'){ //these conditional statements create a lot of clicking between stages
        game1.newGame(); //need to come here when we press 'n'
        while (game1.getmv() != 'x' && game1.checkMenu()){
            if (game1.menuStage())
                game1.chooseSize();
            else
                game1.chooseLevel();
        }
        clear();
        
        int yStart, xStart;
        int c = game1.getSize();
        
        getmaxyx(stdscr, yStart, xStart);
        
        WINDOW * gamewin = newwin((c+1)*2, (c+1)*2, yStart/6, xStart/3);
        refresh();
        box(gamewin, 0, 0);
        game1.drawfield(gamewin);
        wrefresh(gamewin);
        game1.newmv(gamewin);
        
        while (game1.getmv() != 'x'){
            game1.newmv(gamewin);
            game1.tieCheck(gamewin); //does not take into account if last move of game = winning move
            wrefresh(gamewin);
        }
        
        delwin(gamewin);
    }
    
    
}
