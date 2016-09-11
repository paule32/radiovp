#ifndef TTIMER_H
#define TTIMER_H

#include "SDL.h"
#include "SDL_timer.h"

class TTimer
{
public:
    TTimer(int p_interval = 1000)
    {
        interval = p_interval;
        accumulator = 0;
        total = 0;
        cur_time = last_time = SDL_GetTicks();
    }
    int ready()
    {
        return accumulator > interval;
    }
    int check()
    {
        if( ready() )
        {
            accumulator -= interval;
            return 1;
        }
        return 0;
    }
    void update()
    {
        int delta;
        cur_time = SDL_GetTicks();
        delta = cur_time - last_time;
        total += delta;
        accumulator += delta;
        last_time = cur_time;
    }
private:
    int last_time;
    int cur_time;
    int accumulator;
    int total;
    int interval;
};

#endif // TTIMER_H
