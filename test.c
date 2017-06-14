//
// Created by zurek on 3/12/2017.
//

#include<stdio.h>
#include <stdbool.h>

#define MOVES 8
#define LIMIT 1000000

//funkcia kontrolujuca hranice hracej plochy a ci su hracie policka uz obsadene
bool outOfBounds(int n,int x,int y,int chessBoard[n][n]) {return (x>=0 && x<n && y>=0 && y<n && chessBoard[x][y]==-1);}
int i=0;

//funkcia vypisujuca vysledok riesenia programu
void printSolution(int n,int chessBoard[n][n]) {
    for(int x=0;x<n;++x) {
        for(int y=0;y<n;++y) printf(" %2d ",chessBoard[x][y]);
        printf("\n");
    }
    printf("\n");
}

//Rekurzivna funkcia hladajuca pomocou backtrackingu spravne riesenie
bool findPath(int n,int x,int y,int move,int chessBoard[n][n],int xMove[n],int yMove[n]) {
    int k,next_x,next_y;

    if(i>LIMIT) return false;
    if (move==n*n) return true;
    for (k=0;k<MOVES;++k) {                       //vyskusaju sa vsetky pohyby z aktualnych suradnic
        ++i;
        next_x=x+xMove[k];
        next_y=y+yMove[k];
        if (outOfBounds(n,next_x,next_y,chessBoard)){
            chessBoard[next_x][next_y]=move;
            if (findPath(n,next_x,next_y,move+1,chessBoard,xMove,yMove)==true) return true;
            else chessBoard[next_x][next_y]=-1;
        }
    }

    return false;
}

bool solveKT(int n,int horse_x,int horse_y) {
    int chessBoard[n][n];
    i=0;

    for(int x=0;x<n;++x) {                  //Inicializacia matice hracej plochy
        for (int y=0;y<n;++y)chessBoard[x][y]=-1;
    }

    int xMove[MOVES]={2,1,-1,-2,-2,-1,1,2};   // xMove[] a yMove[] definuju dalsie pohyby kona
    int yMove[MOVES]={1,2,2,1,-1,-2,-2,-1};

    chessBoard[horse_x][horse_y]=0;         //Kon je inicializovany na danej pozicii na hracej ploche

    if (findPath(n,horse_x,horse_y,1,chessBoard,xMove,yMove)==false){   //Zaciname od horse_x a horse_y a objavime vsetky cesty pomocou funkcie findPath
        printf("Privelmi velky pocet krokov alebo ziadne riesenie neexistuje!\n");
        return false;
    }
    else printSolution(n,chessBoard);       //ak vsetko zbehlo spravne vypise sa riesenie do terminala
    return true;
}

int main() {                                //funkcia main ktora inicializuje rozmery sachovnice a suradnice kona
    //5x5 sachovnice
    printf("5x5 rozmerne sachovnice\n\n");
    solveKT(5,4,0);
    solveKT(5,4,4);
    solveKT(5,2,2);
    solveKT(5,3,2);
    solveKT(5,1,4);

    //6x6 sachovnice
    printf("6x6 rozmerne sachovnice\n\n");
    solveKT(6,5,0);
    solveKT(6,3,2);
    solveKT(6,4,4);
    solveKT(6,1,4);
    solveKT(6,2,2);
    return 0;
}