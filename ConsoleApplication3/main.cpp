#include <iostream>
#include "Game.h"

int main(int argc, char* argv[]) {
    Game game;
    game.InitSystem();
    game.MakeInstance();
    game.Run();
    game.Quit();
    return 0;
}