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
    
    mvprintw(0, 0, "Enter field size (max 10): ");
    refresh();
    int c;
    scanf("%d", &c);
    
    NC game1(c);
    
    int yStart, xStart;
    
    getmaxyx(stdscr, yStart, xStart);
    
    WINDOW * gamewin = newwin((c+1)*2, (c+1)*2, yStart/6, xStart/3);
    refresh();
    box(gamewin, 0, 0);
    game1.drawfield(gamewin);
    wrefresh(gamewin);
    
    while (game1.getmv() != 'x'){
        game1.newmv(gamewin);
        game1.tieCheck();
        wrefresh(gamewin);
    }
    
}
