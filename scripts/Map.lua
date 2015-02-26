print( "Map.lua loaded" )

function Map_GetWidth()
	if ( level == nil ) then return 0 end
	return level[ "width" ]
end

function Map_GetHeight()
	if ( level == nil ) then return 0 end
	return level[ "height" ]
end

function Map_GetTileType( index )
    return level[ "layers" ][1][ "data" ][ index ]
end

function Map_GetTilesetWidth()
    return level[ "tilesets" ][1][ "imagewidth" ] / level[ "tilesets" ][1][ "tilewidth" ]
end

function Map_GetTileWidth()
    return level[ "tilesets" ][1][ "tilewidth" ]
end
