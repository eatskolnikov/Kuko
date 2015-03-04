print( "State.lua loaded" )

function State_SetupState()
	if ( state ~= nil ) then
		state.Setup()
	end
end
