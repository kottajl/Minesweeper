#include "sector.h"
#include <raylib.h>
#include "gameData.h"
#include "gameEngine.h"

Sector::Sector(int id_x, int id_y): id_x(id_x), id_y(id_y) {
    float dimension_size= GameData::getInstance()->getSectorDimensionSize();
    cout << "> Sector dim: " << GameData::getInstance()->getSectorDimensionSize() << endl;

    my_rectangle= {dimension_size * (float)id_x, dimension_size * (float)id_y,
                   dimension_size, dimension_size};

    my_texture= GameData::getInstance()->getTexture(GameData::Skin::INACTIVE);
    my_status= INACTIVATED;
}

Sector::~Sector() = default;


void Sector::draw () const {
    DrawTexturePro(*my_texture,
                   {0.0f, 0.0f,(float)my_texture->width, (float)my_texture->height},
                   my_rectangle,{0.0f, 0.0f}, 0.0f, WHITE);
}

bool Sector::mouseHoover() const {
    return CheckCollisionPointRec(GameEngine::getMousePosition(), my_rectangle);
}

void Sector::changeSkin (GameData::Skin skin) {
    my_texture= GameData::getInstance()->getTexture(skin);
}

void Sector::changeSkin(int no_skin) {
    my_texture= GameData::getInstance()->getTexture(no_skin);
}

bool Sector::operator== (const Sector &other) const {
    return this->id_x == other.id_x && this->id_y == other.id_y;
}




#include "sector.h"
