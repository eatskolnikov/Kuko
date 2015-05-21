print( "Config.lua loaded" )

function Config_GetOption( key )
	if ( config == nil or config[ key ] == nil ) then
		return "NOTFOUND"
	end
	return config[ key ]
end

function Savegame_GetData( key )
	if ( save == nil or save[ key ] == nil ) then
		return "NOTFOUND"
	end
	return save[ key ]
end
