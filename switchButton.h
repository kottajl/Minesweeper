#ifndef GAMEPROJECT_SWITCHBUTTON_H
#define GAMEPROJECT_SWITCHBUTTON_H

#include <algorithm>
#include "rectButton.h"


class SwitchButton : public RectButton {
public:
    SwitchButton (int x, int y, int width, int height, Color color_unpressed, Color color_pressed) :
        RectButton(x, y, width, height, color_unpressed) {

        is_pressed= false;
        this->color2= color_pressed;
    }

    void swapColors () {
        is_pressed= !is_pressed;
        std::swap(color, color2);

        if (is_pressed) {
            triangle_color1= GRAY;
            triangle_color2= GRAY;
        }
        else {
            triangle_color1= LIGHTGRAY;
            triangle_color2= DARKGRAY;
        }
    }


private:
    bool is_pressed;        // kolorystycznie
    Color color2{};

};



#endif //GAMEPROJECT_SWITCHBUTTON_H
