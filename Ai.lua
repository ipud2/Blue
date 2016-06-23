# usr/bin/lua
register_ai( );

local Ai = {};

function Ai:seekPos( currentX, currentY, targetX, targetY, currentVel, maxSpeed, maxAccel )
		
	local headingX, headingY = ai_track( currentX, currentY, targetX, targetY );
	
	--[[
		Need to write a basic physics lib to make this easier have structs like:
		struct velocity {
			heading // in degrees
			speed
			maxSpeed
		}
		struct acceleration {
			currentAccel
			maxAccel
		}
		struct physicsBody {
			pos
			size
			mass
			velocity
			accelration
			inertia
		}
	
	
	--]]
end

return Ai;
