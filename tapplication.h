#ifndef TAPPLICATION_H
#define TAPPLICATION_H

//#include <QMainWindow>
//#include <QObject>
//#include <QWidget>

#include <SDL/SDL_video.h>
#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_opengl.h>

#include "tfont.h"
#include "tcolor.h"
#include "tpainter.h"
#include "tgraphicsitem.h"

class TPainter;
class TApplication //: public QMainWindow
{
    //Q_OBJECT
public:
    explicit TApplication();
    ~TApplication();

    int run(TPainter &paint);
    bool GetComponentUnderMouse(SDL_Event &event);

    SDL_Surface * screen;
    TPainter * paint;
};

extern SDL_Surface *appScreen;

#endif // TAPPLICATION_H
