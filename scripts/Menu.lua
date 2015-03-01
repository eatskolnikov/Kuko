print( "Menu.lua loaded" )

function Menu_GetElementCount()
	count = 0
	if ( elements == nil ) then
		return 0
	end

	for key, value in pairs( elements ) do
		count = count + 1
	end
	return count
end

function Menu_GetElementProperty( index, property )
	if ( elements == nil or elements[ index ][ property ] == nil ) then
		if ( property == "centered_text" ) then return 0 end
		return ""
	end
	return elements[ index ][ property ]
end
