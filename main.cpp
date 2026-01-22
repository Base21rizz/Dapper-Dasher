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

    const int sizeOfNebulee{10};
    AnimData nebulee[sizeOfNebulee]{};

    for (int i = 0; i < sizeOfNebulee; i++)
    {
        nebulee[i].rec.x = 0.0;
        nebulee[i].rec.y = 0.0;
        nebulee[i].rec.width = nebula.width / 8;
        nebulee[i].rec.height = nebula.height / 8;
        nebulee[i].pos.y = windowsDimensions[1] - nebula.height / 8;
        nebulee[i].frame = 0;
        nebulee[i].runningTime = 0.0;
        nebulee[i].updateTime = 1.0 / 16.0;
        nebulee[i].pos.x = windowsDimensions[0] + i * 300;
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

        for (int i = 0; i < sizeOfNebulee; i++)
        {
            // Update Nebula Position
            nebulee[i].pos.x += nebVel * dT;
        }

        // Update Scarfy Position
        scarfyData.pos.y += velocity * dT;

        for (int i = 0; i < sizeOfNebulee; i++)
        {
            // Update Animation frame for Nebula
            nebulee[i].runningTime += dT;
            if (nebulee[i].runningTime >= nebulee[i].updateTime)
            {
                nebulee[i].runningTime = 0.0;
                // update animation frame
                nebulee[i].rec.x = nebulee[i].frame * nebulee[i].rec.width;
                nebulee[i].frame++;
                if (nebulee[i].frame > 7)
                {
                    nebulee[i].frame = 0;
                }
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
        for (int i = 0; i < sizeOfNebulee; i++)
        {
            DrawTextureRec(nebula, nebulee[i].rec, nebulee[i].pos, WHITE);
        }

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