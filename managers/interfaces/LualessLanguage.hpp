#ifndef _KUKO_LUALESSLANGUAGE
#define _KUKO_LUALESSLANGUAGE

#ifdef NOLUA

#include <string>
#include <map>

#include "ILanguage.hpp"

namespace kuko
{

class LualessLanguage : public ILanguage
{
    public:
    virtual ~LualessLanguage();

    virtual bool AddLanguage( const std::string& id, const std::string& path );

    virtual std::string Text( const std::string& key );
    virtual std::string Text( const std::string& langType, const std::string& key );
    virtual std::string CurrentLanguage();

    virtual std::string GetSuggestedFont();

    virtual std::string SpecialField( const std::string& langType, const std::string& field, const std::string& key );
    virtual std::string SpecialField( const std::string& langType, const std::string& field, int key );
    virtual int SpecialFieldCount( const std::string& langType, const std::string& field );

    protected:
    std::string m_currentLanguage;
    std::map< std::string, std::string > m_gameText;

    bool LoadLanguageFile( const std::string& path );
};

}


#endif // #ifdef NOLUA

#endif // #ifndef _KUKO_LUALESSLANGUAGE
