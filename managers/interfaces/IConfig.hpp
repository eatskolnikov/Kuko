#ifndef _KUKO_ICONFIG
#define _KUKO_ICONFIG

#include <string>
#include <map>
#include <vector>

namespace kuko
{

class IConfig
{
    public:
    virtual ~IConfig() { ; }

    // Configuration
    virtual void SaveConfig() = 0;
    virtual bool LoadConfig( const std::vector<std::string>& settings ) = 0;
    virtual void SetOption( const std::string& key, const std::string& val ) = 0;
    virtual std::string GetOption( const std::string& key ) = 0;

    // Savegames
    virtual void CreateNewSave( const std::string& playername, std::map<std::string, std::string>& settings ) = 0;
    virtual void SaveState() = 0;
    virtual bool LoadState( const std::string& filename, const std::vector<std::string>& settings ) = 0;
    virtual std::string GetSaveData( const std::string& key ) = 0;
    virtual void SetSaveData( const std::string& key, const std::string& val ) = 0;
    virtual void DeleteCurrentSavefile() = 0;
    virtual std::string GetSavegameName() = 0;

    protected:
    // Configuration
    virtual void CreateNewConfig() = 0;
    std::map<std::string, std::string> m_settings;

    // Savegames
    std::map<std::string, std::string> m_saveData;
    std::string m_currentSavegame;

};

}

#endif
