#include "gameEngine.h"
#include <raylib.h>
#include <raylib-cpp.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
//#include <unistd.h>
#include <cstdlib>
#include <queue>
#include <chrono>
#include "gameData.h"
#include "rectButton.h"

using namespace std;

Vector2 GameEngine::mouse_position= {0.0f, 0.0f};

GameEngine::GameEngine(int no_sectors_x, int no_sectors_y, int no_mines) :
        no_sectors_x(no_sectors_x), no_sectors_y(no_sectors_y), no_mines(no_mines) {

    Sector::setXShift( ((float)GetScreenWidth() - (float)no_sectors_x * GameData::getInstance()->getSectorDimensionSize()) / 2.0f );

    for (int i=0; i < no_sectors_y; i++) {
        vector <Sector> sector_line;
        for (int j=0; j < no_sectors_x; j++)
            sector_line.emplace_back(j, i);
        sectors.push_back(sector_line);
    }

    remained_flags= no_mines;
    uncovered_sectors= no_sectors_x * no_sectors_y - remained_flags;
    game_lost= false;
    hovered_clicked.clear();

    time_start= std::chrono::steady_clock::now();
    time_end= time_start;
}


GameData::GameStatus GameEngine::makeGame() {
    bool is_first_move= true;
    string victory_msg= *GameData::getInstance()->getRandomVictoryMsg();
    string defeat_msg= *GameData::getInstance()->getRandomDefeatMsg();
    const int msg_size= 30;

    RectButton restart_button(500, 720, 200, 50, BLUE);
    restart_button.addText("RESTART", RAYWHITE);

    Color orange_col({255, 128, 0});
    RectButton menu_button(100, 720, 240, 50, (Color){ 240, 113, 0, 255 });
    menu_button.addText("MAIN MENU", RAYWHITE);

    RectButton minefield_border((int)Sector::getXShift(), (int)GameData::getInstance()->getSectorYShift(),
                                 (int)((float)no_sectors_x * GameData::getInstance()->getSectorDimensionSize()),
                                 (int)((float)no_sectors_y * GameData::getInstance()->getSectorDimensionSize()), BLACK);
    minefield_border.disableHover();

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        GameEngine::updateMousePosition();

        /// Draw elements
        minefield_border.draw();
        drawMinefield();
        restart_button.draw();
        menu_button.draw();

        /// Game mechanics
        if (game_lost) {
            DrawText(defeat_msg.c_str(),
                     (int)(((float)GetScreenWidth() - (float)msg_size * (float)defeat_msg.size() * 0.65f) / 2.0f),
                     (int)GameData::getInstance()->getSectorYShift() + (int)((float)no_sectors_y * GameData::getInstance()->getSectorDimensionSize()) + 30,
                     msg_size, MAROON);
        }
        else if (uncovered_sectors == 0) {
            DrawText(victory_msg.c_str(),
                     (int)(((float)GetScreenWidth() - (float)msg_size * (float)victory_msg.size() * 0.65f) / 2.0f),
                     550, msg_size, GREEN);
        }
        else {
            checkMouseAction(is_first_move);
            if (!is_first_move)
                time_end= std::chrono::steady_clock::now();
        }

        /// Draw remained flags
        DrawText("Remained bombs: ", 370, 635, 40, BLACK);
        DrawText((to_string(remained_flags)).c_str(), 720, 635, 40, BLACK);

        /// Draw timer
        string timer;
        long time_ms= std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count();
        if (time_ms / 1000 >= 1000)
            timer= "999.999";
        else
            timer= to_string( time_ms / 1000 ) + '.' + to_string(time_ms % 1000);
        DrawText("Time: ", 50, 635, 40, BLACK);
        DrawText(timer.c_str(), 170, 635, 40, BLACK);

        /// Check buttons
        if (restart_button.isClicked()) {
            cout << "Game restarted!" << endl;
            EndDrawing();
            return GameData::RESTART;
        }

        if (menu_button.isClicked()) {
            EndDrawing();
            return GameData::MAINMENU;
        }

        EndDrawing();
    }

    return GameData::EXIT;
}


void GameEngine::drawMinefield () const {
    for (const vector<Sector>& sector_line: sectors)
        for (const Sector &my_sector: sector_line)
            my_sector.draw();
}

void GameEngine::updateMousePosition() {
    mouse_position= GetMousePosition();
}

Vector2 GameEngine::getMousePosition() {
    return mouse_position;
}

Sector* findHoveredSector (vector <vector <Sector>>& sectors) {

    for (vector<Sector>& sector_line: sectors)
        for (Sector& my_sector: sector_line)
            if (my_sector.mouseHoover())
                return &my_sector;

    return nullptr;
}

void GameEngine::explodeBombs (Sector* my_sector) {
    queue <Sector*> Q;
    vector <vector <bool>> bt (no_sectors_y, vector <bool> (no_sectors_x, false));
    GameData::getInstance()->playSound(GameData::Tone::BOMBED);

    // Red bomb
    bt[my_sector->getIdY()][my_sector->getIdX()]= true;
    my_sector->changeSkin(GameData::REDMINE);
    for (int ix=-1; ix<=1; ix++)
        for (int iy=-1;iy<=1; iy++) {
            if ( (my_sector->getIdX() + ix < 0 || my_sector->getIdX() + ix >= no_sectors_x) ||
                 (my_sector->getIdY() + iy < 0 || my_sector->getIdY() + iy >= no_sectors_y) )
                continue;

            if (ix != 0 || iy != 0) {
                Q.push(&sectors[my_sector->getIdY() + iy][my_sector->getIdX() + ix]);
                bt[my_sector->getIdY() + iy][my_sector->getIdX() + ix] = true;
            }
        }

    // White bombs
    while (!Q.empty()) {
        Sector* temp= Q.front();
        Q.pop();
        SectorInfo temp_info(*temp);

        for (int ix=-1; ix<=1; ix++)
            for (int iy=-1;iy<=1; iy++) {
                if ( (temp_info.id_x + ix < 0 || temp_info.id_x + ix >= no_sectors_x) ||
                     (temp_info.id_y + iy < 0 || temp_info.id_y + iy >= no_sectors_y) )
                    continue;

                if (!bt[temp_info.id_y + iy][temp_info.id_x + ix]) {
                    bt[temp_info.id_y + iy][temp_info.id_x + ix]= true;
                    Q.push(&sectors[temp_info.id_y + iy][temp_info.id_x + ix]);
                }
            }

        if ( bombed_sectors.contains(temp_info) ) {
            temp->changeSkin(GameData::WHITEMINE);
        }
    }

}

void GameEngine::uncoverSector (Sector* my_sector, bool& is_first_move) {

    /// Initialise bombs if first move
    if (is_first_move) {
        is_first_move= false;

        time_start= std::chrono::steady_clock::now();

        random_device rd;
        mt19937 gen(rd());

        uniform_int_distribution<> rdGenX(0, no_sectors_x - 1);
        uniform_int_distribution<> rdGenY(0, no_sectors_y - 1);

        for (int i=0; i < no_mines; i++) {
            SectorInfo temp((int)rdGenX(gen), (int)rdGenY(gen));

            if (bombed_sectors.contains(temp) || /*temp == *my_sector || */
                abs(temp.id_x - my_sector->getIdX()) <= 1 || abs(temp.id_y - my_sector->getIdY()) <= 1) {
                i--;
                continue;
            }

            bombed_sectors.insert(temp);
        }

    }

    /// Make an actual action on click
    SectorInfo my_sector_info(*my_sector);

    if (bombed_sectors.contains(my_sector_info)) {
        game_lost= true;
        explodeBombs(my_sector);
        return;
    }

    my_sector->setStatus( Sector::ACTIVATED );
    uncovered_sectors--;

    int bombed_neighbours= numOfBombedNeighbours(my_sector_info);
    my_sector->changeSkin(bombed_neighbours);

    /// If i have no bombs near border, make recursive on neighbours
    if (bombed_neighbours == 0) {
        for (int ix=-1; ix<=1; ix++)
            for (int iy=-1;iy<=1; iy++) {

                if (ix == 0 && iy == 0)
                    continue;

                SectorInfo neigh_info= {my_sector_info.id_x + ix, my_sector_info.id_y + iy};
                if ( (neigh_info.id_x < 0 || neigh_info.id_x >= no_sectors_x) ||
                     (neigh_info.id_y < 0 || neigh_info.id_y >= no_sectors_y) )
                    continue;

                if (sectors[neigh_info.id_y][neigh_info.id_x].getStatus() == Sector::INACTIVATED)
                    uncoverSector(&sectors[neigh_info.id_y][neigh_info.id_x], is_first_move);
            }

    }


}

void GameEngine::checkMouseAction(bool& is_first_move) {

    /// Normal left click
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && !IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        Sector* my_sector= findHoveredSector(sectors);

        if (my_sector != nullptr) {
            switch (my_sector->getStatus()) {

                case Sector::ACTIVATED:
                case Sector::FLAGGED:
                    break;

                case Sector::INACTIVATED:
                    GameData::getInstance()->playSound(GameData::Tone::CLICKED);
                    uncoverSector(my_sector, is_first_move);
                    break;
            }
        }
    }

    /// Normal right click
    if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && !IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Sector* my_sector= findHoveredSector(sectors);

        if (my_sector != nullptr) {
            switch (my_sector->getStatus()) {

                case Sector::ACTIVATED:
                    break;

                case Sector::INACTIVATED:
                    my_sector->setStatus(Sector::FLAGGED);
                    my_sector->changeSkin( GameData::Skin::FLAG );
                    GameData::getInstance()->playSound(GameData::Tone::FLAGGED);
                    remained_flags--;
                    break;

                case Sector::FLAGGED:
                    my_sector->setStatus(Sector::INACTIVATED);
                    my_sector->changeSkin( GameData::Skin::INACTIVE );
                    GameData::getInstance()->playSound(GameData::Tone::UNFLAGGED);
                    remained_flags++;
                    break;
            }
        }
    }

    /// Double click
    if ( (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) ||
            (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) ||
            (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) ) {

        Sector* my_sector= findHoveredSector(sectors);

        cout << "Double click!" << endl;

        if (my_sector != nullptr && my_sector->getStatus() == Sector::ACTIVATED) {
            SectorInfo my_sector_info (*my_sector);

            cout << "Numerki: " << numOfFlaggedNeighbours(my_sector_info) << ' ' << numOfBombedNeighbours(my_sector_info) << endl;
            if( numOfFlaggedNeighbours(my_sector_info) == numOfBombedNeighbours(my_sector_info) ) {
                cout << "JEST TAKIE SAMO!" << endl;
                for (int ix=-1; ix<=1; ix++)
                    for (int iy=-1;iy<=1; iy++) {

                        if (ix == 0 && iy == 0)
                            continue;

                        SectorInfo neigh_info= {my_sector_info.id_x + ix, my_sector_info.id_y + iy};
                        cout << "Looking on neighbour: " << neigh_info.id_x << ' ' << neigh_info.id_y << endl;
                        if ((neigh_info.id_x < 0 || neigh_info.id_x >= no_sectors_x) ||
                            (neigh_info.id_y < 0 || neigh_info.id_y >= no_sectors_y))
                            continue;

                        if (sectors[neigh_info.id_y][neigh_info.id_x].getStatus() == Sector::INACTIVATED) {
                            cout << "Inactivated neighbour: " << neigh_info.id_x << ' ' << neigh_info.id_y << endl;
                            uncoverSector(&sectors[neigh_info.id_y][neigh_info.id_x], is_first_move);
                        }
                    }
            }


        }
    }

//    /// Click hover skin
//    // Clear old
//    for (Sector* my_sector: hovered_clicked)
//        my_sector->changeSkin(GameData::INACTIVE);
//    hovered_clicked.clear();
//
//    // Make new
//    if ( (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT))) {
//        Sector* my_sector= findHoveredSector(sectors);
//        if (my_sector->getStatus() == Sector::INACTIVATED)
//            hovered_clicked.push_back(my_sector);
//            my_sector->changeSkin(GameData::SELECTED);
//    }


}


int GameEngine::numOfBombedNeighbours (GameEngine::SectorInfo my_sector_info) const {
    int bombed_neighbours= 0;

    /// Check how many bombs are near my border
    for (int ix=-1; ix<=1; ix++)
        for (int iy=-1;iy<=1; iy++) {

            if (ix == 0 && iy == 0)
                continue;

            SectorInfo neigh_info= {my_sector_info.id_x + ix, my_sector_info.id_y + iy};
            if ( (neigh_info.id_x < 0 || neigh_info.id_x >= no_sectors_x) ||
                 (neigh_info.id_y < 0 || neigh_info.id_y >= no_sectors_y) )
                continue;

            if (bombed_sectors.contains(neigh_info))
                bombed_neighbours++;
        }

    return bombed_neighbours;
}

int GameEngine::numOfFlaggedNeighbours (GameEngine::SectorInfo my_sector_info) const {
    int flagged_neighbours= 0;

    for (int ix=-1; ix<=1; ix++)
        for (int iy=-1;iy<=1; iy++) {

            if (ix == 0 && iy == 0)
                continue;

            SectorInfo neigh_info= {my_sector_info.id_x + ix, my_sector_info.id_y + iy};
            if ((neigh_info.id_x < 0 || neigh_info.id_x >= no_sectors_x) ||
                (neigh_info.id_y < 0 || neigh_info.id_y >= no_sectors_y))
                continue;

            if (sectors[neigh_info.id_y][neigh_info.id_x].getStatus() == Sector::FLAGGED)
                flagged_neighbours++;
        }

    return flagged_neighbours;
}



