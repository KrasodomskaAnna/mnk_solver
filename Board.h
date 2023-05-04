#ifndef MNKSOLVER_BOARD_H
#define MNKSOLVER_BOARD_H

#include <iostream>
#include <string>

#define DEFAULT_ARRAY_SIZE 9
#define MAX_COMMAND_STRENGTH 40
#define NONE_POSITION -1

class Board {
public:
    int x, y, k, player;
    int* array;
    int arraySize = DEFAULT_ARRAY_SIZE;
    Board() {
        this->array = new int[arraySize]();
    }
    char* cinBoard() {
        static char toExecute[MAX_COMMAND_STRENGTH];
        toExecute[0] = '\0';
        scanf("%s %d %d %d %d", toExecute, &y, &x, &k, &player);
        if(x * y > arraySize) makeBiggerArray(x * y);

        for(int ro = 0; ro < y; ro++) {
            for(int col = 0; col < x; col++)
                scanf("%d", &array[ro * x + col]);
        }
        return toExecute;
    }
    void printBoard() const {
        for(int ro = 0; ro < y; ro++) {
            for(int col = 0; col < x; col++)
                printf("%d ", array[ro * x + col]);
            printf("\n");
        }
    }
    void makeBiggerArray(int size) {
        int* newArray = new int[size]();
        delete[] this->array;
        this->array = newArray;
        this->arraySize = size;
    }
    bool checkIsOnBoard(int position) {
        return position >= 0 && position < x * y;
    }
    int getOponentPlayer() {
        return player == 1 ? 2 : 1;
    }
    int getNextFreePosition(int id) {
        int newPos = id+1;
        if(!checkIsOnBoard(newPos))
            return NONE_POSITION;
        while(array[newPos]) {
            if(!checkIsOnBoard(newPos))
                return NONE_POSITION;
            newPos++;
        }
        return newPos;
    }
    int getColumn(int position) {
        return position%x;
    }
    int getRow(int position) {
        return position/x;
    }
    ~Board(){
        delete[] array;
    }
};

#endif //MNKSOLVER_BOARD_H
