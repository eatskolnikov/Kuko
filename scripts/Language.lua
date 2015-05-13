print( "Language.lua loaded" )

function Language_GetText( key )
	if ( language == nil or language[ key ] == nil ) then
		return "NOTFOUND"
	end
	return language[ key ]
end

-- this is for if the language table is stored in something other than a variable named "language"
function Language_GetTextFromLanguage( key, langType )
	if ( language == nil or language[ langType ] == nil or language[ langType ][ key ] == nil ) then
		return "NOTFOUND"
	end
	return language[ langType ][ key ]
end

function Language_GetSuggestedFont()
	return language[ "suggested_font" ]
end
