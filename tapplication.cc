#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <SDL/SDL.h>
#include <SDL/SDL_mutex.h>

#include <vlc/vlc.h>
#include <vlc/libvlc.h>


#include "tapplication.h"
#include "tfont.h"
#include "tpainter.h"
#include "tgraphicsitem.h"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 800;

#define VIDEOWIDTH 320
#define VIDEOHEIGHT 240

const char* WINDOW_TITLE = "GOOD-Sound.DE Streamer v1.0 (c) paule32";

SDL_Surface *appScreen;

struct ctx {
    SDL_Surface *surf;
    SDL_mutex *mutex;
};

static void *lock(void *data, void **p_pixels)
{
    struct ctx *ctx = data;

    SDL_LockMutex(ctx->mutex);
    SDL_LockSurface(ctx->surf);
    *p_pixels = ctx->surf->pixels;
    return NULL; /* picture identifier, not needed here */
}

static void unlock(void *data, void *id, void *const *p_pixels)
{
    struct ctx *ctx = data;

    /* VLC just rendered the video, but we can also render stuff */
    uint16_t *pixels = *p_pixels;
    int x, y;

    for(y = 10; y < 40; y++)
        for(x = 10; x < 40; x++)
            if(x < 13 || y < 13 || x > 36 || y > 36)
                pixels[y * VIDEOWIDTH + x] = 0xffff;
            else
                pixels[y * VIDEOWIDTH + x] = 0x0;

    SDL_UnlockSurface(ctx->surf);
    SDL_UnlockMutex(ctx->mutex);

    assert(id == NULL); /* picture identifier, not needed here */
}


static void display(void *data, void *id)
{
    /* VLC wants to display the video */
    (void) data;
    assert(id == NULL);
}

TApplication::TApplication() //QWidget *parent) : QMainWindow(parent)
{
    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER);
    TTF_Init();

    int options = SDL_ANYFORMAT | SDL_HWSURFACE | SDL_DOUBLEBUF;

    appScreen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, options);
    SDL_WM_SetCaption( WINDOW_TITLE, 0 );

    inst = libvlc_new(0, NULL);
    m    = libvlc_media_new_location(inst,"screen://");
    mp   = libvlc_media_player_new_from_media(m);
    libvlc_media_player_play(mp);
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
    struct ctx ctx;

    SDL_Event event;
    this->paint = &paint;

    SDL_Surface *empty;
    SDL_Rect      rect;

    int done = 0, action = 0, pause = 0, n = 0;

    empty     = SDL_CreateRGBSurface(SDL_SWSURFACE, VIDEOWIDTH, VIDEOHEIGHT, 32, 0, 0, 0, 0);
    ctx.surf  = SDL_CreateRGBSurface(SDL_SWSURFACE, VIDEOWIDTH, VIDEOHEIGHT, 16, 0x001f, 0x07e0, 0xf800, 0);
    ctx.mutex = SDL_CreateMutex();

    rect.x = 10;
    rect.y = 10;

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


        rect.x = (int)((1. + .5 * sin(0.03 * n)) * (320 - VIDEOWIDTH) / 2);
        rect.y = (int)((1. + .5 * cos(0.03 * n)) * (200 - VIDEOHEIGHT) / 2);

        paint.paint();

        SDL_LockMutex(ctx.mutex);
        SDL_BlitSurface(ctx.surf, NULL, appScreen, &rect);
        SDL_UnlockMutex(ctx.mutex);

        SDL_Flip(appScreen);
        SDL_BlitSurface(empty, NULL, appScreen, &rect);
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
