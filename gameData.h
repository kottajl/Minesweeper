#ifndef GAMEPROJECT_GAMEDATA_H
#define GAMEPROJECT_GAMEDATA_H

#include <vector>
#include <map>
#include <raylib.h>
using namespace std;

class GameData {
public:
    enum Skin {
        NUMBER_1, NUMBER_2, NUMBER_3, NUMBER_4,
        NUMBER_5, NUMBER_6, NUMBER_7, NUMBER_8,
        NUMBER_0, INACTIVE, FLAG, SELECTED,
        WHITEMINE, REDMINE
    };
    enum Tone {
        CLICKED, FLAGGED, UNFLAGGED, BOMBED
    };
    enum GameStatus {
        EXIT, RESTART, MAINMENU
    };

    static GameData* getInstance();

    [[nodiscard]] const Texture2D* getTexture (int) const;
    [[nodiscard]] const Texture2D* getTexture (Skin) const;

    [[nodiscard]] const Sound* getSound (int) const;
    [[nodiscard]] const Sound* getSound (Tone) const;
    void playSound (int) const;
    void playSound (Tone) const;

    // [[nodiscard]] int getNumOfMines () const { return num_of_mines; }
    [[nodiscard]] float getSectorDimensionSize () const { return sector_dimension_size; }
    void setSectorDimensionSize (float value) { sector_dimension_size= value; }


private:
    GameData();

    // int num_of_mines;
    static GameData* gameData;
    float sector_dimension_size;
    vector <Texture2D> textures;

    bool is_sound_on;
    vector <Sound> sounds;
};


#endif //GAMEPROJECT_GAMEDATA_H
