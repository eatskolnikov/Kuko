// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License
#include "Application.hpp"

#include "../utilities/Logger.hpp"
#include "../utilities/StringUtil.hpp"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

namespace kuko
{

int Application::m_screenWidth;
int Application::m_screenHeight;
int Application::m_defaultWidth;
int Application::m_defaultHeight;
float Application::m_widthRatio;
float Application::m_heightRatio;

SDL_Window* Application::m_window = NULL;
SDL_Renderer* Application::m_renderer = NULL;
Timer Application::m_timer;

void Timer::Setup( int fps )
{
    countedFrames = 0;
}

void Timer::Start()
{
    startTicks = SDL_GetTicks();
}

void Timer::Update()
{
    float averageFps = countedFrames / ( SDL_GetTicks() / 1000.0f );
    if ( countedFrames % 10000 == 0 )
    {
        Logger::Out( "Average FPS: " + StringUtil::FloatToString( averageFps ) );
    }

    ++countedFrames;
}

void Application::TimerStart()
{
    m_timer.Start();
}

void Application::TimerUpdate()
{
    m_timer.Update();
}

void Application::SetDefaultResolution( int width, int height )
{
    m_defaultWidth = width;
    m_defaultHeight = height;
}

bool Application::Start( const std::string& winTitle, int screenWidth /* = 480 */, int screenHeight /* = 480 */, int defaultWidth, int defaultHeight, bool useVsync )
{
    Logger::Out( "Title \"" + winTitle + "\", Screen: "
        + StringUtil::IntToString( screenWidth ) + "x" + StringUtil::IntToString( screenHeight )
        + ", Actual Resolution: "
        + StringUtil::IntToString( defaultWidth ) + "x" + StringUtil::IntToString( defaultHeight ),
        "Application::Start" );

    // Screen scaling is based on the default width/height
    SetDefaultResolution( defaultWidth, defaultHeight );

    m_timer.Setup( 60 );

    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0 )
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

    if ( useVsync )
    {
        Logger::Out( "Use VSYNC", "Application::Start" );
        m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    }
    else
    {
        Logger::Out( "Do not use VSYNC", "Application::Start" );
        m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED );
    }

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
        std::string error( IMG_GetError() );
        Logger::Error( "Error initializing SDL_Image: " + error, "Application::Start" );
        return false;
    }

    if( TTF_Init() == -1 )
    {
        std::string error( TTF_GetError() );
        Logger::Error( "Error initializing SDL_TTF: " + error, "Application::Start" );
        return false;
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        std::string error( Mix_GetError() );
        Logger::Error( "Error initializing SDL_Mixer: " + error, "Application::Start" );
        return false;
    }

    m_widthRatio = float( m_screenWidth ) / float( m_defaultWidth );
    m_heightRatio = float( m_screenHeight ) / float( m_defaultHeight );

    Logger::Out( "Renderer scale ratio: " + StringUtil::FloatToString( m_widthRatio ) + "x" + StringUtil::FloatToString( m_heightRatio ), "Application::Start" );

    //SDL_RenderSetScale( m_renderer, 0.5, 0.5 );
    SDL_RenderSetScale( m_renderer, m_widthRatio, m_heightRatio );

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

int Application::GetDefaultWidth()
{
    return m_defaultWidth;
}

int Application::GetDefaultHeight()
{
    return m_defaultHeight;
}

float Application::GetWidthRatio()
{
    return m_widthRatio;
}

float Application::GetHeightRatio()
{
    return m_heightRatio;
}

SDL_Renderer* Application::GetRenderer()
{
    return m_renderer;
}

void Application::BeginDraw()
{
    SDL_SetRenderDrawColor( m_renderer, 0x33, 0x33, 0x33, 0xFF );
    SDL_RenderClear( m_renderer );
}

void Application::EndDraw()
{
    SDL_RenderPresent( m_renderer );
}

}
