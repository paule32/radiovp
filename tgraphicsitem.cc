#include <iostream>
#include <string>

#include "SDL.h"
#include "tapplication.h"
#include "tgraphicsitem.h"

void TGraphicsText::draw()
{
    surface = TTF_RenderText_Shaded(font->font, str.c_str(),
    font->fgColor.sdl_color,
    font->bgColor.sdl_color);

    SDL_Rect textLocation = { xpos, ypos, 0, 0 };
    SDL_BlitSurface(surface, NULL, appScreen, &textLocation);
}

void TGraphicsRectangle::draw()
{
    SDL_FillRect(appScreen, &rect,
    SDL_MapRGB(appScreen->format,
        color.sdl_color.r,
        color.sdl_color.g,
        color.sdl_color.b));
}

void TGraphicsImage::draw()
{
    rect = { xpos, ypos, width, height };
    SDL_BlitSurface(surface, NULL, appScreen, &rect);
}
