#pragma once
#include <graphics.h>
#include <iostream>
#include "filehandling.cpp"
using namespace std;

// screen resolution
#define WIDTH 1280
#define HEIGHT 720

// draw text at x,y (depending on alignment)
void drawText(int x, int y, string text, int color = WHITE, int midx = 1, int midy = 1)
{
    // midx = 1 (x in middle), midy (y in middle) of text
    int w = textwidth((char *)text.c_str());  // width of text
    int h = textheight((char *)text.c_str()); // height of text
    if (midx)
    {
        x -= w / 2;
    }
    if (midy)
    {
        y -= h / 2;
    }
    setcolor(color);                       // set color of text
    outtextxy(x, y, (char *)text.c_str()); // draw text from top-left
    setcolor(WHITE);                       // reset color
}

// general menu template
int menu(string heading, string options[], int size, int color, int start_index = 0)
{
    initwindow(WIDTH, HEIGHT, "Brick-Breaker Game", (getmaxwidth() - WIDTH) / 2, (getmaxheight() - HEIGHT) / 2, true);
    int option_gap;          // gap b/w options
    int index = start_index; // option index initially marked
    int x = getmaxx() / 2;   // x-coordinate of text (centered)
    int y;                   // varies with text
    // set font, direction, charsize of text
    settextstyle(6, 0, 0);
    setusercharsize(3, 2, 2, 1);
    do
    {
        swapbuffers();
        delay(100);
        cleardevice();

        y = 100; // heading starts at
        drawText(x, y, heading, color);

        // use up-down arrow to cycle menu
        if (GetKeyState(VK_UP) & 0x8000)
        {
            if (index != start_index)
            {
                index--;
            }
        }
        else if (GetKeyState(VK_DOWN) & 0x8000)
        {
            if (index != size - 1)
            {
                index++;
            }
        }
        // draw options
        y = 150;                                // 1st option top
        option_gap = (HEIGHT - y) / (size + 1); // even gap b/w options
        for (int i = start_index; i < size; i++)
        {
            y += option_gap;
            if (i != index)
            {
                drawText(x, y, options[i]);
            }
            // highlighted option (selected)
            else
            {
                setbkcolor(LIGHTGRAY);
                drawText(x, y, options[i], BLACK);
                setbkcolor(BLACK);
            }
        }
        // hit enter to select option and break loop
    } while (!(GetKeyState(VK_RETURN) & 0x8000));
    closegraph();
    return index;
}

// create/load userprofile
bool myProfile(string &username, int index)
{
    initwindow(WIDTH, HEIGHT, "Brick-Breaker Game", (getmaxwidth() - WIDTH) / 2, (getmaxheight() - HEIGHT) / 2);
    string title;          // menu title
    int max_length = 15;   // Max username length
    int x = getmaxx() / 2; // Text centered
    bool found = false;
    if (index == 0)
    {
        title = "C R E A T E = M Y = P R O F I L E";
    }
    else
    {
        title = "L O A D = P R O F I L E";
    }
    // set font, direction, charsize of text
    settextstyle(3, 0, 0);
    setusercharsize(1, 2, 1, 1);
    // hit escape to break loop
    while (!(GetKeyState(VK_ESCAPE) & 0x8000))
    {
        drawText(x, 100, title, LIGHTRED);
        drawText(x, 200, "* MAX " + to_string(max_length) + " Char    * BKSPACE=Clear    * ENTER=Confirm    * ESC=Back", LIGHTBLUE);
        drawText(x, 300, "Enter Username: " + username + "_");

        char c = getch();
        //  Only alpha-numeric characters
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
        {
            if (username.length() < max_length)
            {
                username += c;
            }
        }
        // backspace
        else if (c == 8)
        {
            if (username.length() > 0)
            {
                username = username.substr(0, username.length() - 1);
            }
        }
        // Pressed Enter and username not empty
        else if (c == 13 && username.length() > 0)
        {
            // index = 0 (Create Profile), index = 1 (Load Profile)
            if (index == 0)
            {
                // username not exists
                if (!findName(username))
                {
                    drawText(x, 400, "> > >  LOADING  NEW  PROFILE  < < <", LIGHTGREEN);
                    newPlayer(username);
                    delay(3000);
                    closegraph();
                    return true;
                }
                else
                {
                    drawText(x, 400, "!!!  FOUND : TRY  AGAIN  !!!", RED);
                    getch();
                }
            }
            else
            {
                // username exists
                if (findName(username))
                {
                    drawText(x, 400, "> > >  LOADING  PROFILE  < < <", LIGHTGREEN);
                    delay(3000);
                    closegraph();
                    return true;
                }
                else
                {
                    drawText(x, 400, "!!!  PROFILE  NOT  FOUND  !!!", RED);
                    getch();
                }
            }
        }
        delay(100);
        cleardevice();
    }
    closegraph();
    return false;
}

// sorting scores in descending order
void sortScores(string data[][2], int size)
{
    string temp_username, temp_score;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (stoi(data[j][1]) < stoi(data[j + 1][1]))
            {
                temp_username = data[j][0];
                temp_score = data[j][1];

                data[j][0] = data[j + 1][0];
                data[j][1] = data[j + 1][1];

                data[j + 1][0] = temp_username;
                data[j + 1][1] = temp_score;
            }
        }
    }
}

// display highscores
void viewHighScores()
{
    initwindow(WIDTH, HEIGHT, "Brick-Breaker Game", (getmaxwidth() - WIDTH) / 2, (getmaxheight() - HEIGHT) / 2);
    string scores[100][2];             // {{"username", "user_score"},{}..}
    int size = getScores(scores, 100); // occupied size
    sortScores(scores, size);          // scores sorted

    settextstyle(6, 0, 0);
    setusercharsize(3, 2, 2, 1);
    drawText(WIDTH / 2, 50, "L E A D E R B O A R D || T O P  1 0", BROWN);

    int y = 50, gap = (HEIGHT - 2 * y) / (size + 1);
    for (int i = 0; i < size; i++)
    {
        y += gap;
        drawText(WIDTH / 2, y, to_string(i + 1) + ".  " + scores[i][0] + "  " + scores[i][1], LIGHTGRAY);
    }
    drawText(WIDTH / 2, HEIGHT - 50, "Esc = Back", BROWN);

    // hit escape to break loop
    while (!(GetKeyState(VK_ESCAPE) & 0x8000))
    {
        continue;
    }
}

// show instructions
void howToPlay()
{
    initwindow(WIDTH, HEIGHT, "Brick-Breaker Game", (getmaxwidth() - WIDTH) / 2, (getmaxheight() - HEIGHT) / 2);
    string help[20];              // instructions
    int size = getHelp(help, 20); // total lines in instructions

    settextstyle(6, 0, 0);
    setusercharsize(3, 2, 2, 1);
    drawText(WIDTH / 2, 50, "|| I N S T R U C T I O N S ||", BROWN);

    int y = 50, gap = (HEIGHT - 2 * y) / (size + 1);
    setusercharsize(1, 1, 3, 2);
    for (int i = 0; i < size; i++)
    {
        y += gap;
        drawText(50, y, to_string(i+1) + ". " + help[i], LIGHTGRAY, 0, 1);
    }
    drawText(WIDTH / 2, HEIGHT - 50, "Esc = Back", BROWN);

    // hit escape to break loop
    while (!(GetKeyState(VK_ESCAPE) & 0x8000))
    {
        continue;
    }
}