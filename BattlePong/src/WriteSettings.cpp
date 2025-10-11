#include "WriteSettings.h"
#include "Settings.h"
#include <GameUtilities/Core/PreferencesManager.h>
#include "Log.h"
#include "SFMLFunctions.h"

WriteSettings::WriteSettings()
{
    BP_LOG_TRACE(__FUNCTION__);
    read();
}


void WriteSettings::read()
{
    BP_LOG_TRACE(__FUNCTION__);
    GU::Core::PreferencesManager prefMan(Settings::preferencesFile);

    //Load game settings
    Settings::dimensions.x = prefMan.read("Dimension_x", Settings::dimensions.x);
    Settings::dimensions.y = prefMan.read("Dimension_y", Settings::dimensions.y);
    Settings::ai = prefMan.read("Difficulty", Settings::ai.toAnsiString()).toStdString();
    Settings::currentTheme = prefMan.read("Theme", Settings::currentTheme);
    Settings::currentBackground = prefMan.read("Background", Settings::currentBackground);

    #ifdef DEBUG
        Settings::frameRate = prefMan.read("FrameRate", Settings::frameRate);
        Settings::ballSpeed = prefMan.read("BallSpeed", Settings::ballSpeed);
        Settings::paddleSpeed = prefMan.read("PaddleSpeed", Settings::paddleSpeed);
        Settings::wallThickness = prefMan.read("WallThickness", Settings::wallThickness);
        Settings::ballRadius = prefMan.read("BallRadius", Settings::ballRadius);
    #endif

    //Load keyboard preferences
    Settings::keyboardControlUp = toString(static_cast<sf::Keyboard::Key>(prefMan.read("KeyboardControlUp", toKey(Settings::keyboardControlUp)))).toAnsiString();
    Settings::keyboardControlDown = toString(static_cast<sf::Keyboard::Key>(prefMan.read("KeyboardControlDown", toKey(Settings::keyboardControlDown)))).toAnsiString();
    Settings::keyboardControlLeft = toString(static_cast<sf::Keyboard::Key>(prefMan.read("KeyboardControlLeft", toKey(Settings::keyboardControlLeft)))).toAnsiString();
    Settings::keyboardControlRight = toString(static_cast<sf::Keyboard::Key>(prefMan.read("KeyboardControlRight", toKey(Settings::keyboardControlRight)))).toAnsiString();
    Settings::keyboardControlMenu = toString(static_cast<sf::Keyboard::Key>(prefMan.read("KeyboardControlMenu", toKey(Settings::keyboardControlMenu)))).toAnsiString();
    Settings::keyboardControlNext = toString(static_cast<sf::Keyboard::Key>(prefMan.read("KeyboardControlNext", toKey(Settings::keyboardControlNext)))).toAnsiString();
    Settings::keyboardControlSelect = toString(static_cast<sf::Keyboard::Key>(prefMan.read("KeyboardControlSelect", toKey(Settings::keyboardControlSelect)))).toAnsiString();

    //Load joystick preferences
    Settings::joystickControlMenu = prefMan.read("PlayerJoystickControlMenu", Settings::joystickControlMenu);
    Settings::joystickControlNext = prefMan.read("PlayerJoystickControlNext", Settings::joystickControlNext);
    Settings::joystickControlSelect = prefMan.read("PlayerJoystickControlSelect", Settings::joystickControlSelect);

    //Load Box2D Settings
    #ifdef  DEBUG
        Settings::b2aabb = prefMan.read("b2aabb", Settings::b2aabb);
        Settings::b2shapes = prefMan.read("b2shapes", Settings::b2shapes);
        Settings::b2centerOfMass = prefMan.read("b2centerOfMass", Settings::b2centerOfMass);
        Settings::b2joints = prefMan.read("b2joints", Settings::b2joints);
        Settings::b2pair = prefMan.read("b2pair", Settings::b2pair);
        Settings::velocityIterations = prefMan.read("VelocityIterations", Settings::velocityIterations);
        Settings::positionIterations = prefMan.read("PositionIterations", Settings::positionIterations);
    #endif
 
    //Sound settings
    Settings::musicVolume = prefMan.read("MusicVolume", Settings::musicVolume);
    Settings::soundVolume = prefMan.read("SoundVolume", Settings::soundVolume);
    Settings::currentSong = prefMan.read("Music", Settings::currentSong);

    //Network settings
    Settings::port = prefMan.read("Port", Settings::port);
    
    //Load log settings
    Settings::logSeverity = prefMan.read("LogSeverity", Settings::logSeverity);

}

void WriteSettings::write()
{
    BP_LOG_TRACE(__FUNCTION__);
    GU::Core::PreferencesManager prefMan(Settings::preferencesFile);
    
    //Write game settings
    prefMan.write("Dimension_x", Settings::dimensions.x);
    prefMan.write("Dimension_y", Settings::dimensions.y);
    prefMan.write("Difficulty", Settings::ai.toAnsiString());
    prefMan.write("Theme", Settings::currentTheme);
    prefMan.write("Background", Settings::currentBackground);
    
    #ifdef  DEBUG
        prefMan.write("FrameRate", Settings::frameRate);
        prefMan.write("BallSpeed", Settings::ballSpeed);
        prefMan.write("PaddleSpeed", Settings::paddleSpeed);
        prefMan.write("WallThickness", Settings::wallThickness);
        prefMan.write("BallRadius", Settings::ballRadius);
    #endif

    //Write keyboard preferences
    prefMan.write("KeyboardControlUp", toKey(Settings::keyboardControlUp));
    prefMan.write("KeyboardControlDown", toKey(Settings::keyboardControlDown));
    prefMan.write("KeyboardControlLeft", toKey(Settings::keyboardControlLeft));
    prefMan.write("KeyboardControlRight", toKey(Settings::keyboardControlRight));
    prefMan.write("KeyboardControlMenu", toKey(Settings::keyboardControlMenu));
    prefMan.write("KeyboardControlNext", toKey(Settings::keyboardControlNext));
    prefMan.write("KeyboardControlSelect", toKey(Settings::keyboardControlSelect));
                        
    //Write joystick preferences
    prefMan.write("PlayerJoystickControlMenu", Settings::joystickControlMenu);
    prefMan.write("PlayerJoystickControlNext", Settings::joystickControlNext);
    prefMan.write("PlayerJoystickControlSelect", Settings::joystickControlSelect);

    //Write Box2D Settings
    #ifdef  DEBUG
        prefMan.write("b2aabb", Settings::b2aabb);
        prefMan.write("b2shapes", Settings::b2shapes);
        prefMan.write("b2centerOfMass", Settings::b2centerOfMass);
        prefMan.write("b2joints", Settings::b2joints);
        prefMan.write("b2pair", Settings::b2pair);
        prefMan.write("VelocityIterations", Settings::velocityIterations);
        prefMan.write("PositionIterations", Settings::positionIterations);
    #endif
    
    //Sound settings
    prefMan.write("MusicVolume", Settings::musicVolume);
    prefMan.write("SoundVolume", Settings::soundVolume);
    prefMan.write("Music", Settings::currentSong);
            
    //Network settings
    prefMan.write("Port", Settings::port);
    
    //Load log settings
    prefMan.write("LogSeverity", Settings::logSeverity);
}

WriteSettings::~WriteSettings()
{
    BP_LOG_TRACE(__FUNCTION__);
    write();
}

