#ifndef GAMEPROJECT_GAMEDATA_H
#define GAMEPROJECT_GAMEDATA_H

#include <vector>
#include <map>
#include <raylib.h>
#include <random>
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

    [[nodiscard]] float getSectorDimensionSize () const { return sector_dimension_size; }
    void setSectorDimensionSize (float value) { sector_dimension_size= value; }

    [[nodiscard]] float getSectorYShift () const { return sector_y_shift; }
    void setSectorYShift (float value) { sector_y_shift= value; }

    [[nodiscard]] bool isSoundOn () const { return is_sound_on; }
    void changeSoundness () { is_sound_on= !is_sound_on; }

    string* getRandomVictoryMsg ();
    string* getRandomDefeatMsg ();


private:
    GameData();

    static GameData* gameData;
    float sector_dimension_size;
    float sector_y_shift;

    vector <Texture2D> textures;

    bool is_sound_on;
    vector <Sound> sounds;

    vector <string> victory_msgs;
    vector <string> defeat_msgs;
};


#endif //GAMEPROJECT_GAMEDATA_H
