#pragma once
#include <string>

//info
const std::string INFO_MODE = "Info";
const std::string ENGINE_ON_MODE = "EngineOn";
const std::string ENGINE_OFF_MODE = "EngineOff";
const std::string SET_GEAR_MODE = "SetGear";
const std::string SET_SPEED_MODE = "SetSpeed";
const std::string UNKNOWN_MODE = "Unknown mode";

const std::string ENGINE_CONDITION_INFO = "Engine condition: ";
const std::string DIRECTION_INFO = "Direction of movement: ";
const std::string SPEED_INFO = "Speed: ";
const std::string GEAR_INFO = "Gear: ";

const std::string ENGINE_ON = "The engine is on\n";
const std::string ENGINE_OFF = "The engine is off\n";

const std::string SET_GEAR = "Gear is set to ";
const std::string SET_SPEED = "The speed is set to ";

//errors
const std::string ERROR_ENGINE_ON = "Engine failed to turn on\n";
const std::string ERROR_ENGINE_OFF = "Engine failed to turn off\nThe engine can be turned off, if the speed is 0, the transmission is neutral in the direction of standing\n";

const std::string ERROR_NON_NUMBER = "You entered not a number\n";

const std::string ERROR_SET_GEAR = "Gear is not set\n";
const std::string ERROR_SET_GEAR_NUMBER = "Gear must be a number from -1 to 5\n";

const std::string ERROR_SET_SPEED = "The speed is not set\n";
const std::string ERROR_SET_SPEED_NUMBER = "The speed must be a number from 0 to 150\n";
