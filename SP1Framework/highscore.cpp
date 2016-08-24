#include "highscore.h"


string score = "7000";
string highscore = "";
int itempoints = 100;
int lifelostpoints = 500;
int treasurepoint = 2000;
bool opentreasure = false;
bool tookitem = false;
//int lives = 3;    //game.cpp have this
bool lostlive = false;

void calculate()
{
    int c_score = stoi(score);
    if (tookitem == true)
    {
        c_score += itempoints;
        tookitem = false; //set it back to false to prevent looping
    }
    if (lostlive == true)
    {
        if (c_score >= lifelostpoints)
        {
            c_score -= lifelostpoints;
        }
        else
        {
            c_score -= c_score;
        }
        lostlive = false;
    }
    if (opentreasure == true)
    {
        c_score += treasurepoint;
        opentreasure = false;
    }
    score = to_string(c_score);
}
void highscoreboard()
{
    COORD c = g_Console.getConsoleSize();
    
    string line;
    ifstream myfile("highscore.txt");
    if (myfile.is_open())
    {
        getline(myfile, line);
        highscore = line;

        c.X = g_Console.getConsoleSize().X / 2;
        c.Y = (g_Console.getConsoleSize().Y / 2);

        g_Console.writeToBuffer(c, "Previous Highest Score : ", 0x03);
        c.Y += 1;
        g_Console.writeToBuffer(c, line, 0x03);
        c.Y += 1;
        g_Console.writeToBuffer(c, "Your Score : ", 0x03);
        c.Y += 1;
        g_Console.writeToBuffer(c, score, 0x03);

        int playerScore = stoi(score);
        int currenthighscore = stoi(highscore);
        
        if (playerScore > currenthighscore) //new highscore
        {
            c.Y += 1;
            g_Console.writeToBuffer(c, "New High Score", 0x03);
        }
        myfile.close();
    }
}
void comparescore()
{
    COORD c = g_Console.getConsoleSize();
    c.X = g_Console.getConsoleSize().X / 2;
    c.Y = (g_Console.getConsoleSize().Y / 2) + 4;
        int _score = stoi(score);
        int _highscore = stoi(highscore);

        if (_score > _highscore) //new highscore
        {
            _highscore = _score;
            
            score = to_string(_score);
            highscore = to_string(_highscore);
            ofstream myFile("highscore.txt");
            myFile << highscore;       //record highscore into text file
            myFile.close();
        }
}