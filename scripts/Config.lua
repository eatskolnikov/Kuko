print( "Config.lua loaded" )

function Config_GetOption( key )
	if ( config == nil or config[ key ] == nil ) then
		return "NOTFOUND"
	end
	return config[ key ]
end
