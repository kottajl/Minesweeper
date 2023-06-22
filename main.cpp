#include <iostream>
#include <raylib.h>
#include <raylib-cpp.hpp>
#include "sector.h"
#include "gameEngine.h"
#include "rectButton.h"
#include "switchButton.h"
//#include <unistd.h>

using namespace std;

int main() {

    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Kotla's Minesweeper");
    SetWindowIcon( LoadImage("../resources/flag.png") );
    InitAudioDevice();

    std::cout << GetWorkingDirectory() << std::endl;
    SetTargetFPS(60);

    RectButton button1= {310, 375, 180, 50, BLACK};
    button1.addText("EASY", RAYWHITE);

    RectButton button2= {310, 475, 180, 50, BLACK};
    button2.addText("NORMAL", RAYWHITE);

    RectButton button3= {310, 575, 180, 50, BLACK};
    button3.addText("HARD", RAYWHITE);

    RectButton exit_button= {670, 720, 85, 38, RED};
    exit_button.addText(" EXIT", RAYWHITE);

    SwitchButton sound_button= {50, 720, 160, 38, MAROON, GREEN};
    sound_button.addText("SOUND FX", RAYWHITE);
    sound_button.swapColors();

//    random_device rd;
//    mt19937 gen(rd());
//    uniform_int_distribution<> rdGenX(0, 800);
//    uniform_int_distribution<> rdGenSkin(1, 8);
//
//    GameData::getInstance()->setSectorDimensionSize(25.0f);
//    GameData::getInstance()->setSectorYShift(0.0f);
//    Sector sector1(0, 0);
//    sector1.setLeftCorner(rdGenX(gen), -25);
//    int counter= 0;
//    const int speed= 5;

    while (true) {
        GameData::GameStatus game_status= GameData::MAINMENU;
        GameData::getInstance()->setSectorDimensionSize(25.0f);
        GameData::getInstance()->setSectorYShift(0.0f);

//        counter= (counter + 1) % 60;
//        if (counter == 0) {
//
//        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        /// Test matrix
//        sector1.lowerRectangle(speed);
//        if (counter % 5 == 0)
//            sector1.changeSkin( rdGenSkin(gen) );
//        sector1.draw();

        DrawText("MINESWEEPER", 100, 110, 80, BLACK);
        DrawText("by Kotla", 500, 200, 30, BLACK);
        DrawText("version 1.3", 350, 730, 20, DARKGRAY);

        button1.draw();
        if (button1.isClicked()) {
            EndDrawing();
            game_status= GameData::GameStatus::RESTART;
            GameData::getInstance()->setSectorDimensionSize(50.0f);
            GameData::getInstance()->setSectorYShift(60.0f);

            while (game_status == GameData::GameStatus::RESTART) {
                GameEngine gameEngine(9, 9, 10);
                game_status= gameEngine.makeGame();
            }
        }

        button2.draw();
        if (button2.isClicked()) {
            EndDrawing();
            game_status= GameData::GameStatus::RESTART;
            GameData::getInstance()->setSectorDimensionSize(32.0f);
            GameData::getInstance()->setSectorYShift(30.0f);

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
            GameData::getInstance()->setSectorYShift(50.0f);

            while (game_status == GameData::GameStatus::RESTART) {
                GameEngine gameEngine(30, 16, 99);
                game_status = gameEngine.makeGame();
            }
        }

        exit_button.draw();
        if (exit_button.isClicked())
            return 0;

        sound_button.draw();
        if (sound_button.isClicked()) {
            sound_button.swapColors();
            GameData::getInstance()->changeSoundness();
        }

        EndDrawing();

        if (WindowShouldClose() || game_status == GameData::GameStatus::EXIT)
            return 0;

        if (game_status == GameData::MAINMENU)
            continue;
    }


    return 0;
}
