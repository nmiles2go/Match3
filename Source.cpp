
#include "raylib.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define BOARD_SIZE 8
#define TILE_SIZE 84
#define TILE_TYPES 5
#define SCORE_FONT_SIZE 60

const char tile_chars[TILE_TYPES] = { '#','@','%','&','?' }; // types of our tiles. 
char board[BOARD_SIZE][BOARD_SIZE]; // Array for our board

Vector2 grid_origin; // We use this to calculate the offset
Texture2D background;

int score = 200;
Font score_font;

char random_tile()
{
    return tile_chars[rand() % TILE_TYPES];
}

void initialize_board()
{
    //    X X X X X X X X 
    //  Y # # # # # # # # 
    //  Y # # # # # # # # 
    //  Y # # # # # # # # 
    //  Y # # # # # # # # 
    //  Y # # # # # # # # 
    //  Y # # # # # # # # 
    //  Y # # # # # # # # 
    //  Y # # # # # # # # 


    // # are the characters on the board, while X and Y represent the 2 axis.

    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            board[y][x] = random_tile();
        }
    }

    int grid_width  = BOARD_SIZE * TILE_SIZE;
    int grid_height = BOARD_SIZE * TILE_SIZE;
    
    Vector2 grid{ (GetScreenWidth() - grid_width) / 2, (GetScreenHeight() - grid_height) / 2 };
    grid_origin = grid;
}


int main(void)
{
    const int SCREEN_WIDTH = 1600;
    const int SCREEN_HEIGHT= 900;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MATCH THE 3! 2D ASCII Game using Raylib");
    SetTargetFPS(60);
    srand(time(NULL));

    background = LoadTexture("D:\\Match3\\assets\\PlaceHolder_BackgroundForMatch3.png");
    score_font = LoadFontEx("D:\\Match3\\assets\\super-adorable-font\\SuperAdorable-MAvyp.ttf", SCORE_FONT_SIZE, NULL, 0);
    
    initialize_board();

    while (!WindowShouldClose())
    {
        // ALL GAME LOGIC GOES HERE

        BeginDrawing();

        ClearBackground(GRAY);
        Rectangle source = { 0,0, background.width, background.height }; // to pass to the DrawTexturePro Function
        Rectangle destination = { 0,0, GetScreenWidth(), GetScreenHeight() };
        DrawTexturePro(background, source, destination, {0.0f,0.0f}, 0.0f, WHITE);


        
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            for (int x = 0; x < BOARD_SIZE; x++)
            {
                Rectangle rect =
                {
                    grid_origin.x + (x * TILE_SIZE),
                    grid_origin.y + (y * TILE_SIZE),
                        TILE_SIZE,
                        TILE_SIZE
                };

                Vector2 textPos = { rect.x + 24, rect.y + 16 };
                DrawRectangleLinesEx(rect, 2.0f, Color{ 53, 38, 32, 255});
                DrawTextEx(
                    score_font,
                    TextFormat("%c", board[y][x]),
                    textPos,
                    60, 1, Color{ 53, 38, 32, 255 }
                    );
                
                    
                

            }
        }

        DrawTextEx(
            GetFontDefault(),
            TextFormat("Score: %d", score), 
            { 20.0f, 20.0f }, 
            SCORE_FONT_SIZE, 
            5.0f, 
            WHITE
        );

        
        EndDrawing();
    }

    UnloadFont(score_font);
    UnloadTexture(background);

    CloseWindow();

    return 0;
}