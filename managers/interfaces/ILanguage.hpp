#ifndef _KUKO_ILANGUAGE
#define _KUKO_ILANGUAGE

#include <string>

namespace kuko
{
    class ILanguage
    {
        public:
        virtual ~ILanguage() { ; }

        virtual bool AddLanguage( const std::string& id, const std::string& path ) = 0;

        virtual std::string Text( const std::string& key ) = 0;
        virtual std::string Text( const std::string& langType, const std::string& key ) = 0;
        virtual std::string CurrentLanguage() = 0;

        virtual std::string GetSuggestedFont() = 0;

        virtual std::string SpecialField( const std::string& langType, const std::string& field, const std::string& key ) = 0;
        virtual std::string SpecialField( const std::string& langType, const std::string& field, int key ) = 0;
        virtual int SpecialFieldCount( const std::string& langType, const std::string& field ) = 0;

        protected:
        std::string m_currentLanguage;
    };
}

#endif
