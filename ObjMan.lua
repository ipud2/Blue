# usr/bin/lua

local ObjMan = { };
ObjMan.objs = { };

function ObjMan:addObj( obj )
	if obj.id ~= nil and self.objs[obj.id] == nil then  
		self.objs[obj.id] = obj;
		print( "Added " .. obj.id .. " to ObjMan");
	end
end

function ObjMan:removeObj( id )
	if self.objs[id] ~= nil then -- if check for debugging prompt.. no point in checking if something is nil just to make it nil.
		self.objs[id] = nil;
		print( id .. " Removed Successfully!" );
	else print( "tried to remove an object that doesn't exist! ".. id ); 
	end
end

function ObjMan:handleEvent( event )
	if self.objs[event.receiverID] ~= nil then
		self.objs[event.receiverID]:handleEvent( event );
	end
end

function ObjMan:update( )
	for i in pairs( self.objs ) do 
		if self.objs[i] ~= nil then 
			self.objs[i]:update(); 
		end 
	end
end

function ObjMan:get( id )
	return self.objs[i];
end

return ObjMan;
