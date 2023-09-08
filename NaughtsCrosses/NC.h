//
//  NC.h
//  NaughtsCrosses
//
//  Created by Kosa Kasanda on 08.09.23.
//

#ifndef NC_h
#define NC_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <ncurses.h>

#define MAXsize 10
#define emptySpace 0
#define naught 1
#define cross 2

class NC {
public:
    NC(int s);
    void drawfield(WINDOW * win);
    bool winningCondition();
    void newmv(WINDOW * win);
    int getmv();
    bool tieCheck();
    void restart();
private:
    bool continueGame;
    bool winner;
    bool tie;
    bool turn;
    int size;
    int cells;
    int yWin, xWin;
    int yPos, xPos;
    int digitalfield[MAXsize][MAXsize];
};

NC::NC (int s){
    size = s;
    cells = (size * 2) - 1;
    memset(digitalfield, 0, sizeof(digitalfield));
    continueGame = true;
    yPos = xPos = 1;
    turn = true; // naughts always start
    tie = false;
    winner = false;
}

void NC::drawfield(WINDOW * win){
    getbegyx(win, yWin, xWin);
    mvprintw(2, 0, "ywin: %d, xwin: %d", yWin, xWin);
    
    for (int i=0;i<cells;i++){
        mvprintw(3, i, "%d ", i);
        if (i%2 == 0){
            for (int j=0;j<cells;j++){
                if (j%2 != 0)
                    mvwprintw(win, i+1, j+1, "|");
            }
        }
        else{
            for (int j=0;j<cells;j++){
                mvwprintw(win, i+1, j+1, "-");
            }
        }
    }
}

bool NC::winningCondition(){
    return winner;
}

void NC::newmv(WINDOW * win){
    
    for (int i=0;i<cells;i++){
        if (i%2 == 0){
            for (int j=0;j<cells;j++){
                if (j%2 != 0)
                    mvwprintw(win, i+1, j+1, "|");
                else {
                    if (yPos == i+1 && xPos == j+1)
                        wattron(win, A_STANDOUT);
                    if (digitalfield[i/2][j/2] == emptySpace)
                        mvwprintw(win, i+1, j+1, " ");
                    else if (digitalfield[i/2][j/2] == naught)
                        mvwprintw(win, i+1, j+1, "O");
                    else if (digitalfield[i/2][j/2] == cross)
                        mvwprintw(win, i+1, j+1, "X");
                }
                wattroff(win, A_STANDOUT);
            }
        }
        else{
            for (int j=0;j<cells;j++){
                mvwprintw(win, i+1, j+1, "-");
            }
        }
    }
    
    
    move(0, 0);
    clrtoeol();
    //mvwprintw(stdscr, 0, 0, "y:%d , x:%d", yPos, xPos);
    if (turn)
        mvwprintw(stdscr, 0, 0, "O turn");
    else
        mvwprintw(stdscr, 0, 0, "X turn");
    
    
    for (int k=0;k<size;k++){
        for (int l=0;l<size;l++){
            mvwprintw(stdscr, 18+k, l, "%d", digitalfield[k][l]);
        }
    }
    
}

int NC::getmv(){
    int choice = getch();
    switch (choice) {
        case KEY_UP:
            yPos -= 2;
            if (yPos < 1)
                yPos = 1;
            break;
        case KEY_DOWN:
            yPos += 2;
            if (yPos > cells)
                yPos = cells;
            break;
        case KEY_LEFT:
            xPos -= 2;
            if (xPos < 1)
                xPos = 1;
            break;
        case KEY_RIGHT:
            xPos += 2;
            if (xPos > cells)
                xPos = cells;
            break;
        case 'g':
            if (digitalfield[yPos/2][xPos/2] == emptySpace && !tie){
                if (turn)
                    digitalfield[yPos/2][xPos/2] = naught;
                else
                    digitalfield[yPos/2][xPos/2] = cross;
                turn = !turn;
            }
            break;
        case 'r':
            restart();
            continueGame = true;
            break;
        default:
            break;
    }
    return choice;
}

bool NC::tieCheck(){
    tie = true;
    for (int i=0;i<size;i++){
        for (int j=0;j<size;j++){
            if (digitalfield[i][j] == 0)
                tie = false;
        }
    }
    if (tie){
        continueGame = false;
        mvprintw(0, 0, "Game is a tie");
    }
    return tie;
}

void NC::restart(){
    memset(digitalfield, 0, sizeof(digitalfield));
    turn = true;
}

#endif /* NC_h */
