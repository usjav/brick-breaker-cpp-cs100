#include <graphics.h>
#include "filehandling.cpp"
#include "menus.cpp"
#include "gameplay.cpp"
using namespace std;

int main()
{
    string username;
    string menu1[] = {" Create New Profile ", " Load Profile ", " Quit "};
    string menu2[] = {" Resume Game ", " Start New Game ", " How To Play ", " Choose Difficulty ", " View HighScores ", " Return To Profile Menu ", " Quit Game "};
    string menu3[] = {" Continue To Next Level ", " Return To Main Menu ", " Quit Game "};
    string menu4[] = {" Easy ", " Medium ", " Hard ", " Go Back "};
    int choice, new_game, difficulty;
    bool game_on = true;

    while (game_on)
    {
        username = "";
        difficulty = 0; // default easy
        choice = menu("B R I C K || B R E A K E R", menu1, 3, RED);
        if (choice == 0 || choice == 1)
        {
            if (myProfile(username, choice))
            {
                while (game_on)
                {
                    new_game = loadstate(username);
                    if (new_game)
                    {
                        // show newgame option
                        choice = menu("M A I N || M E N U", menu2, 7, RED, 1);
                    }
                    else
                    {
                        // show resume + newgame option
                        choice = menu("M A I N || M E N U", menu2, 7, RED);
                    }
                    if (choice == 0 || choice == 1)
                    {
                        // Start new game
                        if (choice == 1)
                        {
                            new_game = 1;
                        }
                        while (gameLoop(username, new_game, difficulty))
                        {
                            // New random level
                            choice = menu("!! L E V E L  C L E A R E D !!", menu3, 3, LIGHTGREEN);
                            if (choice == 1)
                            {
                                break;
                            }
                            else if (choice == 2)
                            {
                                game_on = false;
                                break;
                            }
                        }
                    }
                    // instructions
                    else if (choice == 2)
                    {
                        howToPlay();
                    }
                    // change in-game difficulty
                    else if (choice == 3)
                    {
                        // Difficulty menu
                        choice = menu(" S E T || D I F F I C U L T Y  ( " + menu4[difficulty] + " )", menu4, 4, BROWN);
                        if (choice < 3)
                        {
                            difficulty = choice;
                        }
                    }
                    // view highscores of all players
                    else if (choice == 4)
                    {
                        viewHighScores();
                    }
                    else if (choice == 5)
                    {
                        break;
                    }
                    else
                    {
                        game_on = false;
                    }
                }
            }
        }
        else
        {
            game_on = false;
        }
    }
    return 0;
}