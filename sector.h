#ifndef GAMEPROJECT_SECTOR_H
#define GAMEPROJECT_SECTOR_H

#include <iostream>
#include <string>
#include <raylib.h>
#include "gameData.h"

using namespace std;

class Sector {
public:
    enum Status {
        ACTIVATED, INACTIVATED, FLAGGED
    };

    Sector(int, int);
    ~Sector();

    void draw () const;
    [[nodiscard]] bool mouseHoover () const;
    void changeSkin (GameData::Skin skin);
    void changeSkin (int no_skin);

    [[nodiscard]] Status getStatus () const { return my_status; }
    void setStatus (Status new_status) { my_status= new_status; }

    [[nodiscard]] int getIdX () const { return id_x; }
    [[nodiscard]] int getIdY () const { return id_y; }

    bool operator== (const Sector& other) const;

private:

    const int id_x, id_y;
    Rectangle my_rectangle{};
    const Texture2D* my_texture;
    Status my_status;

    static map <string, Texture2D> textures;
    // constexpr static const float dimension_size= 50.0f;

};


#endif //GAMEPROJECT_SECTOR_H
