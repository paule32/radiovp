#include <stdio.h>
#include <assert.h>

#include <vlc/vlc.h>

#include "tapplication.h"
#include "tfont.h"
#include "tpainter.h"
#include "tgraphicsitem.h"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 800;
const char* WINDOW_TITLE = "GOOD-Sound.DE Streamer v1.0 (c) paule32";

SDL_Surface *appScreen;

TApplication::TApplication() //QWidget *parent) : QMainWindow(parent)
{
    inst = libvlc_new(0, NULL);
    m    = libvlc_media_new_location(inst,"screen://");
    mp   = libvlc_media_player_new_from_media(m);

    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER);
    TTF_Init();

    appScreen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0,
    SDL_HWSURFACE |
    SDL_DOUBLEBUF );
    SDL_WM_SetCaption( WINDOW_TITLE, 0 );
}

TApplication::~TApplication()
{
    libvlc_media_player_stop   (mp);
    libvlc_media_player_release(mp);
    libvlc_release(inst);

    TTF_Quit();
    SDL_Quit();
}

int TApplication::run(TPainter &paint)
{
    SDL_Event event;
    this->paint = &paint;

    bool mousebutton_left = false;
    int quit = 0;
    while (!quit)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mousebutton_left = true;
                }
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                mousebutton_left = false;
            }

            if (event.type == SDL_MOUSEMOTION) {
                if (mousebutton_left == true) {
                    bool result = GetComponentUnderMouse(event);
                    if (!result) {
                        quit = 1;
                    }
                }
            }
        }

        SDL_FillRect(appScreen, NULL, SDL_MapRGB(appScreen->format,0x47,0x47,0x47));

        paint.paint();

        SDL_Flip(appScreen);
    }
    return 0;
}

bool TApplication::GetComponentUnderMouse(SDL_Event &event)
{
    for(auto it = std::begin(paint->objects); it != std::end(paint->objects); ++it) {
        try {
            TGraphicsText *item = dynamic_cast<TGraphicsText*>(*it);
            if (item)
            if (item->name == "Label1") {
                item->xpos  = event.motion.x;
                item->ypos  = event.motion.y;
                item->draw();
            }
        }   catch (...) { printf("ERRRRR\n"); }
    }

    return true;
}
