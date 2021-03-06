# usr/bin/lua
register_system();
register_input();

local Keyboard = {};

Keyboard[0] = "A";
Keyboard[1] = "B";
Keyboard[2] = "C";
Keyboard[3] = "D";
Keyboard[4] = "E";
Keyboard[5] = "F";
Keyboard[6] = "G";
Keyboard[7] = "H";
Keyboard[8] = "I";
Keyboard[9] = "J";
Keyboard[10] = "K";
Keyboard[11] = "L";
Keyboard[12] = "M";
Keyboard[13] = "N";
Keyboard[14] = "O";
Keyboard[15] = "P";
Keyboard[16] = "Q";
Keyboard[17] = "R";
Keyboard[18] = "S";
Keyboard[19] = "T";
Keyboard[20] = "U";
Keyboard[21] = "V";
Keyboard[22] = "W";
Keyboard[23] = "X";
Keyboard[24] = "Y";
Keyboard[25] = "Z";
Keyboard[26] = "num0";
Keyboard[27] = "num1";
Keyboard[28] = "num2";
Keyboard[29] = "num3";
Keyboard[30] = "num4";
Keyboard[31] = "num5";
Keyboard[32] = "num6";
Keyboard[33] = "num7";
Keyboard[34] = "num8";
Keyboard[35] = "num9";
Keyboard[36] = "escape";
Keyboard[37] = "lControl";
Keyboard[38] = "lShift";
Keyboard[39] = "lAlt";
Keyboard[40] = "lSystem";
Keyboard[41] = "rControl";
Keyboard[42] = "rShift";
Keyboard[43] = "rAlt";
Keyboard[44] = "rSystem";
Keyboard[45] = "menu";
Keyboard[46] = "lBracket";
Keyboard[47] = "rBracket";
Keyboard[48] = "semicolon";
Keyboard[49] = "comma";
Keyboard[50] = "period";
Keyboard[51] = "quote";
Keyboard[52] = "slash";
Keyboard[53] = "backslash";
Keyboard[54] = "tilde";
Keyboard[55] = "equal";
Keyboard[56] = "dash";
Keyboard[57] = "space";
Keyboard[58] = "return";
Keyboard[59] = "backspace";
Keyboard[60] = "tab";
Keyboard[61] = "pageUp";
Keyboard[62] = "pageDown";
Keyboard[63] = "end";
Keyboard[64] = "home";
Keyboard[65] = "insert";
Keyboard[66] = "delete";
Keyboard[67] = "add";
Keyboard[68] = "subtract";
Keyboard[69] = "multiply";
Keyboard[70] = "divide";
Keyboard[71] = "left";
Keyboard[72] = "right";
Keyboard[73] = "up";
Keyboard[74] = "down";
Keyboard[75] = "numpad0";
Keyboard[76] = "numpad1";
Keyboard[77] = "numpad2";
Keyboard[78] = "numpad3";
Keyboard[79] = "numpad4";
Keyboard[80] = "numpad5";
Keyboard[81] = "numpad6";
Keyboard[82] = "numpad7";
Keyboard[83] = "numpad8";
Keyboard[84] = "numpad9";
Keyboard[85] = "f1";
Keyboard[86] = "f2";
Keyboard[87] = "f3";
Keyboard[88] = "f4";
Keyboard[89] = "f5";
Keyboard[90] = "f6";
Keyboard[91] = "f7";
Keyboard[92] = "f8";
Keyboard[93] = "f9";
Keyboard[94] = "f10";
Keyboard[95] = "f11";
Keyboard[96] = "f12";
Keyboard[97] = "f13";
Keyboard[98] = "f14";
Keyboard[99] = "f15";
Keyboard[100] = "pause";

Keyboard["A"] = 0;
Keyboard["B"] = 1;
Keyboard["C"] = 2;
Keyboard["D"] = 3;
Keyboard["E"] = 4;
Keyboard["F"] = 5;
Keyboard["G"] = 6;
Keyboard["H"] = 7;
Keyboard["I"] = 8;
Keyboard["J"] = 9;
Keyboard["K"] = 10;
Keyboard["L"] = 11;
Keyboard["M"] = 12;
Keyboard["N"] = 13;
Keyboard["O"] = 14;
Keyboard["P"] = 15;
Keyboard["Q"] = 16;
Keyboard["R"] = 17;
Keyboard["S"] = 18;
Keyboard["T"] = 19;
Keyboard["U"] = 20;
Keyboard["V"] = 21;
Keyboard["W"] = 22;
Keyboard["X"] = 23;
Keyboard["Y"] = 24;
Keyboard["Z"] = 25;
Keyboard["num0"] = 26;
Keyboard["num1"] = 27;
Keyboard["num2"] = 28;
Keyboard["num3"] = 29;
Keyboard["num4"] = 30;
Keyboard["num5"] = 31;
Keyboard["num6"] = 32;
Keyboard["num7"] = 33;
Keyboard["num8"] = 34;
Keyboard["num9"] = 35;
Keyboard["escape"] = 36;
Keyboard["lControl"] = 37;
Keyboard["lShift"] = 38;
Keyboard["lAlt"] = 39;
Keyboard["lSystem"] = 40;
Keyboard["rControl"] = 41;
Keyboard["rShift"] = 42;
Keyboard["rAlt"] = 43;
Keyboard["rSystem"] = 44;
Keyboard["menu"] = 45;
Keyboard["lBracket"] = 46;
Keyboard["rBraket"] = 47;
Keyboard["semicolon"] = 48;
Keyboard["comma"] = 49;
Keyboard["period"] = 50;
Keyboard["quote"] = 51;
Keyboard["slash"] = 52;
Keyboard["blackslash"] = 53;
Keyboard["tilde"] = 54;
Keyboard["equal"] = 55;
Keyboard["dash"] = 56;
Keyboard["space"] = 57;
Keyboard["return"] = 58;
Keyboard["backspace"] = 59;
Keyboard["tab"] = 60;
Keyboard["pageUp"] = 61;
Keyboard["pageDown"] = 62;
Keyboard["end"] = 63;
Keyboard["home"] = 64;
Keyboard["insert"] = 65;
Keyboard["delete"] = 66;
Keyboard["add"] = 67;
Keyboard["subtract"] = 68;
Keyboard["multiply"] = 69;
Keyboard["divide"] = 70;
Keyboard["left"] = 71;
Keyboard["right"] = 72;
Keyboard["up"] = 73;
Keyboard["down"] = 74;
Keyboard["numpad0"] = 75;
Keyboard["numpad1"] = 76;
Keyboard["numpad2"] = 77;
Keyboard["numpad3"] = 78;
Keyboard["numpad4"] = 79;
Keyboard["numpad5"] = 80;
Keyboard["numpad6"] = 81;
Keyboard["numpad7"] = 82;
Keyboard["numpad8"] = 83;
Keyboard["numpad9"] = 84;
Keyboard["f1"] = 85;
Keyboard["f2"] = 86;
Keyboard["f3"] = 87;
Keyboard["f4"] = 88;
Keyboard["f5"] = 89;
Keyboard["f6"] = 90;
Keyboard["f7"] = 91;
Keyboard["f8"] = 92;
Keyboard["f9"] = 93;
Keyboard["f10"] = 94;
Keyboard["f11"] = 95;
Keyboard["f12"] = 96;
Keyboard["f13"] = 97;
Keyboard["f14"] = 98;
Keyboard["f15"] = 99;
Keyboard["pause"] = 100;
-- Key is the string value of the button on the keyboard
-- passing the string value of the key as the key to self returns the index of that key in the table
-- C++ needs the numer to convert to keyboard enum
function Keyboard:isKeyPressed( key )
	-- return value of c++ method sf::isKeyDown through api magic
	return keyboard_isKeyPressed( self[key] );
end

return Keyboard;
