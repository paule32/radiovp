#ifndef TPAINTER_H
#define TPAINTER_H

#include <iostream>
#include <vector>

#include "tapplication.h"
#include "tfont.h"

class TApplication;
class TGraphicsItem;

class TPainter
{
public:
    TPainter();
    void drawText(TFont *font, int xpos, int ypos, std::string str);
    void drawRectangle(int xpos, int ypos, int width, int height, TColor color);

    void paint(TApplication &app);

    std::vector<TGraphicsItem*> objects;
};

#endif // TPAINTER_H
