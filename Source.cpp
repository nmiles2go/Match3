
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

// Background elements
Vector2 grid_origin; // We use this to calculate the offset
Texture2D background;

// UI
int score = 200;
Font character_font;
Font score_font;

// Gameplay Variables
Vector2 selected_tile = { -1.0f, -1.0f };

// Bools for some conditions
bool isTileHighlighted = false;

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
    character_font = LoadFontEx (
                                    "D:\\Match3\\assets\\super-adorable-font\\SuperAdorable-MAvyp.ttf",
                                    SCORE_FONT_SIZE, 
                                    NULL, 
                                    0
                                );
    score_font     = LoadFontEx (
                                    "D:\\Match3\\assets\\04b03-font\\04B03-XKP.ttf",
                                    SCORE_FONT_SIZE,
                                    NULL,
                                    0
                                );
    
    initialize_board();
    
    // Just before we start the game loop, we are creating a mouse position variable.
    Vector2 mouse = { 0.0f, 0.0f };
    
    while (!WindowShouldClose())
    {
        // ALL GAME LOGIC GOES HERE

        // Updating mouse location every loop
        mouse = GetMousePosition();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            

            int x = (mouse.x - grid_origin.x) / TILE_SIZE ;
            int y = (mouse.y - grid_origin.y) / TILE_SIZE ;

            if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
            {
                selected_tile = { (float)x, (float)y };
                
            }
        }

        BeginDrawing();

        ClearBackground(GRAY);
        
        Rectangle source = { 0,0, background.width, background.height }; // to pass to the DrawTexturePro Function
        Rectangle destination = { 0,0, GetScreenWidth(), GetScreenHeight() };
        
        DrawTexturePro(
                        background, 
                        source, 
                        destination, 
                        {0.0f,0.0f},
                        0.0f, 
                        WHITE
                      );




        
        
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
                DrawRectangleLinesEx(rect, 2.0f, Color{ 53, 38, 32, 255 });
                DrawTextEx(
                    character_font,
                    TextFormat("%c", board[y][x]),
                    textPos,
                    60, 1, Color{ 53, 38, 32, 255 }
                );

                
            }
        }
        

        
        // Drawing the selected tile

        if (isTileHighlighted ==false && selected_tile.x >= 0.0f)
        {
            isTileHighlighted = true;
            
            
            Rectangle selectedTileRectangle = { 
                                                grid_origin.x + (selected_tile.x * TILE_SIZE), 
                                                grid_origin.y + (selected_tile.y * TILE_SIZE),
                                                TILE_SIZE,
                                                TILE_SIZE
                                              };
            
            Vector2 textPos1 = { grid_origin.x + (selected_tile.x * TILE_SIZE) + 24,  grid_origin.y + (selected_tile.y * TILE_SIZE ) + 16};

            
           
            DrawTextEx(
                character_font,
                TextFormat("%c", board[(int)selected_tile.y][(int)selected_tile.x]),
                textPos1,
                60, 1, Color{ 91,124,153, 255 }
            );
            
            DrawRectangleLinesEx(selectedTileRectangle, 10.0f, RAYWHITE);
            DrawRectangleRec(selectedTileRectangle, Color{ 255, 255, 255, 25 });

            
        }

        else
        {
            ;
        }

        isTileHighlighted = !isTileHighlighted;

        DrawTextEx(
                    score_font,
                    TextFormat("Score: %d", score), 
                    { 590.0f, 30.0f }, 
                    SCORE_FONT_SIZE + 10, 
                    5.0f, 
                    WHITE
                  );

        
        EndDrawing();
    }

    UnloadFont(character_font);
    UnloadFont(score_font);
    UnloadTexture(background);

    CloseWindow();

    return 0;
}