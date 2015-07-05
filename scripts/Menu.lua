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

function Menu_GetOptionProperty( property )
	if ( menu_options == nil or menu_options[ property ] == nil ) then
		if ( property == "centered_text" ) then return 0 end
		return ""
	end
	return menu_options[ property ]
end

function Menu_GetAssetCount()
	if ( assets == nil ) then return 0 end
	return #assets
end

function Menu_GetAssetTitle( index )
	if ( assets == nil ) then 
		print( "assets not found" )
		return "NOTFOUND" 
	end
	
	if ( assets[ index ] == nil ) then 
		print( "assets[ " .. index .. " ] not found" )
		return "NOTFOUND" 
	end
	
	if ( assets[ index ][ "name" ] == nil ) then 
		print( "assets[ " .. index .. " ][ name ] not found" )
		return "NOTFOUND" 
	end
	
	return assets[ index ][ "name" ]
end

function Menu_GetAssetPath( index )
	if ( assets == nil or assets[ index ] == nil or assets[ index ][ "path" ] == nil ) then return "NOTFOUND" end
	return assets[ index ][ "path" ]
end
