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
