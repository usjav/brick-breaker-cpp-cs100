#pragma once
#include <fstream>
using namespace std;

// does user exist?
bool findName(string username)
{
    ifstream file(username + ".txt");
    if (file.is_open())
    {
        file.close();
        return true;
    }
    return false;
}

// is user currently playing?
int loadstate(string username)
{
    int new_game;
    ifstream fin(username + ".txt");
    fin >> new_game;
    fin.close();

    return new_game;
}

// save user gamedata (write to file)
void saveUser(string username, int new_game, int max_score, int score, int lives, int total_tiles, int tiles_left, int tiles[][6])
{
    ofstream myfile(username + ".txt");
    myfile << new_game << ' ';
    myfile << max_score << ' ';
    myfile << score << ' ';
    myfile << lives << ' ';
    myfile << total_tiles << ' ';
    myfile << tiles_left;
    for (int x = 0; x < total_tiles; x++)
    {
        myfile << endl;
        for (int y = 0; y < 6; y++)
        {
            myfile << tiles[x][y] << ' ';
        }
    }
}

// load user gamedata (read from file)
void loadUser(string username, int &max_score, int &score, int &lives, int &total_tiles, int &tiles_left, int tiles[][6])
{
    ifstream myfile(username + ".txt");
    int temp;
    myfile >> temp >> max_score >> score >> lives >> total_tiles >> tiles_left;
    for (int x = 0; x < total_tiles; x++)
    {
        for (int y = 0; y < 6; y++)
        {
            myfile >> tiles[x][y];
        }
    }
}

// newplayer profile (newgame=1, score=0)
void newPlayer(string username)
{
    ofstream file1(username + ".txt");        // create new user file
    ofstream file2("profiles.txt", ios::app); // add new user

    file1 << 1 << ' ' << 0 << ' ' << 0 << ' ' << 0 << ' ' << 0 << ' ' << 0;    // newgame_state and max_score
    file2 << username << endl; // username

    file1.close();
    file2.close();
}

// read user scores
int getScores(string data[][2], int rows)
{
    ifstream fin1("profiles.txt");
    int size = 0, temp;
    string username, max_score;
    // read till end of file
    while (fin1 >> username)
    {
        ifstream fin2(username + ".txt");
        fin2 >> temp >> max_score;
        // stoi(string) returns int
        // max_score=0, no score recorded (skip)
        if (stoi(max_score) > 0)
        {
            data[size][0] = username;
            data[size][1] = max_score;
            size++;
        }
        fin2.close();
    }
    fin1.close();
    return size;
}

// read instructions
int getHelp(string data[], int rows)
{
    ifstream fin("help.txt");
    int size = 0;
    // read till end of file
    while (getline(fin, data[size]))
    {
        size++;
    }
    fin.close();
    return size;
}