// This is the main file for the game logic and function
//
//
#include "map.h"
#include "game.h"
#include "highscore.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];
bool	setTimeTrap = false;
int		timer;
int		lives = 3;
bool	getAntiPoisonPill = false;
bool	fireset = false;
extern bool lostlive;
extern string score;

vector<int> fireX;
vector<int> fireY;
vector<int> spikeX;
vector<int> spikeY;
vector<int> poisonX;
vector<int> poisonY;

vector<Wall> WallHolder;
bool WallSet = false;

int nMapArray[MAP_HEIGHT][MAP_WIDTH] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};


// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once
EPLAYERSTATES g_ePlayerState = P_ALIVE;


// Console object
Console g_Console(125, 30, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init(void)
{
	// Set precision for floating point output
	g_dElapsedTime = 0.0;
	g_dBounceTime = 0.0;

	// sets the initial state for the game
	//g_eGameState = S_SPLASHSCREEN;

	g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2 - 61;
	g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2 - 11;
	g_sChar.m_bActive = true;
	// sets the width, height and the font name to use in the console
	g_Console.setConsoleFont(0, 16, L"Consolas");
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown(void)
{
    
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput(void)
{
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_RETURN] = isKeyPressed(VK_RETURN);
    g_abKeyPressed[K_BACKSPACE] = isKeyPressed(VK_BACK);
    g_abKeyPressed[K_RSHIFT] = isKeyPressed(VK_RSHIFT);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
	// get the delta time
	g_dElapsedTime += dt;
	g_dDeltaTime = dt;

	switch (g_eGameState)
	{
	/*case S_SPLASHSCREEN: splashScreenWait(); // game logic for the splash screen
		break;*/
	case S_GAME: gameplay(); // gameplay logic when we are in the game
		break;
    //case S_HIGHSCORE: highscoreboard();
        //break;
	}
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
	clearScreen();      // clears the current screen and draw from scratch 
	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: renderSplashScreen();
		break;
	case S_GAME: renderGame();
		break;
	case S_MENU: renderMenu();
		break;
	case S_TUTORIAL: renderTutorial();
		break;
    case S_STORY: renderStory();
        break;
    case S_HIGHSCORE: renderhighscoreboard();
        //comparescore();
        break;
	}
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}
void renderhighscoreboard(){
    processUserInput();
    highscoreboard();
}

/*void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
		g_eGameState = S_MENU;
}
*/
void gameplay()            // gameplay logic
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveCharacter();    // moves the character, collision detection, physics, etc
	// sound can be played here too.
	PlayerFire();
	//PlayerPoison();
	//PlayerSpike();
    processhighscore();
    calculate();
}

void moveCharacter()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0)
	{
		for (int i = 0; i < WallHolder.size(); i++)
		{
			if ((g_sChar.m_cLocation.Y - 1) != WallHolder[i].w_location.Y)
			{
				if (i == (WallHolder.size() - 1))
				{
					//Beep(1440, 30);
					g_sChar.m_cLocation.Y--;
					bSomethingHappened = true;
				}
			}
			else if (g_sChar.m_cLocation.X != WallHolder[i].w_location.X)
			{
				if (i == (WallHolder.size() - 1))
				{
					//Beep(1440, 30);
					g_sChar.m_cLocation.Y--;
					bSomethingHappened = true;
				}
			}
			else
			{
				break;
			}
		}
	}
	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		for (int i = 0; i < WallHolder.size(); i++)
		{
			if ((g_sChar.m_cLocation.Y + 1) != WallHolder[i].w_location.Y)
			{
				if (i == (WallHolder.size() - 1))
				{
					//Beep(1440, 30);
					g_sChar.m_cLocation.Y++;
					bSomethingHappened = true;
				}

			}
			else if (g_sChar.m_cLocation.X != WallHolder[i].w_location.X)
			{
				if (i == (WallHolder.size() - 1))
				{
					//Beep(1440, 30);
					g_sChar.m_cLocation.Y++;
					bSomethingHappened = true;
				}
			}
			else
			{
				break;
			}
		}
	}

	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		for (int i = 0; i < WallHolder.size(); i++)
		{
			if ((g_sChar.m_cLocation.X - 1) != WallHolder[i].w_location.X)
			{
				if (i == (WallHolder.size() - 1))
				{
					//Beep(1440, 30);
					g_sChar.m_cLocation.X--;
					bSomethingHappened = true;
				}

			}
			else if (g_sChar.m_cLocation.Y != WallHolder[i].w_location.Y)
			{
				if (i == (WallHolder.size() - 1))
				{
					//Beep(1440, 30);
					g_sChar.m_cLocation.X--;
					bSomethingHappened = true;
				}
			}
			else
			{
				break;
			}
		}
	}
	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		for (int i = 0; i < WallHolder.size(); i++)
		{
			if ((g_sChar.m_cLocation.X + 1) != WallHolder[i].w_location.X)
			{
				if (i != (WallHolder.size() - 1))
				{
					continue;
				}
				else
				{
					//Beep(1440, 30);
					g_sChar.m_cLocation.X++;
					bSomethingHappened = true;
				}
			}
			else if (g_sChar.m_cLocation.Y != WallHolder[i].w_location.Y)
			{
				if (i != (WallHolder.size() - 1))
				{
					continue;
				}
				else
				{
					//Beep(1440, 30);
					g_sChar.m_cLocation.X++;
					bSomethingHappened = true;
				}
			}
			else
			{
				break;
			}
		}
	}
	if (g_abKeyPressed[K_SPACE])
	{
		g_sChar.m_bActive = !g_sChar.m_bActive;
		bSomethingHappened = true;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}

void processUserInput()
{
	// quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
    {
        g_bQuitGame = true;
    }
    if (g_abKeyPressed[K_BACKSPACE])
    {
        g_eGameState = S_MENU;
    }
}
void processhighscore()
{
    if (lives == 0)
    {
        g_eGameState = S_HIGHSCORE;
        
    }
}
void clearScreen()
{
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer(0x0F);
}

void renderSplashScreen()  // renders the splash screen
{


	COORD c = g_Console.getConsoleSize();
    c.Y = 0;
	c.X = g_Console.getConsoleSize().X;

	string line;
	ifstream myfile("splash2.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			c.Y += 1;
			g_Console.writeToBuffer(c, line, 0x03);
		}
		myfile.close();
	}
    if (g_abKeyPressed[K_SPACE])
    {
        g_eGameState = S_MENU;
    }
    processUserInput(); //allow user to quit game
	/*COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 20;
	g_Console.writeToBuffer(c, "Welcome to treasure hunt <WORKING!!!>.", 0x03);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 20;
	g_Console.writeToBuffer(c, "'W', 'S', 'A', 'D' keys to move", 0x09);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);*/
	/* COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 9;
	g_Console.writeToBuffer(c, "Testing for this title.", 0x03);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 20;
	g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);*/
}

void renderMenu()
{
	/*COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 9;
	g_Console.writeToBuffer(c, "Press <ENTER> to play!", 0x03);
	c.Y += 1;
	g_Console.writeToBuffer(c, "Press <SPACE> for tutorial");

	if (g_abKeyPressed[K_RETURN])
	{
	g_eGameState = S_GAME;
	}*/

	COORD c = g_Console.getConsoleSize();
	c.Y = 0;
	c.X = g_Console.getConsoleSize().X;

	string line;
	ifstream myfile("menu.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			c.Y += 1;
			g_Console.writeToBuffer(c, line, 0x03);
		}
		myfile.close();
	}
    lives = 3;
    score = "0";
	if (g_abKeyPressed[K_RETURN])
	{
		g_eGameState = S_GAME;
	}
	if (g_abKeyPressed[K_SPACE])
	{
		g_eGameState = S_TUTORIAL;
    }
    if (g_abKeyPressed[K_RSHIFT])
    {
        g_eGameState = S_STORY;
    }
    processUserInput(); //allow user to quit game
}
void renderGame()
{
	renderMap();        // renders the map to the buffer first
	renderCharacter();  // renders the character into the buffer
}
void renderMap()
{
	// Set up sample colours, and output shadings
	const WORD colors[] = {
		0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6,
		0x1F
	};

	//COORD c;
	/*for (int i = 0; i < 12; ++i)
	{
	c.X = 5 * i;
	c.Y = i + 1;
	colour(colors[i]);
	g_Console.writeToBuffer(c, " °±²Û", colors[i]);
	}*/
	//TrapPoison();
	//TrapFlame();
	//TrapSpike();

	/*string mapvar[] = { "i", "j", "k" };

	string line;
	ifstream myfile("map.txt");
	if (myfile.is_open())
	{
	while (getline(myfile, line))
	{
	c.Y += 1;
	g_Console.writeToBuffer(c, line, 0x1F);

	if (line == mapvar[0])
	{
	g_Console.writeToBuffer(c, "Û", 0xFF);
	}
	}
	myfile.close();
	}*/


	//c.X = 0;
	//c.Y = 0;
	//int count;
	//char ch = getchar();
	/*string line;
	ifstream myfile("map.txt");
	if (myfile.is_open())
	{
	while (getline(myfile, line))
	{
	c.Y += 1;
	//g_Console.writeToBuffer(c, line, 0x03);
	for (int i = 0; i < line.size(); i++)
	{
	count = line[i];

	if (count == '1')
	{
	count = TILE_WALL;
	g_Console.writeToBuffer(c, " ", 0x33);
	break;
	}

	else
	{
	g_Console.writeToBuffer(c, " ", 0x03);
	break;
	}
	}
	}


	myfile.close();
	}
	}*/


	/*for (int y = 0; y < MAP_HEIGHT; y++)
	{
	c.Y += 1;
	c.X = 0;
	for (int x = 0; x < MAP_WIDTH; x++)
	{
	c.X += 1;
	switch (nMapArray[y][x])
	{
	case TILE_FLOOR:
	g_Console.writeToBuffer(c, " ", colors[2]);
	break;
	case TILE_WALL:
	g_Console.writeToBuffer(c, " ", colors[4]);
	break;
	}
	}
	}*/




	/*for (int rows = 0; rows < g_Console.getConsoleSize().X; rows++)
	{
	g_Console.writeToBuffer(c, "²", colors[12]);
	c.X++;
	}
	c.X = 0;
	c.Y = 2;

	for (int column = 2; column < g_Console.getConsoleSize().Y - 1; column++)
	{
	g_Console.writeToBuffer(c, "²", colors[12]);

	for (int spacing = c.X; spacing < 3; spacing++)
	{
	g_Console.writeToBuffer(c, 32, colors[12]);
	}

	g_Console.writeToBuffer(c, "²", colors[12]);
	c.Y++;
	}

	for (int rows = 0; rows < g_Console.getConsoleSize().X; rows++)
	{
	g_Console.writeToBuffer(c, "²", colors[12]);
	c.X++;
	}*/

	char map[150][150];
	WallSet = false;

	COORD c;
	c.Y = 0;
	c.X = 0;

	ifstream myfile("map2.txt");

	if (myfile.is_open())
	{
		for (int i = 0; i < 24; i++)
		{
			for (int j = 0; j < 125; j++)
			{
				myfile >> map[i][j];
			}
		}
		myfile.close();                            // °±²Û
		for (int i = 0; i < 24; i++)
		{
			c.Y = i + 2;
			for (int j = 0; j < 125; j++) //94
			{
				c.X = j;
				if (map[i][j] == '1')
				{
					if (WallSet == false)
					{
						if (WallHolder.size() < 1)
						{
							WallHolder.push_back(MakeWall(c.X, c.Y));
						}
						else
						{
							if (c.X != WallHolder[0].w_location.X || c.Y != WallHolder[0].w_location.Y)
							{
								WallHolder.push_back(MakeWall(c.X, c.Y));
							}
							else
							{
								WallSet = true;
							}
						}
					}
					g_Console.writeToBuffer(c, '²', 0x60); //wall 6

				}

				if (map[i][j] == '0')
				{
					//map[i][j] = '|';
					g_Console.writeToBuffer(c, ' ', 0x81); //floor 8
				}

				if (map[i][j] == 'f')
				{
					g_Console.writeToBuffer(c, '±', 0x4E); //fire 4E
				}

				if (map[i][j] == 'p')
				{
					g_Console.writeToBuffer(c, '±', 0x5F); //poison 5
				}

				if (map[i][j] == 's')
				{
					g_Console.writeToBuffer(c, '°', 0x80); //spike
				}

				if (map[i][j] == 't')
				{
					g_Console.writeToBuffer(c, ' ', 0xEE); //treasure
				}

				if (map[i][j] == 'L')
				{
					g_Console.writeToBuffer(c, '/', 0x84); // lever
				}

				if (map[i][j] == 'o')
				{
					g_Console.writeToBuffer(c, 'o', 0x8E); // items
				}

				if (map[i][j] == 'w')
				{
					g_Console.writeToBuffer(c, '²', 0x14); // lever activated walls
				}

				if (map[i][j] == 'a')
				{
					g_Console.writeToBuffer(c, '²', 0x4F); // poison cure pill
				}

				if (map[i][j] == 'E')
				{
					g_Console.writeToBuffer(c, '>', 0xF2); // Exit
				}
				//g_Console.writeToBuffer(c, map[i][j]);
			}
		}
	}

}


void renderCharacter()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	if (g_sChar.m_bActive)
	{
		charColor = 0x0A;
	}
	g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
}

void renderFramerate()
{
	COORD c;
	std::ostringstream ss;
	/* displays the framerate

	ss << std::fixed << std::setprecision(3);
	ss << (int) (1.0 / g_dDeltaTime) << "fps";
	c.X = g_Console.getConsoleSize().X - 5;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str());
	*/

	// displays the elapsed time
	ss.str("");
	ss << g_dElapsedTime << "secs";
	c.X = 0;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 0x0F);
}
void renderToScreen()
{
	// Writes the buffer to the console, hence you will see what you have written
	g_Console.flushBufferToConsole();
}
void TrapFlame()
{
	// Set up sample colours, and output shadings
	const WORD colors[] = {
		0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};
	COORD c;
	//Trap - Flame Geyser
	if (!setTimeTrap)
	{
		timer = g_dElapsedTime;
		setTimeTrap = true;
	}
	for (int i = 0; i < 5; ++i)
	{
		c.X = 4 * i;
		c.Y = 10;
		if (g_dElapsedTime < timer + 3)
		{
			fireset = true;
			g_Console.writeToBuffer(c, "²²²²", colors[2]); // Flame ON
		}
		else
		{
			fireset = false;
			g_Console.writeToBuffer(c, "²²²²", colors[0]); // Flame OFF
		}
	}

	if (g_dElapsedTime > timer + 8)
	{
		setTimeTrap = false;
	}
}
void TrapPoison()
{
	// Set up sample colours, and output shadings
	const WORD colors[] = {
		0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};

	COORD c;
	//Trap - Poison Mist
	for (int i = 0; i < 5; ++i)
	{
		c.X = 4 * i;
		c.Y = 15;
		g_Console.writeToBuffer(c, "²²²²", colors[3]);
		for (int j = 1; j <= 5; j++)
		{
			c.Y += 1;
			g_Console.writeToBuffer(c, "²²²²", colors[3]);
		}
	}
}
void TrapSpike()
{
	// Set up sample colours, and output shadings
	const WORD colors[] = {
		0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};

	COORD c;
	//Trap - Spike
	for (int i = 0; i < 2; ++i)
	{
		c.X = 4 * i;
		c.Y = 5;
		g_Console.writeToBuffer(c, "²²²²", colors[5]);
		for (int j = 1; j <= 2; j++)
		{
			c.Y += 1;
			g_Console.writeToBuffer(c, "²²²²", colors[5]);
		}
	}
}

void renderTutorial()
{
	COORD c = g_Console.getConsoleSize();
	c.Y = 3;

	c.X = g_Console.getConsoleSize().X / 2 - 32;

	string line;
	ifstream myfile("tutorial.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			c.Y += 1;
			g_Console.writeToBuffer(c, line, 0x03);
		}
		myfile.close();
	}
    processUserInput();
}
void renderStory()
{
    COORD c = g_Console.getConsoleSize();
    c.Y = 1;
    c.X = g_Console.getConsoleSize().X;

    string line;
    ifstream myfile("story.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            c.Y += 1;
            g_Console.writeToBuffer(c, line, 0x03);
        }
        myfile.close();
    }
    processUserInput();
}
/*void map()
{
COORD c = g_Console.getConsoleSize();
string mapvar[] = { "i", "j", "k" };

string line;
ifstream myfile("menu.txt");
if (myfile.is_open())
{
while (getline(myfile, line))
{
c.Y += 1;
g_Console.writeToBuffer(c, line, 0x03);

/*if (line == mapvar[0])
{
g_Console.writeToBuffer(c, "Û", 0xFF);
}
}
myfile.close();
}
}*/


void PlayerState(){
	//fire deducts life, if lives == 0 spawn back at map start. Requires timing 
	//Spikes deducts life and spawn back to map starting spawn.
	//poison reverse controls.
	//fireX.push_back(26);
	//fireY.push_back(3);
	//poisonX.push_back(24);
	//poisonY.push_back(26);
	//spikeX.push_back(13);
	//spikeY.push_back(11);

	//Checking player's coordinate with fire's coordinate
	for (unsigned int i = 0; i < fireX.size(); i++){
		if ((g_sChar.m_cLocation.X == fireX[i]) && (g_sChar.m_cLocation.Y == fireY[i])){
			if (fireset == true){
				lives--;
                lostlive = true;
				if (lives == 0){
					//g_ePlayerState = P_DEAD;
				}
				g_ePlayerState = P_ALIVE;
				g_sChar.m_cLocation.X = 1;
				g_sChar.m_cLocation.Y = 4;

			}

		}
	}




	//Checking player's coordinate with spike's coordinate
	for (int i = 0; i < spikeX.size(); i++){
		for (int u = 0; u < spikeY.size(); u++){
			if ((g_sChar.m_cLocation.X == spikeX[i]) && (g_sChar.m_cLocation.Y == spikeY[u])){
				lives--;
				g_ePlayerState = P_ALIVE;
				g_sChar.m_cLocation.X = 1;  //Value == to spawn location at X
				g_sChar.m_cLocation.Y = 4;  //Value == to spawn location at Y
				if (lives == 0){
					g_ePlayerState = P_DEAD;
				}
				break;
			}
		}
	}

	//Checking player's coordinate and poison's coordinate
	for (unsigned int i = 0; i < poisonX.size(); i++){
		for (int u = 0; u < poisonY.size(); u++){
			if ((g_sChar.m_cLocation.X == poisonX[i]) && (g_sChar.m_cLocation.Y == poisonY[u])){
				g_ePlayerState = P_POISONED;
				break;
			}
		}
	}
}


void PlayerFire()
{
	fireX.push_back(26);
	fireX.push_back(26);
	fireX.push_back(26);
	fireX.push_back(26);
	fireX.push_back(26);
	fireY.push_back(3);
	fireY.push_back(4);
	fireY.push_back(5);
	fireY.push_back(6);
	fireY.push_back(7);


	fireX.push_back(9);
	fireX.push_back(10);
	fireX.push_back(11);
	fireX.push_back(12);
	fireX.push_back(13);
	fireX.push_back(14);
	fireX.push_back(15);
	fireX.push_back(16);
	fireX.push_back(17);
	fireX.push_back(18);
	fireX.push_back(19);
	fireX.push_back(20);
	fireX.push_back(21);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);
	fireY.push_back(19);

	fireX.push_back(22);
	fireX.push_back(22);
	fireX.push_back(22);
	fireX.push_back(22);
	fireX.push_back(22);
	fireX.push_back(22);
	fireY.push_back(10);
	fireY.push_back(11);
	fireY.push_back(12);
	fireY.push_back(13);
	fireY.push_back(14);
	fireY.push_back(15);

	//Checking player's coordinate with fire's coordinate
	for (unsigned int i = 0; i < fireX.size(); i++){
		if ((g_sChar.m_cLocation.X == fireX[i]) && (g_sChar.m_cLocation.Y == fireY[i]))
			fireset = true;
		{
			if (fireset == true){
				lives--;
                lostlive = true;
				g_ePlayerState = P_ALIVE;
				g_sChar.m_cLocation.X = 1;
				g_sChar.m_cLocation.Y = 4;
				if (lives == 0){
					//g_ePlayerState = P_DEAD;
				}

				fireset = false;

			}

		}
	}
}

void PlayerSpike()
{

	spikeX.push_back(13);
	spikeY.push_back(11);


	//Checking player's coordinate with spike's coordinate
	for (int i = 0; i < spikeX.size(); i++){
		for (int u = 0; u < spikeY.size(); u++){
			if ((g_sChar.m_cLocation.X == spikeX[i]) && (g_sChar.m_cLocation.Y == spikeY[u])){
				lives--;
				g_ePlayerState = P_ALIVE;
				g_sChar.m_cLocation.X = 1;  //Value == to spawn location at X
				g_sChar.m_cLocation.Y = 4;  //Value == to spawn location at Y
				if (lives == 0){
					g_ePlayerState = P_DEAD;
				}
				break;
			}
		}
	}

}

Wall MakeWall(int CoordX, int CoordY)
{
	Wall Wall1;

	Wall1.w_location.X = CoordX;
	Wall1.w_location.Y = CoordY;

	return Wall1;
}

void stillPoisoned(){
	if (getAntiPoisonPill == true){
		g_ePlayerState = P_ALIVE;
	}
}