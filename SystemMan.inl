#include "SystemMan.h"

///
/// \brief SystemMan::Events::update
/// This method updates all deleyed events and checks if they should be added to current events
void SystemMan::Events::update( void )
{
    unsigned int numDelayedEvents = delayedEvents.size();
    while( numDelayedEvents > 0 )
    {
        if( delayedEvents[numDelayedEvents].delay == 0 )
        {
            // add delay event ot current events and remove it from delayed Events
            currentEvents.push( delayedEvents[numDelayedEvents - 1] );
            delayedEvents.erase( delayedEvents.begin() + numDelayedEvents - 1 ); // removes the delayed event at the index
        }
        else
        {
            delayedEvents[numDelayedEvents].delay = delayedEvents[numDelayedEvents].delay - 1;
        }
        numDelayedEvents = numDelayedEvents - 1;
    }
}

/// \brief addEvent
/// \param event
///
void SystemMan::Events::addEvent( sf::Event event ) {
    SystemMan::Events::Event newEvent = SystemMan::Events::Event();
    switch( event.type ) {
    case sf::Event::Closed: newEvent.attributes.insert( std::pair<std::string, std::string>( "name", "WINDOW_CLOSED" ) ); break;
    case sf::Event::Resized:
        newEvent.attributes.insert( std::pair<std::string, std::string>( "name", "WINDOW_RESIZED" ) );
        // also needs to pass new size params
    break;
    case sf::Event::LostFocus: newEvent.attributes.insert( std::pair<std::string, std::string>( "name", "WINDOW_LOST_FOCUS" ) ); break;
    case sf::Event::GainedFocus: newEvent.attributes.insert( std::pair<std::string, std::string>( "name", "WINODW_GAINED_FOCUS" ) ); break;
    case sf::Event::TextEntered:
        newEvent.attributes.insert( std::pair<std::string, std::string>( "name", "TEXT_ENTERED" ) );
        newEvent.attributes.insert( std::pair<std::string, std::string>( "key", std::to_string( event.key.code ) ) );
        break;
    case sf::Event::KeyPressed:
        newEvent.attributes.insert( std::pair<std::string, std::string>( "name", "KEY_PRESSED" ) );
        newEvent.attributes.insert( std::pair<std::string, std::string>( "key", std::to_string( event.key.code ) ) );
        break;
    case sf::Event::KeyReleased:
        newEvent.attributes.insert( std::pair<std::string, std::string>( "name", "KEY_RELEASED" ) );
        newEvent.attributes.insert( std::pair<std::string, std::string>( "key", std::to_string( event.key.code ) )  );
        break;
    case sf::Event::MouseWheelMoved:
        newEvent.attributes.insert( std::pair<std::string, std::string>( "name", "MOUSE_WHEEL_MOVED" ) );
        newEvent.attributes.insert( std::pair<std::string, std::string>( "delta", std::to_string( event.mouseWheel.delta ) ) );
        newEvent.attributes.insert( std::pair<std::string, std::string>( "x", std::to_string( event.mouseWheel.x )  ) );
        newEvent.attributes.insert( std::pair<std::string, std::string>( "y", std::to_string( event.mouseWheel.y ) ) );
        break;
    case sf::Event::MouseButtonPressed:
        newEvent.attributes.insert( std::pair<std::string, std::string>( "name", "MOUSE_BUTTON_PRESSED" ) );
        // tell lua which button was pressed
        switch( event.mouseButton.button ) {
            case sf::Mouse::Button::Left:     newEvent.attributes.insert( std::pair<std::string, std::string>( "button", "LEFT_BUTTON" ) );   break;
            case sf::Mouse::Button::Right:    newEvent.attributes.insert( std::pair<std::string, std::string>( "button", "RIGHT_BUTTON" ) );  break;
            case sf::Mouse::Button::Middle:   newEvent.attributes.insert( std::pair<std::string, std::string>( "button", "MIDDLE_BUTTON" ) ); break;
            case sf::Mouse::Button::XButton1: newEvent.attributes.insert( std::pair<std::string, std::string>( "button", "X1_BUTTON" ) );     break;
            case sf::Mouse::Button::XButton2: newEvent.attributes.insert( std::pair<std::string, std::string>( "button", "X2_BUTTON" ) );     break;
            default: assert( "Invalid Mouse Button Pressed" == std::string() );  break;
        }
        newEvent.attributes.insert( std::pair<std::string, std::string>( "x", std::to_string( event.mouseButton.x ) ) );
        newEvent.attributes.insert( std::pair<std::string, std::string>( "y", std::to_string( event.mouseButton.y ) ) );
        break;
    case sf::Event::MouseButtonReleased:
        newEvent.attributes.insert( std::pair<std::string, std::string>( "name", "MOUSE_BUTTON_RELEASED" ) );
        // tell lua which button was pressed
        switch( event.mouseButton.button ) {
        case sf::Mouse::Button::Left:     newEvent.attributes.insert( std::pair<std::string, std::string>( "button", "LEFT_BUTTON" ) );   break;
        case sf::Mouse::Button::Right:    newEvent.attributes.insert( std::pair<std::string, std::string>( "button", "RIGHT_BUTTON" ) );  break;
        case sf::Mouse::Button::Middle:   newEvent.attributes.insert( std::pair<std::string, std::string>( "button", "MIDDLE_BUTTON" ) ); break;
        case sf::Mouse::Button::XButton1: newEvent.attributes.insert( std::pair<std::string, std::string>( "button", "X1_BUTTON" ) );     break;
        case sf::Mouse::Button::XButton2: newEvent.attributes.insert( std::pair<std::string, std::string>( "button", "X2_BUTTON" ) );     break;
        default: assert( "Invalid Mouse Button released" == std::string() );  break;
        }      
        newEvent.attributes.insert( std::pair<std::string, std::string>( "x", std::to_string( event.mouseButton.x ) ) );
        newEvent.attributes.insert( std::pair<std::string, std::string>( "y", std::to_string( event.mouseButton.y ) ) );
        break;
    case sf::Event::MouseMoved:
        newEvent.attributes.insert( std::pair<std::string, std::string>( "name", "MOUSE_MOVED" ) );
        newEvent.attributes.insert( std::pair<std::string, std::string>( "x", std::to_string( event.mouseButton.x ) ) );
        newEvent.attributes.insert( std::pair<std::string, std::string>( "y", std::to_string( event.mouseButton.y ) ) );
        break;
    case sf::Event::MouseEntered: newEvent.attributes.insert( std::pair<std::string, std::string>( "name", "MOUSE_ENTERED" ) ); break;
    case sf::Event::MouseLeft: newEvent.attributes.insert( std::pair<std::string, std::string>( "name", "MOUSE_LEFT" ) ); break;
        /*
    case sf::Event::JoystickButtonPressed: break;
    case sf::Event::JoystickButtonReleased: break;
    case sf::Event::JoystickMoved: break;
    case sf::Event::JoystickConnected: break;
    case sf::Event::JoystickDisconnected: break;
        */
    default:
        assert( "EventHandling Default case reached IMPOSSIBLE!!" == std::string() );
        break;
    }
    // add sender and receiver ids to the created table, because these are all system events they will all have the same ids..
    newEvent.attributes.insert( std::pair<std::string, std::string>( "senderID", "ENGINE" ) );
    newEvent.attributes.insert( std::pair<std::string, std::string>( "receiverID", "LUA" ) );
    newEvent.delay = 0;
    addCustomEvent( newEvent );
}
/// \brief addEvent
/// This method is to add custom game events to the event queue
void SystemMan::Events::addCustomEvent( SystemMan::Events::Event event )
{
    if( event.delay > 0 ) delayedEvents.push_back( event );
    else currentEvents.push( event );
}
/// \brief luaAddEvent
/// This method allows lua to add events to the the event queue
///  \param luaState
/// STACK
/// 4 delay       -1
/// 3 senderID    -2
/// 2 receiverID  -3
/// 1 name        -4
int SystemMan::Events::luaAddEvent( lua_State* luaState )
{
    // table is in the stack at index 't'
    if( !lua_istable( luaState, 1 ) ) assert( "No event passed to the add event method!!" == std::string( ) );

    Event event = Event( );
    lua_pushnil( luaState );  // first key
    while( lua_next( luaState, 1 ) != 0 )
    {
      event.attributes.insert( std::pair<std::string, std::string>( lua_tostring( luaState, -2 ), lua_tostring( luaState, -1 )  ) );
      // removes 'value'; keeps 'key' for next iteration
      lua_pop( luaState, 1);
    }
    event.delay = 0;
    addCustomEvent( event );
    return 0;
}
/// \brief luaGetEvent
/// Pulls the next event off the current event queue and returns it to lua
/// \return
/// Returns an event
int SystemMan::Events::luaGetEvent( lua_State* luaState )
{
    if( currentEvents.size() > 0 ) {
        Event event = currentEvents.front();
        currentEvents.pop();
        lua_createtable( luaState, 0, 0 );
        for( auto i : event.attributes ) {
            lua_pushstring( luaState, i.second.c_str( ) );
            lua_setfield( luaState, -2, i.first.c_str( ) );
        }
        // std::cout << "Getting event, Name: " << event.attributes.at("name") << " Sender: " << event.attributes["senderID"]<< std::endl;
    }
    else lua_pushboolean( luaState, false );
    return 1;
}
/// \brief luaRegister
/// Registers the Event system to lua
int SystemMan::Events::luaRegister( lua_State* luaState ) {
    static bool alreadyRegistered = false;
    if( !alreadyRegistered ) {
        lua_pushcfunction( luaState, SystemMan::Events::luaAddEvent );
        lua_setglobal( luaState, "add_event" );
        lua_pushcfunction( luaState, SystemMan::Events::luaGetEvent );
        lua_setglobal( luaState, "get_event" );
        alreadyRegistered = true;
    }
    return 0;
}

int SystemMan::Input::luaIsKeyPressed( lua_State* luaState ) {
    lua_pushboolean( luaState, sf::Keyboard::isKeyPressed( (sf::Keyboard::Key)lua_tointeger( luaState, -1 ) ) );
    return 1;
}

int SystemMan::Input::luaIsMouseClicked( lua_State* luaState ) {
    lua_pushboolean( luaState, sf::Mouse::isButtonPressed( (sf::Mouse::Button)lua_tointeger( luaState, -1 ) ) );
    return 1;
}
int SystemMan::Input::luaGetMousePosition( lua_State* luaState )
{
    // i need to add the renderWindow as arg to gtPos function to gt relative coords
    lua_pushnumber( luaState, sf::Mouse::getPosition( (*Window) ).x );
    lua_pushnumber( luaState, sf::Mouse::getPosition( (*Window) ).y );
    return 2;
}

int SystemMan::Input::luaRegister( lua_State* luaState ) {
    static bool alreadyRegistered = false;
    if( !alreadyRegistered ) {
        lua_pushcfunction( luaState, SystemMan::Input::luaIsKeyPressed );
        lua_setglobal( luaState, "keyboard_isKeyPressed" );
        lua_pushcfunction( luaState, SystemMan::Input::luaIsMouseClicked );
        lua_setglobal( luaState, "mouse_isButtonClicked" );

        lua_pushcfunction( luaState, SystemMan::Input::luaGetMousePosition );
        lua_setglobal( luaState, "mouse_getPos" );
        alreadyRegistered = true;
    }
    return 0; // returns SYSTEM_EVENTS table
}

int SystemMan::luaRegister( lua_State* luaState ) {
    static bool alreadyRegistered = false;
    if( !alreadyRegistered ) {
        lua_pushcfunction( luaState, SystemMan::Events::luaRegister );
        lua_setglobal( luaState, "register_event" );
        lua_pushcfunction( luaState, SystemMan::Input::luaRegister );
        lua_setglobal( luaState, "register_input" );
        alreadyRegistered = true;
    }
    return 0;
}
