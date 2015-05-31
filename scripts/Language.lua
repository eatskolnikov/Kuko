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

-- language["target"]["pronouns"][2]
-- language["helper"]["pronouns"]["English-he"]
function Language_GetSpecialField( langType, field, key )
	if ( language == nil or language[langType] == nil or language[langType][field] == nil or language[langType][field][key] == nil ) then
		return "NOTFOUND"
	end
	return language[langType][field][key]
end

-- Target / Pronouns
function Language_GetSpecialFieldCount( langType, field )
	count = 0
	if ( language[langType][field] == nil ) then
		return 0
	end

	for key, value in pairs( language[langType][field] ) do
		count = count + 1
	end
	return count
end
