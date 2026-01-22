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

    // Textures Scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = (windowWidth / 2) - (scarfyRec.width / 2);
    scarfyPos.y = windowHeight - scarfyRec.height;

    // Is Rectangle in air
    bool isInAir{false};

    // Jump Velocity
    const int jumpVel{-22};

    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Begin Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Game Logic Start
        // Perform Ground Check
        if (scarfyPos.y >= windowHeight - scarfyRec.height)
        {
            // Rectangle is on the ground
            isInAir = false;
            velocity = 0;
        }
        else
        {
            // Rectangle is in the Air
            isInAir = true;
            velocity += gravity;
        }

        // Jump Check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }
        // Apply gravity

        // Update Position
        scarfyPos.y += velocity;

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // Game Logic End
        // End Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}