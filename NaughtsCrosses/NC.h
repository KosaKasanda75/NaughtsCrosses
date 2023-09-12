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
    
    for (int i=0;i<cells;i++){
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
    
    int yArr, xArr;
    yArr = yPos/2;
    xArr = xPos/2;
    
    int Hthree, Vthree, Dnthree, Dpthree;
    Hthree = Vthree = Dnthree = Dpthree = 0;
    
    int who;
    if (!turn)
        who = naught;
    else
        who = cross;
    
    //HORIZONTAL=================================================================
    for (int i=0;i<size;i++){
        if (digitalfield[yArr][i] == who)
            Hthree++;
        else
            Hthree = 0;
        if (Hthree == 3){
            winner = true;
            return winner;
        }
    }
    //VERTICAL==================================================================
    for (int i=0;i<size;i++){
        if (digitalfield[i][xArr] == who)
            Vthree++;
        else
            Vthree = 0;
        if (Vthree == 3){
            winner = true;
            return winner;
        }
    }
    //DIAGONAL NEGATIVE==========================================================
    if (xArr > yArr){
        for (int i=0;i<size-(xArr-yArr);i++){ //Iterate through matrix
            for (int j=xArr-yArr;j<size;j++){
                if (j-i == xArr-yArr){ //only analyse values on diagonal
                    if (digitalfield[i][j] == who)
                        Dnthree++;
                    else
                        Dnthree = 0;
                    if (Dnthree == 3){
                        winner = true;
                        return winner;
                    }
                }
            }
        }
    }
    else {
        for (int i=yArr-xArr;i<size;i++){ //Iterate through matrix
            for (int j=0;j<size-(yArr-xArr);j++){
                if (i-j == yArr-xArr){ //only analyse values on diagonal
                    if (digitalfield[i][j] == who)
                        Dnthree++;
                    else
                        Dnthree = 0;
                    if (Dnthree == 3){
                        winner = true;
                        return winner;
                    }
                }
            }
        }
    }
    //DIAGONAL POSITIVE==========================================================

    if (xArr > yArr){
        for (int i=0;i<size-(xArr-yArr);i++){ //Iterate through matrix
            for (int j=size-(xArr-yArr);j>=0;j--){
                if (size-(j-i) == size-(xArr-yArr)){ //only analyse values on diagonal
                    if (digitalfield[i][j] == who)
                        Dpthree++;
                    else
                        Dpthree = 0;
                    mvprintw(1, 0, "Coord: %d, %d", i, j);
                    getch();
                    if (Dpthree == 3){
                        winner = true;
                        return winner;
                    }
                }
            }
        }
    }
    else {
        for (int i=yArr-xArr;i<size;i++){ //Iterate through matrix
            for (int j=size;j<=yArr-xArr;j--){
                if (i-j == yArr-xArr){ //only analyse values on diagonal
                    if (digitalfield[i][j] == who)
                        Dpthree++;
                    else
                        Dpthree = 0;
                    if (Dpthree == 3){
                        winner = true;
                        return winner;
                    }
                }
            }
        }
    }
    
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
    
    //Print turn
    move(0, 0);
    clrtoeol();
    if (turn)
        mvwprintw(stdscr, 0, 0, "O turn");
    else
        mvwprintw(stdscr, 0, 0, "X turn");
    
    //Print array
    for (int k=0;k<size;k++){
        for (int l=0;l<size;l++){
            mvwprintw(stdscr, 18+k, l, "%d", digitalfield[k][l]);
        }
    }
    
    winningCondition();
    if (winner){
        if (!turn)
            mvprintw(0, 0, "O Wins");
        else
            mvprintw(0, 0, "X Wins");
        continueGame = false;
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
            if (digitalfield[yPos/2][xPos/2] == emptySpace && continueGame){
                if (turn)
                    digitalfield[yPos/2][xPos/2] = naught;
                else
                    digitalfield[yPos/2][xPos/2] = cross;
                turn = !turn;
            }
            break;
        case 'r':
            restart();
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
    continueGame = true;
    winner = false;
}

#endif /* NC_h */
