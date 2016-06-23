# usr/bin/lua
register_system( );
register_input( );

local Mouse = {};

Mouse[0] = "Left";
Mouse[1] = "Right";
Mouse[2] = "Middle";
Mouse[3] = "XButton1";
Mouse[4] = "XButton2";

Mouse["Left"] = 0;
Mouse["Right"] = 1;
Mouse["Middle"] = 2;
Mouse["XButton1"] = 3;
Mouse["XButton2"] = 4;

function Mouse:isButtonClicked( button )
	return mouse_isButtonClicked( button ); 
end

function Mouse:getPos( )
	local x, y = mouse_getPos();
	return { x = x; y = y };
end

return Mouse;
