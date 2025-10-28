
#include "raylib.h"

int main(void)
{
    InitWindow(800, 450, "MATCH THE 3!");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(ORANGE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}