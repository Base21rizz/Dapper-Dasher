#include "raylib.h"
int main()
{
    // Window Dimensions
    const int windowWidth{512};
    const int windowHeight{380};

    // Initialize Window
    InitWindow(windowWidth, windowHeight, "Dapper-Dasher");
    // Gravity (p/f)/f
    const int gravity{1};

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
        // Perform Ground Check
        if (posY >= windowHeight - heigth)
        {
            // Rectangle is on the ground
            velocity = 0;
        }
        else
        {
            // Rectangle is in the Air
            velocity += gravity;
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            velocity -= 10;
        }
        // Apply gravity

        // Update Position
        posY += velocity;

        DrawRectangle(windowWidth / 2, posY, width, heigth, BLUE);

        // Game Logic End
        // End Drawing
        EndDrawing();
    }
    CloseWindow();
}