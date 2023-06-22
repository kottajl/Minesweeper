#ifndef GAMEPROJECT_RECTBUTTON_H
#define GAMEPROJECT_RECTBUTTON_H

#include <raylib.h>
#include <raylib-cpp.hpp>
#include <iostream>
#include <string>

class RectButton {
public:
    RectButton (int x, int y, int width, int height, Color color) {
        button_area= {(float)x, (float)y, (float)width, (float)height};
        this->color= color;
        this->text= "";
        is_hover_on= true;

        triangle_color1= LIGHTGRAY;
        triangle_color2= DARKGRAY;
    }

    void draw () const {
        const float k= 3.0f;     /// przesuniecie w trójkątach

        /// Trójkąty do efektu 3D
        DrawTriangle({button_area.x - k, button_area.y + button_area.height + k},
                     {button_area.x + button_area.width + k, button_area.y + button_area.height + k},
                     {button_area.x + button_area.width + k, button_area.y - k}, triangle_color2);
        DrawTriangle({button_area.x - k, button_area.y + button_area.height + k},
                     {button_area.x + button_area.width + k, button_area.y - k},
                     {button_area.x - k, button_area.y - k}, triangle_color1);

        DrawTriangle({button_area.x - k, button_area.y + button_area.height + k},
                     {button_area.x + 5*k, button_area.y + button_area.height + k},
                     {button_area.x + 5*k, button_area.y + button_area.height - 5*k}, triangle_color2);
        DrawTriangle({button_area.x + button_area.width - 5*k, button_area.y + 5*k},
                     {button_area.x + button_area.width + k, button_area.y - k},
                     {button_area.x + button_area.width - 5*k, button_area.y - k}, triangle_color1);
//        return;

        if (isHover() && is_hover_on) {
            DrawRectangle((int)button_area.x - 2, (int) button_area.y - 2, (int)button_area.width + 4,
                          (int)button_area.height + 4, GRAY);
        }

        DrawRectangle((int)button_area.x, (int)button_area.y, (int)button_area.width,
                      (int)button_area.height, color);

        if (!text.empty()) {
            float text_height= 0.7f * button_area.height;

            DrawText(text.c_str(),
                     (int)(button_area.x + (((float)button_area.width - (float)text_height * ((float)text.size() * 0.67f - (float)num_of_spaces * 0.35f))) / 2.0f),
                     (int)(button_area.y + 0.2f * button_area.height),
                     (int)text_height, text_color);
        }
    }

    [[nodiscard]] bool isClicked () const {
        return isHover() && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
    }

    [[nodiscard]] bool isHover () const {
        return CheckCollisionPointRec( GetMousePosition(), button_area);
    }
    void disableHover () { is_hover_on= false; }


    void addText (string text_, Color color_) {
        text= text_;
        text_color= color_;

        num_of_spaces= 0;
        for (char c: text)
            if (c == ' ')
                num_of_spaces++;
    }

protected:
    Rectangle button_area{};
    Color color{};
    Color triangle_color1{}, triangle_color2{};

    string text;
    int num_of_spaces;
    Color text_color{};

    bool is_hover_on;

};


#endif //GAMEPROJECT_RECTBUTTON_H
