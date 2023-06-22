#ifndef GAMEPROJECT_GAMEENGINE_H
#define GAMEPROJECT_GAMEENGINE_H

#include <raylib.h>
#include <raylib-cpp.hpp>
#include <vector>
#include <chrono>
#include <random>
#include <set>
#include "sector.h"

using namespace std;


class GameEngine {
public:
    struct SectorInfo {
        int id_x, id_y;

        explicit SectorInfo (const Sector& sector): id_x(sector.getIdX()), id_y(sector.getIdY()) {}
        SectorInfo (int id_x, int id_y): id_x(id_x), id_y(id_y) {}

        bool operator< (const SectorInfo& other) const {
            return this->id_x < other.id_x || (this->id_x == other.id_x && this->id_y < other.id_y);
        }

        bool operator== (const SectorInfo& other) const {
            return this->id_x == other.id_x && this->id_y == other.id_y;
        }

        bool operator== (const Sector& sector) const {
            return this->id_x == sector.getIdX() && this->id_y == sector.getIdY();
        }

    };

    GameEngine(int no_sectors_x, int no_sectors_y, int no_mines);
    GameData::GameStatus makeGame();

    void drawMinefield () const;

    [[nodiscard]] int getNumOfSectorsX() const { return no_sectors_x; }
    [[nodiscard]] int getNumOfSectorsY() const { return no_sectors_y; }

    static void updateMousePosition();
    static Vector2 getMousePosition();

    [[nodiscard]] int numOfBombedNeighbours (SectorInfo) const;
    [[nodiscard]] int numOfFlaggedNeighbours (SectorInfo) const;


private:
    const int no_sectors_x, no_sectors_y, no_mines;
    int remained_flags;
    int uncovered_sectors;
    bool game_lost;
    std::chrono::steady_clock::time_point time_start, time_end;

    vector <vector <Sector>> sectors;
    vector <Sector*> hovered_clicked;
    set <SectorInfo> bombed_sectors;
    static Vector2 mouse_position;

    void checkMouseAction (bool&);
    void uncoverSector (Sector*, bool&);
    void explodeBombs (Sector*);

};


#endif //GAMEPROJECT_GAMEENGINE_H
