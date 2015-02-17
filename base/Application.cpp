// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "Application.hpp"

#include "../utilities/Logger.hpp"

#include "SDL_image.h"

namespace kuko
{

int Application::m_screenWidth;
int Application::m_screenHeight;
SDL_Window* Application::m_window = NULL;
SDL_Renderer* Application::m_renderer = NULL;
Timer Application::m_timer;

void Timer::Setup( int fps )
{
    this->fps = fps;
    this->startTicks = 0;
    this->ticksPerFrame = 1000 / this->fps;
}

void Timer::Start()
{
    startTicks = SDL_GetTicks();
}

void Timer::Update()
{
    int frameTicks = SDL_GetTicks();
    if ( frameTicks < ticksPerFrame )
    {
        SDL_Delay( ticksPerFrame - frameTicks );
    }
}

void Application::TimerStart()
{
    m_timer.Start();
}

void Application::TimerUpdate()
{
    m_timer.Update();
}

bool Application::Start( const std::string& winTitle, int screenWidth /* = 480 */, int screenHeight /* = 480 */ )
{
    m_timer.Setup( 60 );

    if ( SDL_Init( SDL_INIT_VIDEO ) != 0 )
    {
        std::string error( SDL_GetError() );
        Logger::Error( "Error initializing SDL: " + error, "Application::Start" );
        return false;
    }

    if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        Logger::Error( "Error setting hint - Linear texture filtering not enabled!", "Application::Start" );
    }

    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;

    m_window = SDL_CreateWindow( winTitle.c_str(),
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        m_screenWidth, m_screenHeight, SDL_WINDOW_SHOWN );

    if ( m_window == NULL )
    {
        std::string error( SDL_GetError() );
        Logger::Error( "Error creating window: " + error, "Application::Start" );
        return false;
    }

    m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED );
    if ( m_renderer == NULL )
    {
        std::string error( SDL_GetError() );
        Logger::Error( "Error initializing renderer: " + error, "Application::Start" );
        return false;
    }
    SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    int imgFlags = IMG_INIT_PNG;
    if ( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        std::string error( SDL_GetError() );
        Logger::Error( "Error initializing SDL_Image: " + error, "Application::Start" );
        return false;
    }

    return true;
}

void Application::End()
{
    Logger::Out( "Cleaning up application!", "Application::End" );

    if ( m_renderer != NULL )
    {
        SDL_DestroyRenderer( m_renderer );
        m_renderer = NULL;
    }

    if ( m_window != NULL )
    {
        SDL_DestroyWindow( m_window );
        m_window = NULL;
    }

    SDL_Quit();
}

int Application::GetScreenWidth()
{
    return m_screenWidth;
}

int Application::GetScreenHeight()
{
    return m_screenHeight;
}

SDL_Renderer* Application::GetRenderer()
{
    return m_renderer;
}

void Application::BeginDraw()
{
    SDL_RenderClear( m_renderer );
}

void Application::EndDraw()
{
    SDL_RenderPresent( m_renderer );
}

}
