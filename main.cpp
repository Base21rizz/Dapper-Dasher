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
    int windowsDimensions[2];
    windowsDimensions[0] = 512;
    windowsDimensions[1] = 380;

    // Initialize Window
    InitWindow(windowsDimensions[0], windowsDimensions[1], "Dapper-Dasher");
    // Gravity (pixels / sec ) / sec
    const int gravity{1'000};

    // Nebula Variable
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // 1st Nebula data
    AnimData nebData{
        {0.0, 0.0, nebula.width / 8, nebula.height / 8},                  // Rectangle rec
        {windowsDimensions[0], windowsDimensions[1] - nebula.height / 8}, // Vector2 Pos
        0,                                                                // int frame
        1.0 / 12.0,                                                       // float updateTime
        0                                                                 // float runningTime
    };
    // 2nd Nebula Data
    AnimData neb2Data{
        {0.0, 0.0, nebula.width / 8, nebula.height / 8},                        // Rectangle rec
        {windowsDimensions[0] + 300, windowsDimensions[1] - nebula.height / 8}, // Vector2 Pos
        0,                                                                      // int frame
        1.0 / 16.0,                                                             // float updateTime
        0                                                                       // float runningTime
    };

    AnimData nebulee[2]{nebData, neb2Data};

    // Nebula X velocity (Pixels/ Sec)
    int nebVel{-200};

    // Scarfy Variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = (windowsDimensions[0] / 2) - (scarfyData.rec.width / 2);
    scarfyData.pos.y = windowsDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    // Is Scarfy in air
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
        if (scarfyData.pos.y >= windowsDimensions[1] - scarfyData.rec.height)
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
        nebulee[0].pos.x += nebVel * dT;
        // Update 2nd Nebula Position
        nebulee[1].pos.x += nebVel * dT;

        // Update Scarfy Position
        scarfyData.pos.y += velocity * dT;

        // Update Animation frame for Nebula
        nebulee[0].runningTime += dT;
        if (nebulee[0].runningTime >= nebulee[0].updateTime)
        {
            nebulee[0].runningTime = 0;
            // update animation frame
            nebulee[0].rec.x = nebulee[0].frame * nebulee[0].rec.width;
            nebulee[0].frame++;
            if (nebulee[0].frame > 7)
            {
                nebulee[0].frame = 0;
            }
        }

        nebulee[1].runningTime += dT;
        if (nebulee[1].runningTime >= nebulee[1].updateTime)
        {
            nebulee[1].runningTime = 0;
            // update animation frame
            nebulee[1].rec.x = nebulee[1].frame * nebulee[1].rec.width;
            nebulee[1].frame++;
            if (nebulee[1].frame > 7)
            {
                nebulee[1].frame = 0;
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
        DrawTextureRec(nebula, nebulee[0].rec, nebulee[0].pos, WHITE);
        // Draw Nebula 2
        DrawTextureRec(nebula, nebulee[1].rec, nebulee[1].pos, RED);

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