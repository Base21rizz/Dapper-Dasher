#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

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

    // 1st Nebula data
    AnimData nebData{
        {0.0, 0.0, nebula.width / 8, nebula.height / 8}, // Rectangle rec
        {windowWidth, windowHeight - nebula.height / 8}, // Vector2 Pos
        0,                                               // int frame
        1.0 / 12.0,                                      // float updateTime
        0                                                // float runningTime
    };
    // 2nd Nebula Data
    AnimData neb2Data{
        {0.0, 0.0, nebula.width / 8, nebula.height / 8},       // Rectangle rec
        {windowWidth + 300, windowHeight - nebula.height / 8}, // Vector2 Pos
        0,                                                     // int frame
        1.0 / 16.0,                                            // float updateTime
        0                                                      // float runningTime
    };

    // Nebula X velocity (Pixels/ Sec)
    int nebVel{-200};

    // Scarfy Variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = (windowWidth / 2) - (scarfyData.rec.width / 2);
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    /* Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = (windowWidth / 2) - (scarfyRec.width / 2);
    scarfyPos.y = windowHeight - scarfyRec.height; */

    /*     // Scarfy Animation
        int frame{};
        // Amount of time before we update the animation frame
        const float updateTime{1.0 / 12.0};
        float runningTime{}; */

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
        if (scarfyData.pos.y >= windowHeight - scarfyData.rec.height)
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
        nebData.pos.x += nebVel * dT;
        // Update 2nd Nebula Position
        neb2Data.pos.x += nebVel * dT;

        // Update Scarfy Position
        scarfyData.pos.y += velocity * dT;

        // Update Animation frame for Nebula
        nebData.runningTime += dT;
        if (nebData.runningTime >= nebData.updateTime)
        {
            nebData.runningTime = 0;
            // update animation frame
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            if (nebData.frame > 7)
            {
                nebData.frame = 0;
            }
        }

        neb2Data.runningTime += dT;
        if (neb2Data.runningTime >= neb2Data.updateTime)
        {
            neb2Data.runningTime = 0;
            // update animation frame
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
            if (neb2Data.frame > 7)
            {
                neb2Data.frame = 0;
            }
        }

        // Update Animation frame for Scarfy
        scarfyData.runningTime += dT;
        if (scarfyData.runningTime >= scarfyData.updateTime && !isInAir) // Slightly different from the tutorial but is better
        {
            scarfyData.runningTime = 0;
            // update animation frame
            scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
            scarfyData.frame++;
            if (scarfyData.frame > 5)
            {
                scarfyData.frame = 0;
            }
        }

        // Draw Nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
        // Draw Nebula 2
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // Game Logic End
        // End Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}