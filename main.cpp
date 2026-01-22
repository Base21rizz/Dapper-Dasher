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

    // Nebula Variable
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width / 8, nebula.height / 8};
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};

    Rectangle neb2Rec{0.0, 0.0, nebula.width / 8, nebula.height / 8};
    Vector2 neb2Pos{windowWidth + 300, windowHeight - nebRec.height};

    // Nebula Animation
    int nebFrame{};
    // Amount of time before we update the animation frame
    const float nebUpdateTime(1.0 / 12.0);
    float nebRunningTime{};

    int neb2Frame{};
    // Amount of time before we update the animation frame
    const float neb2UpdateTime(1.0 / 16.0);
    float neb2RunningTime{};

    // Nebula X velocity (Pixels/ Sec)
    int nebVel{-200};

    // Scarfy Variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = (windowWidth / 2) - (scarfyRec.width / 2);
    scarfyPos.y = windowHeight - scarfyRec.height;

    // Scarfy Animation
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

        // Update Nebula Position
        nebPos.x += nebVel * dT;
        // Update 2nd Nebula Position
        neb2Pos.x += nebVel * dT;

        // Update Scarfy Position
        scarfyPos.y += velocity * dT;

        // Update Animation frame for Nebula
        nebRunningTime += dT;
        if (nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0;
            // update animation frame
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if (nebFrame > 7)
            {
                nebFrame = 0;
            }
        }

        neb2RunningTime += dT;
        if (neb2RunningTime >= neb2UpdateTime)
        {
            neb2RunningTime = 0;
            // update animation frame
            neb2Rec.x = neb2Frame * neb2Rec.width;
            neb2Frame++;
            if (neb2Frame > 7)
            {
                neb2Frame = 0;
            }
        }

        // Update Animation frame for Scarfy
        runningTime += dT;
        if (runningTime >= updateTime && !isInAir) // Slightly different from the tutorial but is better
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

        // Draw Nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);
        // Draw Nebula 2
        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // Game Logic End
        // End Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}