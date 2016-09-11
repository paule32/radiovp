#ifndef TAPPLICATION_H
#define TAPPLICATION_H

#include <SDL/SDL_video.h>
#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_opengl.h>

#include <vlc/vlc.h>

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

    libvlc_instance_t * inst;
    libvlc_media_t *m;
    libvlc_media_player_t *mp;
};

extern SDL_Surface *appScreen;

#endif // TAPPLICATION_H
