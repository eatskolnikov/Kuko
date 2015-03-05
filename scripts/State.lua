print( "State.lua loaded" )

function State_SetupState()
	if ( state ~= nil ) then
		state.Setup()
	end
end

function State_GetPrerequisites()
	if ( state ~= nil ) then
		return state.GetPrerequisites()
	end
end

function State_Update()
	if ( state ~= nil ) then
		state.Update()
	end
end

function State_GetEntityCount()
	if ( state ~= nil ) then
		return state.GetEntityCount()
	end
	return 0
end

function State_GetEntityName( index )
	if ( state ~= nil ) then
		return state.GetEntityAtIndex( index ).name
	end
	return ""
end

function State_GetEntityPosition( nameKey )
	if ( state ~= nil ) then
		ent = state.entities[ nameKey ]
		return ent.position.x, ent.position.y, ent.position.w, ent.position.h
	end
	return 0, 0, 0, 0
end

function State_GetEntityTexture( nameKey )
	if ( state ~= nil ) then
		return state.entities[ nameKey ].texture
	end
	return ""
end

function State_GetEntityFrame( nameKey )
	if ( state ~= nil ) then
		return state.entities[ nameKey ].frame
	end
	return 0
end

function State_HandleInput( input )
	if ( state ~= nil ) then
		return state.HandleInput( input )
	end
end

