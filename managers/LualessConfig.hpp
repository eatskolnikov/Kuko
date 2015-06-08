#ifndef _KUKO_LUALESSCONFIGMANAGER
#define _KUKO_LUALESSCONFIGMANAGER

#ifdef NOLUA

#include "IConfig.hpp"

namespace kuko
{

class LualessConfig : public IConfig
{
    public:
    // Configuration
    virtual void SaveConfig();
    virtual bool LoadConfig( const std::vector<std::string>& settings );
    virtual void SetOption( const std::string& key, const std::string& val );
    virtual std::string GetOption( const std::string& key );

    // Savegames
    virtual void CreateNewSave( const std::string& playername, std::map<std::string, std::string>& settings );
    virtual void SaveState();
    virtual bool LoadState( const std::string& filename, const std::vector<std::string>& settings );
    virtual std::string GetSaveData( const std::string& key );
    virtual void SetSaveData( const std::string& key, const std::string& val );
    virtual void DeleteCurrentSavefile();
    virtual std::string GetSavegameName();

    private:
    // Configuration
    virtual void CreateNewConfig();
    //std::map<std::string, std::string> m_settings;

    // Savegames
    //std::map<std::string, std::string> m_saveData;
    //std::string m_currentSavegame;
};

}


#endif // #ifdef NOLUA

#endif // #ifndef _KUKO_LUALESSCONFIGMANAGER
