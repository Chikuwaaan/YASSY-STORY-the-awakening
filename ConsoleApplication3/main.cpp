#include <iostream>
#include "Game.h"
#include <windows.h>
#include <random>

int main(int argc, char* argv[]) {
    /*
    MessageBoxW(
        NULL,
        L"LET'S YASSY!",
        L"YASSY STORY",
        MB_ICONQUESTION
    );
    */

    Game game;
    game.InitSystem();
    game.MakeInstance();
    game.Run();
    game.Quit();
    return 0;
    
}