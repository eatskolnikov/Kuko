// Kuko Framework - https://github.com/Rejcx/Kuko - Rachel J. Morris - MIT License

#include "../utilities/Logger.hpp"

#include "State.hpp"

#include <string>

namespace kuko
{

State::State( LuaManager* ptrLuaManager, ImageManager* ptrImageManager, const std::string& stateName, const std::string& scriptPath )
{
    Logger::Out( "begin", "State::State" );
    m_ptrLuaMgr = ptrLuaManager;
    m_stateName = stateName;

    m_ptrLuaMgr->LoadScript( scriptPath );
    m_ptrLuaMgr->State_LoadRequiredScripts();
    m_ptrLuaMgr->State_Setup();

    // Populate the entities list m_lstEntities
    int entityCount = m_ptrLuaMgr->State_GetEntityCount();
    Logger::Out( I2S( entityCount ) + " entities" );

    for ( int i = 0; i < entityCount; i++ )
    {
        BaseEntity* newEntity = new BaseEntity( m_ptrLuaMgr, ptrImageManager, i );
        m_lstEntities.push_back( newEntity );
    }

    Logger::Out( "end", "State::State" );
}

State::~State()
{
    for ( unsigned int i = 0; i < m_lstEntities.size(); i++ )
    {
        if ( m_lstEntities[i] != NULL )
        {
            delete m_lstEntities[i];
            m_lstEntities[i] = NULL;
        }
    }
}

void State::Setup()
{
}

void State::Cleanup()
{
}

void State::Update()
{
}

void State::Draw()
{
    for ( unsigned int i = 0; i < m_lstEntities.size(); i++ )
    {
        m_lstEntities[i]->Draw();
    }
}


}
