#include <iostream>
#include <string>

#include "SDL.h"
#include "tgraphicsitem.h"

void TGraphicsText::draw()
{
    surface = TTF_RenderText_Shaded(font->font, str.c_str(),
    font->fgColor.sdl_color,
    font->bgColor.sdl_color);
}
