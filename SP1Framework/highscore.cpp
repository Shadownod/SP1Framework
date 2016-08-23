#include "highscore.h"


string score = "10";
string highscore = "0";
bool opentreasure = false;
bool tookitem = false;
//int lives = 3;    //game.cpp have this
bool lostlive = false;

void calculate()
{
    if (tookitem == true)
    {
        
        tookitem = false; //set it back to false to prevent looping
    }
    if (lostlive == true)
    {
        score -= 500;
        lostlive = false;
    }
    if (opentreasure == true)
    {
        score += 2000;
        opentreasure = false;
    }
}
void highscoreboard()
{
    COORD c = g_Console.getConsoleSize();
    
    string line;
    ifstream myFile("highscore.txt");
    //myfile.open("highscore.txt");
    if (myFile.is_open())
    {
        //while (getline(myfile, line))
        //{
           // c.Y += 1;
        //}
        getline(myFile, line);
        g_Console.writeToBuffer(c, "Highest Score : ", 0x03);
        g_Console.writeToBuffer(c, line, 0x03);
        g_Console.writeToBuffer(c, "Your Score : ", 0x03);
        g_Console.writeToBuffer(c, score, 0x03);

        highscore = line;

        ofstream myfile;
        myfile.open("highscore.txt");
        if (score > highscore)
        {
            highscore = score;
            myfile << highscore;        //writing highscore into text file
        }
        myFile.close();
    }
}