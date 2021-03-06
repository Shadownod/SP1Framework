#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "tutorial.h"
#include "highscore.h"

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_SPACE,
    K_COUNT,
    K_RETURN,
    K_BACKSPACE,
    K_RSHIFT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
	S_SPLASHSCREEN,
	S_GAME,
	S_COUNT,
	S_MENU,
	S_TUTORIAL,
    S_STORY,
    S_HIGHSCORE
};

// struct for the game character
struct SGameChar
{
	COORD m_cLocation;
	bool  m_bActive;
};

struct Wall
{
	COORD w_location;
};

enum EPLAYERSTATES
{
	P_ALIVE,
	P_DEAD,
	P_POISONED
};

void init(void);      // initialize your variables, allocate memory, etc
void getInput(void);      // get input from player
void update(double dt); // update the game and the state of the game
void render(void);      // renders the current state of the game to the console
void shutdown(void);      // do clean up, free memory

void  renderTutorial();		//renders Tutorial Screen
void renderMenu();			//renders Main Menu
void splashScreenWait();    // waits for time to pass in splash screen
void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void TrapFlame(); //Flame Geyser trap
void TrapPoison(); //Poison Mist trap
void TrapSpike();  //Spike trap
void PlayerState();
void PlayerFire();
void PlayerSpike();
Wall MakeWall(int CoordX, int CoordY);
void renderStory();
void processhighscore();
void renderhighscoreboard();
#endif // _GAME_H