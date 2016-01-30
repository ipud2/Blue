# usr/bin/lua

local Animation = { currentFrame = 1, numFrames = 0, frameTime = 1, frameCycle = 1, frames = { } };
function Animation:create( frameWidth, frameHeight, startX, startY, numFrames, frameTime )
	self.numFrames = numFrames or 0;
	self.frameTime = frameTime or 0;
	local X = startX or 0; local Y = startY or 0;
	print( "CreateAnimation StartPos: " .. X .. ", " .. Y );
	local index = 1;	
	self.frames = {};
	print( "Made It!" );
	while X < frameWidth * numFrames do
		self.frames[index] = {};
		self.frames[index].x = X;
		self.frames[index].y = Y;
		self.frames[index].width = frameWidth;
		self.frames[index].height = frameHeight;
		X = X + frameWidth;
		index = index + 1;			
	end
end
function Animation:update(  )
	if self.frameCycle < self.frameTime then
		self.frameCycle = self.frameCycle + 1;
	else
		if self.currentFrame < self.numFrames then
			self.currentFrame = self.currentFrame + 1;
		else
			self.currentFrame = 1;
		end
		self.frameCycle = 1;
	end
	local rect = self.frames[self.currentFrame];
	return rect;
end

return Animation;
