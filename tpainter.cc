#include "tpainter.h"
#include "tfont.h"
#include "tgraphicsitem.h"

TPainter::TPainter()
{
    objects.clear();
}

void TPainter::paint(TApplication &app)
{
    for(auto it = std::begin(objects); it != std::end(objects); ++it)
    {
        {
            TGraphicsText *item = dynamic_cast<TGraphicsText*>(*it);
            if (item) {
                item->draw();
                continue;
            }
        }   {
            TGraphicsRectangle *item = dynamic_cast<TGraphicsRectangle*>(*it);
            if (item) {
                item->draw();
                continue;
            }
        }
    }
}

void TPainter::drawText(TFont *font, int xpos, int ypos, std::string str)
{
    TGraphicsText *text = new TGraphicsText;
    text->xpos = xpos;
    text->ypos = ypos;
    text->str  = str;
    text->font = font;
    text->name = "Label1";

    text->font->fgColor = font->fgColor;
    text->font->bgColor = font->bgColor;

    objects.push_back(text);
}

void TPainter::drawRectangle(int xpos, int ypos, int width, int height, TColor color)
{
    TGraphicsRectangle *rect = new TGraphicsRectangle;
    rect->xpos   = xpos;
    rect->ypos   = ypos;
    rect->width  = width;
    rect->height = height;
    rect->color  = color;
    rect->name   = "Label1";

    objects.push_back(rect);
}
