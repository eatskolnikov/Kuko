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
	return elements[ index ][ property ]
end
