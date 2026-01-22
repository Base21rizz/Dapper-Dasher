#include "raylib.h"
int main()
{
    // Window Dimensions
    const int windowWidth{512};
    const int windowHeight{380};

    // Initialize Window
    InitWindow(windowWidth, windowHeight, "Dapper-Dasher");
    // Gravity (pixels / sec ) / sec
    const int gravity{1'000};

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

    // Animation Frame
    int frame{};
    // Amount of time before we update the animation frame
    const float updateTime{1.0 / 12.0};
    float runningTime{};

    // Is Rectangle in air
    bool isInAir{false};

    // Jump Velocity (pixels / sec)
    const int jumpVel{-600};

    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Begin Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Delta time (time since last frame)
        const float dT = GetFrameTime();

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
            velocity += gravity * dT;
        }

        // Jump Check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // Update Position
        scarfyPos.y += velocity * dT;

        // Update running time
        runningTime += dT;
        if (runningTime >= updateTime)
        {
            runningTime = 0;
            // update animation frame
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if (frame > 5)
            {
                frame = 0;
            }
        }

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // Game Logic End
        // End Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}