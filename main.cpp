#include <iostream>
//#include <raylib.h>
#include <raylib-cpp.hpp>
#include "sector.h"
#include "gameEngine.h"
#include "rectButton.h"
#include <unistd.h>

using namespace std;

int main() {

    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Kotla's Minesweeper");
    InitAudioDevice();

    std::cout << GetWorkingDirectory() << std::endl;
    SetTargetFPS(60);

    RectButton button1= {310, 400, 180, 50, BLACK};
    button1.addText("EASY", RAYWHITE);

    RectButton button2= {310, 500, 180, 50, BLACK};
    button2.addText("MEDIUM", RAYWHITE);

    RectButton button3= {310, 600, 180, 50, BLACK};
    button3.addText("HARD", RAYWHITE);


    while (true) {
        GameData::GameStatus game_status= GameData::MAINMENU;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        button1.draw();
        if (button1.isClicked()) {
            EndDrawing();
            game_status= GameData::GameStatus::RESTART;
            GameData::getInstance()->setSectorDimensionSize(50.0f);

            while (game_status == GameData::GameStatus::RESTART) {
                GameEngine gameEngine(9, 9, 10);
                game_status= gameEngine.makeGame();
            }
        }

        button2.draw();
        if (button2.isClicked()) {
            EndDrawing();
            game_status= GameData::GameStatus::RESTART;
            GameData::getInstance()->setSectorDimensionSize(35.0f);

            while (game_status == GameData::GameStatus::RESTART) {
                GameEngine gameEngine(16, 16, 40);
                game_status = gameEngine.makeGame();
            }
        }

        button3.draw();
        if (button3.isClicked()) {
            EndDrawing();
            game_status= GameData::GameStatus::RESTART;
            GameData::getInstance()->setSectorDimensionSize(25.0f);

            while (game_status == GameData::GameStatus::RESTART) {
                GameEngine gameEngine(30, 16, 99);
                game_status = gameEngine.makeGame();
            }
        }

        EndDrawing();

        if (WindowShouldClose() || game_status == GameData::GameStatus::EXIT)
            return 0;

        if (game_status == GameData::MAINMENU)
            continue;
    }


    return 0;
}
