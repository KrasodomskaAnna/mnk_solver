#ifndef MNKSOLVER_ENGINE_H
#define MNKSOLVER_ENGINE_H

#include "Board.h"
#include "Node.h"
#include "Vector.h"
#include "utils.h"

#define MAX_SCORE 10
#define POSITION_ERROR -1

class Engine {
public:
    Engine() {
        this->board = new Board();
        this->solutions = new Vector<Node*>;
    }
    Vector<Node*>* solutions;
    Board* board;

    void generateMoves(bool generateWinningOnly) {
        if(isInitialisedBoardWin()) return;
        for(int ro = 0; ro < board->y; ro++) {
            for(int col = 0; col < board->x; col++) {
                int pos = getPos(col, ro);
                if(board->array[pos]) continue;
                if(generateWinningOnly) {
                    board->array[pos] = board->player;
                    if(isWinnerCRD(col, ro, board->player)) {
                        deleteSolutions();
                        Node* solution = new Node(board->array, board->x * board->y, pos, board->player);
                        solutions->push_back(solution);
                        return;
                    }
                    board->array[pos] = 0;
                }
                Node* solution = new Node(board->array, board->x * board->y, pos, board->player);
                solutions->push_back(solution);
            }
        }
    }
    void drawMoves() {
        printf("%d\n", solutions->size());
        for(int i = 0; i < solutions->size(); i++) {
            int* solution = (*solutions)[i]->situation;
            for(int ro = 0; ro < board->y; ro++) {
                for(int col = 0; col < board->x; col++){
                    printf("%d", solution[getPos(col, ro)]);
                    if(col < board->x -1)
                        printf(" ");
                }
                printf("\n");
            }
            // printf("\n");
        }
    }
    void solveGame() {
        int result = evaluate(false);
        if(!result) {
            if(!isMovesLeft()) {
                printf("BOTH_PLAYERS_TIE\n");
                return;
            }
            result = minimax(0, true);
        }
        switch (result) {
            case MAX_SCORE:
                board->player == 1 ? printf("FIRST_PLAYER_WINS\n") : printf("SECOND_PLAYER_WINS\n");
                break;
            case -MAX_SCORE:
                board->player == 1 ? printf("SECOND_PLAYER_WINS\n") : printf("FIRST_PLAYER_WINS\n");
                break;
            case 0:
                printf("BOTH_PLAYERS_TIE\n");
                break;
        }
    }
    void deleteSolutions() {
        solutions->clear();
    }

    ~Engine() {
        delete[] board;
        delete solutions;
    }

private:
    bool isInitialisedBoardWin() {
        int state = evaluate(false);
        if(!state) return false;
        return true;
    }
    bool isItWinnerC(int column, int row, int player) {
        int elements = 0;
        for(int ro = 0; ro < board->y; ro++) {
            int pos = getPos(column, ro);
            if(board->array[pos] == player) {
                elements++;
                if (elements == board->k) return true;
            }
            else elements = 0;
        }
        return false;
    }
    bool isItWinnerR(int column, int row, int player) {
        int elements = 0;
        for (int col = 0; col < board->x; col++) {
            int pos = getPos(col, row);
            if (board->array[pos] == player) {
                elements++;
                if (elements == board->k) return true;
            }
            else elements = 0;
        }
        return false;
    }

    bool isWinnerCRD(int column, int row, int player) {
        if(isItWinnerC(column, row, player)) return true;
        if(isItWinnerR(column, row, player)) return true;

        // diameter from top-left corner
        int elementsL = 0;
        // diameter from top-right corner
        int elementsR = 0;
        for(int i = -board->k; i <= board->k; i++) {
            if(i == 0) {
                elementsL++;
                elementsR++;
                if (elementsL == board->k || elementsR == board->k) return true;
                continue;
            }
            int position = getMoveDL(column, row, i);
            if(board->checkIsOnBoard(position)) {
                if(board->array[position] == player) {
                    elementsL++;
                    if (elementsL == board->k) return true;
                }
                else elementsL = 0;
            }
            position = getMoveDR(column, row, i);
            if(board->checkIsOnBoard(position)) {
                if(board->array[position] == player) {
                    elementsR++;
                    if (elementsR == board->k) return true;
                }
                else elementsR = 0;
            }
        }

        return false;
    }

    bool isWinnerDL(int column, int row, int player){ // diameter from top-left corner
        int elements = 0;
        int diameterLength = board->y > board->x ? board->x : board->y;
        for(int i = 0; i < diameterLength; i++) {
            int position = getMoveDL(column, row, i);
            if(board->checkIsOnBoard(position)) {
                if(board->array[position] == player) {
                    elements++;
                    if (elements == board->k) return true;
                }
                else elements = 0;
            }
        }
        return false;
    }
    bool isWinnerDR(int column, int row, int player){ // diameter from top-right corner
        int elements = 0;
        int diameterLength = board->y > board->x ? board->x : board->y;
        for(int i = 0; i < diameterLength; i++) {
            int position = getMoveDR(column, row, i);
            if(board->checkIsOnBoard(position)) {
                if(board->array[position] == player) {
                    elements++;
                    if (elements == board->k) return true;
                }
                else elements = 0;
            }
        }
        return false;
    }

    int minimax(int depth, bool isMax) {
         if(!isMovesLeft())
             return 0;

        int pos = board->getNextFreePosition(-1);
        while(pos != NONE_POSITION) {
            int setPlayer = isMax ? board->player : board->getOponentPlayer();
            board->array[pos] = setPlayer;
            if(isWinnerCRD(board->getColumn(pos), board->getRow(pos), setPlayer)) {
                board->array[pos] = 0;
                return isMax ? MAX_SCORE : -MAX_SCORE;
            }
            board->array[pos] = 0;
            pos = board->getNextFreePosition(pos);
        }

        int best = isMax ? -MAX_SCORE : MAX_SCORE;
        pos = board->getNextFreePosition(-1);
        while(pos != NONE_POSITION) {
            int setPlayer = isMax ? board->player : board->getOponentPlayer();
            board->array[pos] = setPlayer;
            int second = minimax(depth+1, !isMax);
            best = isMax ? getMax(best, second) : getMin(best, second);
            board->array[pos] = 0;
            if(best == (isMax ? MAX_SCORE : -MAX_SCORE))
                return best;
            pos = board->getNextFreePosition(pos);
        }
        return best;
    }
    int evaluate(bool checkAfterMove) {
        for(int col = 0; col < board->x; col++) {
            if(isItWinnerC(col, 0, board->player)) return MAX_SCORE;
            if(isItWinnerC(col, 0, board->getOponentPlayer())) return -MAX_SCORE;
        }
        for(int ro = 0; ro < board->y; ro++) {
            if(isItWinnerR(0, ro, board->player)) return MAX_SCORE;
            if(isItWinnerR(0, ro, board->getOponentPlayer())) return -MAX_SCORE;
        }
        for(int ro = 1; ro < board->y-(board->k-1); ro++) {
            if(isWinnerDL(0, ro, board->player)) return MAX_SCORE;
            if(isWinnerDL(0, ro, board->getOponentPlayer())) return -MAX_SCORE;
            if(isWinnerDR(board->x-1, ro, board->player)) return MAX_SCORE;
            if(isWinnerDR(board->x-1, ro, board->getOponentPlayer())) return -MAX_SCORE;
        }
        for(int col = 0; col < board->x; col++) {
            if(isWinnerDL(col, 0, board->player)) return MAX_SCORE;
            if(isWinnerDL(col, 0, board->getOponentPlayer())) return -MAX_SCORE;
            if(isWinnerDR(col, 0, board->player)) return MAX_SCORE;
            if(isWinnerDR(col, 0, board->getOponentPlayer())) return -MAX_SCORE;
        }
        return 0;
    }
    bool isMovesLeft() {
        return board->getNextFreePosition(-1) != NONE_POSITION;
    }

    int getPos(int column, int row) {
        return row * board->x + column;
    }
    int getMoveDR(int col, int ro, int i) {
        if(i==0) return getPos(col, ro);
        int pos = getPos(col, ro);
        int newPos = pos + i * (board->x - 1);
        if(col-i < board->x && col-i >= 0) return newPos;
        return POSITION_ERROR;
    }
    int getMoveDL(int col, int ro, int i) {
        if(i==0) return getPos(col, ro);
        int pos = getPos(col, ro);
        int newPos = pos + i * (board->x + 1);
        if(col+i < board->x && col+i >= 0) return newPos;
        return POSITION_ERROR;
    }
};


#endif //MNKSOLVER_ENGINE_H
