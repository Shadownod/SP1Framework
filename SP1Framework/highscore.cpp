#include "highscore.h"


string score = "";
string highscore = "";
int itempoints = 100;
int lifelostpoints = 500;
int treasurepoint = 2000;
bool opentreasure = false;
bool tookitem = false;
bool lostlive = false;
int highscore_container[5];
int lowest_number = 0;
int high1 = 0;
int high2 = 0;
int high3 = 0;
int high4 = 0;
int high5 = 0;

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
    ifstream myFIle("gameover.txt");
    if (myFIle.is_open())
    {
        c.X = (g_Console.getConsoleSize().X / 3)-20;
        c.Y = 1;
        while (getline(myFIle, line))
        {
            c.Y += 1;
            g_Console.writeToBuffer(c, line, 0x03);
        }
        myFIle.close();
    }
    ifstream myfile("highscore.txt");
    if (myfile.is_open())
    {
        c.X = (g_Console.getConsoleSize().X / 3) + 15;
        c.Y = (g_Console.getConsoleSize().Y / 3);
        int i = 0;
        while (getline(myfile, line))
        {
            int i_line = stoi(line);
            highscore_container[i] = i_line;
            i++;
        }
        myfile.close();

        //Sorts out highscore
        comparescore();

        //Prints out sorted out highscore
        g_Console.writeToBuffer(c, "High Scores", 0x03);
        c.X += 3;
        c.Y += 1;
        for (int j = 0; j < 5; j++)
        {
            c.Y++;
            g_Console.writeToBuffer(c, to_string(highscore_container[j]), 0x03);
        }
        //Checks and update highscore if needed
        int _score = stoi(score);
        if (_score > highscore_container[4] && highscoreset == false) //new highscore
        {
            swap(_score, highscore_container[4]);
            highscoreset = true;
        }
        //Writes in highscore from sorted out array
        fstream myFile("highscore.txt");
        for (int h = 0; h < 5;)
        {
            myFile << highscore_container[h] << "\n";       //record highscore in multiple lines
            h++;
        }
        myFile.close();
        //Prints out remaining contents
        c.X -= 16;
        c.Y += 2;
        g_Console.writeToBuffer(c, "Your current score:", 0x03);
        c.X += 20;
        g_Console.writeToBuffer(c, score, 0x03);
        c.X -= 20;
        c.Y += 2;
        g_Console.writeToBuffer(c, "Press 'backspace' to return to menu.", 0x03);
        c.Y += 1;
        g_Console.writeToBuffer(c, "Press 'esc' to quit game.", 0x03);
    }
}
void comparescore()
{   //Sorting out the highscores
    while ((highscore_container[0] < highscore_container[1]) ||
        (highscore_container[1] < highscore_container[2]) ||
        (highscore_container[2] < highscore_container[3]) ||
        (highscore_container[3] < highscore_container[4]))
    {
        int highscore_container_size = (sizeof(highscore_container) / sizeof(highscore_container[0]));
        for (int a = 0; a < highscore_container_size; a++)
        {
            if (highscore_container[a] < highscore_container[a + 1]) //checks 1st with 2nd,then 2nd with 3rd,and so on
            {//if smaller,swap the two
                swap(highscore_container[a], highscore_container[a + 1]);
            }
        }
    }
}