# usr/bin/lua

local ControlMap = {};

ControlMap.MainMenu = {};
ControlMap.Game = {};
ControlMap.PauseMenu = {};

ControlMap.MainMenu.moveUp = "up";
ControlMap.MainMenu.moveDown = "down";
ControlMap.MainMenu.select = "return";
ControlMap.MainMenu.exit = "escape";

ControlMap.Game.moveUp = "up";
ControlMap.Game.moveDown = "down";
ControlMap.Game.moveLeft = "left";
ControlMap.Game.moveRight = "right";
ControlMap.Game.changeGreen = "A";
ControlMap.Game.changeBlack = "S";
ControlMap.Game.pauseGame = "P";

ControlMap.PauseMenu.moveUp = "up";
ControlMap.PauseMenu.moveDown = "down";
ControlMap.PauseMenu.select = "return";
ControlMap.PauseMenu.exitMenu = "P";

return ControlMap;
