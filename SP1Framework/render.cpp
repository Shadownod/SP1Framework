#include "render.h"

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
	case S_HIGHSCORE: highscoreboard();
		break;
	}
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
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
	//processUserInput(); //allow user to quit game
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
	//processUserInput(); //allow user to quit game
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

	if (g_abKeyPressed[K_BACKSPACE])
	{
		g_eGameState = S_MENU;
	}
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
	if (g_abKeyPressed[K_BACKSPACE])
	{
		g_eGameState = S_MENU;
	}
}
