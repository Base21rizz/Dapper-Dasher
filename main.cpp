#include "raylib.h"
int main()
{
    // Window Dimensions
    const int windowWidth{512};
    const int windowHeight{380};

    // Initialize Window
    InitWindow(windowWidth, windowHeight, "Dapper-Dasher");

    // Rectangle Dimensions
    const int width{50};
    const int heigth{80};

    int posY{windowHeight - heigth};
    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Begin Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Game Logic Start
        if (IsKeyPressed(KEY_SPACE))
        {
            velocity -= 10;
        }
        posY += velocity;

        DrawRectangle(windowWidth / 2, posY, width, heigth, BLUE);

        // Game Logic End
        // End Drawing
        EndDrawing();
    }
    CloseWindow();
}