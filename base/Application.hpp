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
        static bool Start( const std::string& winTitle, int screenWidth = 480, int screenHeight = 480, int defaultWidth = 480, int defaultHeight = 480 );
        static void End();

        static int GetScreenWidth();
        static int GetScreenHeight();

        static int GetDefaultWidth();
        static int GetDefaultHeight();

        static float GetWidthRatio();
        static float GetHeightRatio();

        static void SetDefaultResolution( int width, int height );

        static SDL_Renderer* GetRenderer();
        static void BeginDraw();
        static void EndDraw();

        static void TimerStart();
        static void TimerUpdate();

        private:
        static int m_screenWidth;
        static int m_screenHeight;

        static int m_defaultWidth;
        static int m_defaultHeight;

        static float m_widthRatio;
        static float m_heightRatio;

        static SDL_Window* m_window;
        static SDL_Renderer* m_renderer;

        static Timer m_timer;
    };
}

#endif
