#include "gameData.h"
#include <map>
#include <raylib.h>
#include <string>
using namespace std;

//float GameData::sector_dimension_size= 5.0f;
GameData* GameData::gameData= nullptr;

GameData* GameData::getInstance () {
    if (gameData == nullptr)
        gameData= new GameData();

    return gameData;
}

GameData::GameData () {
    textures.push_back( LoadTexture("../resources/active_0.png") );

    textures.push_back( LoadTexture("../resources/active_1.png") );
    textures.push_back( LoadTexture("../resources/active_2.png") );
    textures.push_back( LoadTexture("../resources/active_3.png") );
    textures.push_back( LoadTexture("../resources/active_4.png") );
    textures.push_back( LoadTexture("../resources/active_5.png") );
    textures.push_back( LoadTexture("../resources/active_6.png") );
    textures.push_back( LoadTexture("../resources/active_7.png") );
    textures.push_back( LoadTexture("../resources/active_8.png") );

    textures.push_back( LoadTexture("../resources/flag.png") );
    textures.push_back( LoadTexture("../resources/inactive.png") );

    textures.push_back(LoadTexture("../resources/selected.png") );

    textures.push_back(LoadTexture("../resources/mine_normal.png") );
    textures.push_back(LoadTexture("../resources/mine_red.png") );

    sector_dimension_size= 30.0f;

    is_sound_on= true;
    sounds.push_back( LoadSound("../resources/sounds/click_sound.wav") );
    sounds.push_back( LoadSound("../resources/sounds/flag_sound.wav") );
    sounds.push_back( LoadSound("../resources/sounds/unflag_sound.wav") );
    sounds.push_back( LoadSound("../resources/sounds/bomb_sound.wav") );
}

const Texture2D* GameData::getTexture (const int it) const {
    if (textures.size() <= it)
        throw std::out_of_range("Out of range in getTexture()");

    return &textures[it];
}

const Texture2D* GameData::getTexture (Skin skin) const {
    int it;

    switch (skin) {

        case NUMBER_0:
            it= 0; break;

        case NUMBER_1:
            it= 1; break;

        case NUMBER_2:
            it= 2; break;

        case NUMBER_3:
            it= 3; break;

        case NUMBER_4:
            it= 4; break;

        case NUMBER_5:
            it= 5; break;

        case NUMBER_6:
            it= 6; break;

        case NUMBER_7:
            it= 7; break;

        case NUMBER_8:
            it= 8; break;

        case FLAG:
            it= 9; break;

        case INACTIVE:
            it= 10; break;

        case SELECTED:
            it= 11; break;

        case WHITEMINE:
            it= 12; break;

        case REDMINE:
            it= 13; break;

        default:
            it= -1; break;
    }

    return getTexture(it);
}

const Sound *GameData::getSound (int it) const {
    if (sounds.size() <= it)
        throw std::out_of_range("Out of range in getTexture()");

    return &sounds[it];
}

const Sound *GameData::getSound (Tone tone) const {
    int it= -1;

    switch (tone) {

        case CLICKED:
            it= 0; break;
        case FLAGGED:
            it= 1; break;
        case UNFLAGGED:
            it= 2; break;
        case BOMBED:
            it= 3; break;
    }

    return getSound(it);
}

void GameData::playSound(int it) const {
    PlaySound( *getSound(it) );
};

void GameData::playSound(Tone tone) const {
    PlaySound( *getSound(tone) );
}

