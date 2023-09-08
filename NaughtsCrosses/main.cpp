//
//  main.cpp
//  NaughtsCrosses
//
//  Created by Kosa Kasanda on 29.08.23.
//

#include <iostream>
#include <stdio.h>
#include <string>
#include <ncurses.h>

#include "naughtsCrosses.hpp"

int main(int argc, const char * argv[]) {
    
    initscr();
    noecho();
    curs_set(0);
    
    keypad(stdscr, true);
    start_color();
    
    naughtsCrosses();
    
    endwin();
    
}
