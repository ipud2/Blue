# usr/bin/lua

local Clone = require( "Clone" )
--local Sprite = require( "Sprite" );
local Texture = require( "Texture" );
local Rectangle = require( "Rectangle" );

local MapMan = {}

function MapMan:loadMap( map )
	local world = Clone( require( "World" ) );
	world:create( );
	-- generate texture rects for all possible tiles being loaded 
	local counter = 1;
	local tileSet = {};
	tileSet[0] = { texId = "NONE", rect = { x = 0; y = 0; width = 32; height = 32; } };
	for k, v in pairs( map.tilesets ) do 	
		-- load the texture for the current tileSet
		world.textures[v.name] = Clone( Texture );
		world.textures[v.name]:create( v.name, v.image );
		-- build rectangles that will cover the area on the texture that is the tile ( divide texture into tiles )
		local y = 0;
		while y < v.imageheight - 1 do
			local x = 0;
			while x < v.imagewidth - 1 do
				tileSet[counter] = { texId = v.name; rect = { x = x; y = y; width = v.tilewidth; height = v.tileheight; }; };
				counter = counter + 1;
				x = x + v.tilewidth;			
			end
			y = y + v.tileheight;
		end
	end
	-- create and set up tile layers using texture rects
	for k, v in pairs( map.layers ) do
		world.layers[v.name] = addLayer(  ); -- add a layer to the engine
		if v.type == "tilelayer" then
			local x = 0;
			local y = 0;
			-- iterate through all tiles in the layer and create them in the engine with the correct tile as created above
			for i, j in pairs( v.data ) do
				if y < (v.height * tileSet[j].rect.height) - 1 then
					if j ~= 0 then
						world.tiles[i] = Clone( Rectangle );
						world.tiles[i]:create( ( v.name .. x .. y), world.layers[v.name], x, y, tileSet[j].rect.width, tileSet[j].rect.height );
						
						-- add special inf about tiles here i.e terrain info 
						-- could be done by running properties loop such as below with obj!!!
						
						
						shape_setTexture( world.tiles[i].id, tileSet[j].texId, true );
						shape_setTexRect( world.tiles[i].id, tileSet[j].rect.x, tileSet[j].rect.y, tileSet[j].rect.width, tileSet[j].rect.height );				
					end			
					if x < (v.width * tileSet[j].rect.width) - tileSet[j].rect.width then -- the minus 32 is to subtract the tilewidth not sure why but it fixes a problem with tiles being skewed
						x = x + tileSet[j].rect.width; 
					else
						x = 0;
						y = y + tileSet[j].rect.height;
					end
				end
			end
			-- buld up the object layer
		elseif v.type == "objectgroup" then
			-- cycle through objs in the layer building there base stats
			-- objects are handled much diferently then regular tiles 
			for i, j in pairs( v.objects ) do 
				local obj = Clone( require( j.properties.fileName ) );
				print( world.layers[v.name] );
				obj.layer = world.layers[v.name];
				
				obj.x = j.x;
				obj.y = j.y;
				obj.height = j.height;
				obj.width = j.width;
				for k, v in pairs( j.properties ) do
					obj[k] = v;
				end
				obj:create( )
				world.objs[obj.id] = obj;
			end	
		end
	end
	return world;
end

return MapMan;
