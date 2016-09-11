#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#include "tapplication.h"
#include "tpainter.h"

int main(int argc, char **argv)
{
    TApplication app;

    TFont font("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
    font.fgColor = TColor(255,255,255);
    font.bgColor = TColor(0  ,  0,255);

    TPainter paint;

    paint.drawImage(180,-5,"/dbase/vlc/release/logo.bmp");
    paint.drawRectangle(50,90,900,5,TColor(105,250,155));
    paint.drawText(&font,100,100,"This is my text.");

    return app.run(paint);
}
