#include <iostream>

#include "Engine.h"

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    auto* engine = new Engine();
    // char* toExecute;
    while(true) {
        // if(feof(stdin)!=0) break;
        char *toExecute = engine->board->cinBoard();
        if (strcmp(toExecute, "GEN_ALL_POS_MOV") == 0) {
            engine->generateMoves(false);
            engine->drawMoves();
        } else if (strcmp(toExecute, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0) {
            engine->generateMoves(true);
            engine->drawMoves();
        } else if (strcmp(toExecute, "SOLVE_GAME_STATE") == 0) {
            engine->solveGame();
        }
        if(feof(stdin)!=0) break;
        engine->deleteSolutions();
        // delete[] toExecute;
    }
    return 0;
}
