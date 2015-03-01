print( "Language.lua loaded" )

function Language_GetText( key )
	if ( language == nil or language[ key ] == nil ) then
		return "NOTFOUND"
	end
	return language[ key ]
end

function Language_GetSuggestedFont()
	return language[ "suggested_font" ]
end
