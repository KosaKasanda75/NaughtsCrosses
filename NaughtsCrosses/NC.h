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

#define totalLvls 8
#define EASY 0
#define HARD 1

class NC {
public:
    NC();
    void drawfield(WINDOW * win);
    void resetMenuSelect();
    void chooseSize();
    int getSize();
    void chooseLevel();
    bool menuStage();
    bool checkMenu();
    bool winningCondition();
    void newmv(WINDOW * win);
    int getmv();
    bool tieCheck(WINDOW * win);
    void restart();
    void newGame();
    void hardEnd(WINDOW * win);
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
    bool menu;
    bool menu1;
    int highlight;
    int level;
};

NC::NC (){
    //size = s;
    //cells = (size * 2) - 1;
    menu = true;
    memset(digitalfield, 0, sizeof(digitalfield));
    continueGame = true;
    yPos = xPos = 1;
    turn = true; // naughts always start
    tie = false;
    winner = false;
}

void NC::drawfield(WINDOW * win){
    menu = false;
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
//=============================================================================================
void NC::resetMenuSelect(){
    highlight = 0;
}
//=============================================================================================
void NC::chooseSize(){
    const char* sizes[] = {"3x3", "4x4", "5x5", "6x6", "7x7", "8x8", "9x9", "10x10"};
    
    for (int i=0;i<totalLvls;i++){
        if (i == highlight)
            attron(A_STANDOUT);
        mvprintw(i, 0, sizes[i]);
        attroff(A_STANDOUT);
    }
}
//=============================================================================================
int NC::getSize(){
    return size;
}
//=============================================================================================
void NC::chooseLevel(){
    const char* levels[] = {"EASY", "HARD"};
    
    for (int i=0;i<2;i++){
        if (i == highlight)
            attron(A_STANDOUT);
        mvprintw(i, 0, levels[i]);
        attroff(A_STANDOUT);
    }
}
//=============================================================================================
bool NC::menuStage(){
    return menu1;
}
//=============================================================================================
bool NC::checkMenu(){
    return menu;
}
//=============================================================================================
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

    if (xArr+yArr < size-1){
        for (int i=0;i<=xArr+yArr;i++){ //Iterate through matrix
            for (int j=xArr+yArr;j>=0;j--){
                if (i+j == yArr+xArr){ //only analyse values on diagonal
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
    else {
        for (int i=(yArr+xArr)-(size-1);i<size;i++){ //Iterate through matrix
            for (int j=size-1;j>=(yArr+xArr)-(size-1);j--){
                if (i+j == yArr+xArr){ //only analyse values on diagonal
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
//=============================================================================================
void NC::newmv(WINDOW * win){
    
    for (int i=0;i<cells;i++){
        if (i%2 == 0){
            for (int j=0;j<cells;j++){
                if (j%2 != 0)
                    mvwprintw(win, i+1, j+1, "|");
                else {
                    if (yPos == i+1 && xPos == j+1)
                        wattron(win, A_STANDOUT);
                    if (level == EASY){
                        if (digitalfield[i/2][j/2] == emptySpace)
                            mvwprintw(win, i+1, j+1, " ");
                        else if (digitalfield[i/2][j/2] == naught)
                            mvwprintw(win, i+1, j+1, "O");
                        else if (digitalfield[i/2][j/2] == cross)
                            mvwprintw(win, i+1, j+1, "X");
                    }
                    else if (level == HARD)
                        mvwprintw(win, i+1, j+1, " ");
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
    
    //Print turn----------------
    move(0, 0);
    clrtoeol();
    if (turn)
        mvwprintw(stdscr, 0, 0, "O turn");
    else
        mvwprintw(stdscr, 0, 0, "X turn");
    if (level == EASY)
        mvprintw(1, 0, "Size: %d\tLevel: EASY", size);
    else if (level == HARD)
        mvprintw(1, 0, "Size: %d\tLevel: HARD", size);
    
    //Print array---------------
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
        if (level == HARD){
            hardEnd(win);
        }
    }
    
}
//=============================================================================================
int NC::getmv(){
    int choice = getch();
    switch (choice) {
        case KEY_UP:
            if (menu){
                highlight--;
                if (highlight<0)
                    highlight = 0;
            }
            else {
                yPos -= 2;
                if (yPos < 1)
                    yPos = 1;
            }
            break;
        case KEY_DOWN:
            if (menu && menu1){
                highlight++;
                if (highlight >= totalLvls)
                    highlight = totalLvls-1;
            }
            if (menu && !menu1){
                highlight++;
                if (highlight >= 2)
                    highlight = 2-1;
            }
            else {
                yPos += 2;
                if (yPos > cells)
                    yPos = cells;
            }
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
            if (menu) {
                if (menu1){
                    size = highlight + 3;
                    cells = (size * 2) - 1;
                    resetMenuSelect();
                    menu1 = false;
                    clear();
                }
                else{
                    switch (highlight) {
                        case 0:
                            level = EASY;
                            break;
                        case 1:
                            level = HARD;
                            break;
                        default:
                            break;
                    }
                    menu = false;
                    mvprintw(0, 0, "Size: %d\tLevel: %d", size, level);
                }
            }
            else {
                if (digitalfield[yPos/2][xPos/2] == emptySpace && continueGame){
                    if (turn)
                        digitalfield[yPos/2][xPos/2] = naught;
                    else
                        digitalfield[yPos/2][xPos/2] = cross;
                    turn = !turn;
                }
            }
            break;
        case 'r':
            restart();
            break;
        case 'n':
            newGame();
        default:
            break;
    }
    return choice;
}
//=============================================================================================
bool NC::tieCheck(WINDOW * win){
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
        hardEnd(win);
    }
    return tie;
}
//=============================================================================================
void NC::restart(){
    memset(digitalfield, 0, sizeof(digitalfield));
    turn = true;
    continueGame = true;
    winner = false;
}
//=============================================================================================
void NC::newGame(){
    clear();
    highlight = 0;
    menu = true;
    menu1 = true;
}
//=============================================================================================
void NC::hardEnd(WINDOW * win){
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
}

#endif /* NC_h */
