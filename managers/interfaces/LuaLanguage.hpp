#ifndef _KUKO_LUALANGUAGE
#define _KUKO_LUALANGUAGE

#ifndef NOLUA

#include "ILanguage.hpp"

namespace kuko
{

class LuaLanguage : public ILanguage
{
    public:
    LuaLanguage();
    virtual ~LuaLanguage();

    virtual bool AddLanguage( const std::string& id, const std::string& path );

    virtual std::string Text( const std::string& key );
    virtual std::string Text( const std::string& langType, const std::string& key );
    virtual std::string CurrentLanguage();

    virtual std::string GetSuggestedFont();

    virtual std::string SpecialField( const std::string& langType, const std::string& field, const std::string& key );
    virtual std::string SpecialField( const std::string& langType, const std::string& field, int key );
    virtual int SpecialFieldCount( const std::string& langType, const std::string& field );

    protected:
    virtual std::string m_currentLanguage;
}

}


#endif // #ifndef NOLUA

#endif // #ifndef _KUKO_LUALANGUAGE
