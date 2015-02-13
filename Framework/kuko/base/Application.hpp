// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#ifndef _KUKO_APPLICATION
#define _KUKO_APPLICATION

#include <SDL.h>

#include <string>

/*
Handles initializing and tearing down SDL,
holds the renderer (might move later),
resizing/orienting the screen based on platform,
game timing,
input detection (might move later)
*/
namespace kuko
{
    struct Timer
    {
        int fps;
        int ticksPerFrame;
        int startTicks;
        void Setup( int fps );
        void Start();
        void Update();
    };

    class Application
    {
        public:
        static bool Start( const std::string& winTitle, int screenWidth = 480, int screenHeight = 480 );
        static void End();

        static int GetScreenWidth();
        static int GetScreenHeight();

        private:
        static int m_screenWidth;
        static int m_screenHeight;
        static SDL_Window* m_window;
        static SDL_Renderer* m_renderer;

        static Timer m_timer;
    };
}

#endif
