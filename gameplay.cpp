#pragma once
#include <graphics.h>
#include "filehandling.cpp"
#include "menus.cpp"
using namespace std;

// screen resolution
#define WIDTH 1280
#define HEIGHT 720

// ball hitting tile
bool detectCollision(int ball[], int radius, int tiles[][6], int total_tiles, int &tiles_left)
{
    if (tiles_left > 0)
    {
        for (int i = 0; i < total_tiles; i++)
        {
            // if tile not hit (rendered)
            if (tiles[i][4])
            {
                // within x1,x2 of tile
                if (ball[0] > (tiles[i][0] - radius) && ball[0] < (tiles[i][2] + radius))
                {
                    // within y1,y2 of tile
                    if (ball[1] > (tiles[i][1] - radius) && ball[1] < (tiles[i][3] + radius))
                    {
                        // hits (upper or lower side) + corners of tile
                        if (ball[1] > tiles[i][1] || ball[1] < tiles[i][3])
                        {
                            ball[3] *= -1;
                        }
                        // hits left or right side of tile
                        else
                        {
                            ball[2] *= -1;
                        }
                        tiles[i][4] = 0;
                        tiles_left--;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// change ball movement
void ballMove(int ball[], int radius, int vel, int barr[], int top)
{
    // hits right or left side of window
    if (ball[0] < radius || ball[0] > WIDTH - radius)
    {
        ball[2] *= -1;
    }
    // hits top-side
    if (ball[1] < top + radius)
    {
        ball[3] *= -1;
    }
    // hits the bar
    else if ((ball[1] >= barr[1] - radius) && (ball[0] >= barr[0] - radius && ball[0] <= barr[2] + radius))
    {
        // special collision
        int mid_point = barr[0] + (barr[2] - barr[0]) / 2;
        // ball hits 2nd half of bar
        if (ball[0] > mid_point)
        {
            // going left
            if (ball[2] < 0)
            {
                ball[2] *= -1;
            }
        }
        // ball hits 1st half of bar
        else
        {
            // going right
            if (ball[2] > 0)
            {
                ball[2] *= -1;
            }
        }
        ball[3] *= -1;
    }
    ball[0] += (ball[2] * vel);
    ball[1] += (ball[3] * vel);
}

// using mouse x-coordinates to change bar location horizontally
void barMove(int barr[], int bar_width)
{
    // mouse inside window in start
    if (mousex() > 0)
    {
        if (mousex() < bar_width / 2)
        {
            barr[0] = 0;
            barr[2] = bar_width;
        }
        else if (mousex() > WIDTH - bar_width / 2)
        {
            barr[0] = WIDTH - bar_width;
            barr[2] = WIDTH;
        }
        else
        {
            barr[0] = mousex() - bar_width / 2;
            barr[2] = mousex() + bar_width / 2;
        }
    }
}

// display current score, level, remaining extra lives
void headsUpDisplay(string username, int score, int lives)
{
    int lives_radius = 20;
    int x = WIDTH - (lives_radius * 2), y = lives_radius + 10;

    drawText(0, y, username, LIGHTGRAY, 0);
    drawText(WIDTH / 2, 0, to_string(score), LIGHTGRAY, 1, 0);

    setcolor(WHITE);
    for (int i = 0; i < lives; i++)
    {
        setfillstyle(INTERLEAVE_FILL, WHITE);
        circle(x, y, lives_radius); // position icons
        floodfill(x, y, WHITE);
        x -= (lives_radius)*3;
    }
    y += y;
    setfillstyle(SOLID_FILL, RED);
    bar(0, y, WIDTH, y + 10); // top borderline
}

// Random Level Generator
int setTiles(int tiles[][6])
{
    int tile_num = 0, rows = rand() % 5 + 2; // random number of rows
    int tile_spacing = 5, max_width = (WIDTH / 10) - tile_spacing;
    int tile_width = 0, tile_height = 50;
    int x = 0, y = HEIGHT / 5; // starting position

    for (int i = 0; i < rows; i++)
    {
        // space for atleast 1/4 tile
        while (WIDTH - x >= max_width / 4)
        {
            tile_width = max_width / (rand() % 2 + 1); // either half or full tile
            // top left corner
            tiles[tile_num][0] = x; // x1
            tiles[tile_num][1] = y; // y1
            // bottom right corner
            tiles[tile_num][2] = x + tile_width;  // x2
            tiles[tile_num][3] = y + tile_height; // y2
            tiles[tile_num][4] = 1;               // render flag
            tiles[tile_num][5] = rand() % 13 + 2; // random tile color
            x += (tile_width + tile_spacing);
            tile_num++;
        }
        x = 0;
        y += (tile_height + tile_spacing);
    }
    return tile_num;
}

// Draw tiles on graphics window
void drawTiles(const int tiles[][6], int total_tiles)
{
    for (int i = 0; i < total_tiles; i++)
    {
        if (tiles[i][4])
        {
            setfillstyle(SOLID_FILL, tiles[i][5]);                   // tile color
            bar(tiles[i][0], tiles[i][1], tiles[i][2], tiles[i][3]); // draw tile
        }
    }
}

// set game difficulty
void setDifficulty(int difficulty, int &vel, int &bar_width)
{
    // easy level
    if (difficulty == 0)
    {
        vel = 4;
        bar_width = 300;
    }
    // medium level
    else if (difficulty == 1)
    {
        vel = 7;
        bar_width = 180;
    }
    // hard level
    else if (difficulty == 2)
    {
        vel = 10;
        bar_width = 100;
    }
}

// initialize ball and bar
void initialize(int ball[], int radius, int barr[], int bar_width, int bar_height, int reset_ball = 1, int reset_barr = 1)
{
    // reset_barr = 1, reset bar variables
    if (reset_barr)
    {
        barr[0] = (WIDTH - bar_width) / 2;
        barr[1] = HEIGHT - bar_height;
        barr[2] = (WIDTH + bar_width) / 2;
        barr[3] = HEIGHT;
    }
    // reset_ball = 1, reset ball variables
    if (reset_ball)
    {
        ball[0] = barr[0] + bar_width / 2;
        ball[1] = HEIGHT - bar_height - (2 * radius);
        // ball direction
        ball[2] = 1;  // initially move right
        ball[3] = -1; // initially move up
    }
}

// returns true if level completed
bool gameLoop(string username, int new_game, int difficulty)
{
    bool play = false, move_bar = false; // Start game? Move the bar?
    int max_score = 0;                   // maximum score achieved
    int score = 0, lives;                // HUD info
    int top_border = 70;                 // top margin of play area
    int radius = 10;                     // radius of ball
    int bar_width, bar_height = 20;      // width, height of bar
    int vel;                             // velocity of ball
    int ball[4];                         // x, y (position), x, y(direction) of ball
    int barr[4];                         //(x1,y1), (x2,y2) of bar
    int tiles[1000][6];                  //(x1,y1), (x2,y2), render_flag, color of Tiles
    int total_tiles, tiles_left;         // total number of tiles and remaining tiles

    loadUser(username, max_score, score, lives, total_tiles, tiles_left, tiles);
    if (new_game)
    {
        score = 0;
        lives = 3;
        total_tiles = setTiles(tiles);
        tiles_left = total_tiles;
    }

    setDifficulty(difficulty, vel, bar_width);
    initialize(ball, radius, barr, bar_width, bar_height);

    initwindow(WIDTH, HEIGHT, "Brick-Breaker Game", (getmaxwidth() - WIDTH) / 2, (getmaxheight() - HEIGHT) / 2, true);
    settextstyle(3, 0, 0);
    setusercharsize(3, 1, 2, 1);

    // main gameLoop
    while (true)
    {
        swapbuffers();
        delay(1);
        cleardevice();

        headsUpDisplay(username, score, lives); // shows gameInfo
        drawTiles(tiles, total_tiles);          // draw tiles

        setfillstyle(SOLID_FILL, WHITE);    // set ball color
        circle(ball[0], ball[1], radius);   // draws ball
        floodfill(ball[0], ball[1], WHITE); // colors ball

        setfillstyle(INTERLEAVE_FILL, LIGHTCYAN); // set bar color
        bar(barr[0], barr[1], barr[2], barr[3]);  // draws bar

        //  Tiles cleared (next level)
        if (tiles_left == 0)
        {
            swapbuffers();
            // reset level
            total_tiles = setTiles(tiles);
            tiles_left = total_tiles;
            new_game = 0;
            if (score > max_score)
            {
                max_score = score;
            }
            saveUser(username, new_game, max_score, score, lives, total_tiles, tiles_left, tiles);
            delay(1500);
            return true;
        }
        //  Click to start/resume
        if (play)
        {
            ballMove(ball, radius, vel, barr, top_border); // moving the ball
            barMove(barr, bar_width);                      // moving the bar
        }
        else
        {
            drawText(WIDTH / 2, tiles[total_tiles - 1][3] + 20, "CLICK HERE TO PLAY!", LIGHTGREEN, 1, 0);
            swapbuffers();
            while (!ismouseclick(WM_LBUTTONDOWN))
            {
                continue;
            }
            play = true;
        }
        // ball falls below bar
        if (ball[1] > HEIGHT - radius)
        {
            // any extra lives
            if (lives > 0)
            {
                lives--;
                setDifficulty(difficulty, vel, bar_width);
                initialize(ball, radius, barr, bar_width, bar_height, 1, 0);
                delay(500);
            }
            // Game over
            else
            {
                drawText(WIDTH / 2, HEIGHT / 2, "!! G A M E  O V E R !!", RED);
                swapbuffers();
                delay(2000);
                new_game = 1;
                break;
            }
        }
        //  check when ball is near tiles
        else if (detectCollision(ball, radius, tiles, total_tiles, tiles_left))
        {
            score += 5;
            // increase ball speed
            if (score % 40 == 0)
            {
                vel++;
            }
        }
        // Hit Escape to Pause
        if ((GetKeyState(VK_ESCAPE) & 0x8000))
        {
            new_game = 0;
            break;
        }
    }
    if (score > max_score)
    {
        max_score = score;
    }
    saveUser(username, new_game, max_score, score, lives, total_tiles, tiles_left, tiles);

    closegraph();
    return false;
}