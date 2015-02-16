// Test file to build and run Kuko.

#include <iostream>

#include "kuko/utilities/Logger.hpp"

#include <SDL.h>

int main()
{
    Logger::Setup();

    SDL_Delay( 2000 );

    Logger::Cleanup();
    return 0;
}
