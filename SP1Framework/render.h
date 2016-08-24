#include "game.h"
#include "Framework\console.h"
#include "highscore.h"


extern Console g_Console;
extern bool    g_abKeyPressed[];
extern EGAMESTATES g_eGameState;
extern double  g_dElapsedTime;
extern SGameChar   g_sChar;
extern bool WallSet;
extern vector<Wall> WallHolder;



void renderStory();
void  renderTutorial();		//renders Tutorial Screen
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void renderStory();
void renderMenu();
