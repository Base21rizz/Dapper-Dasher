#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnground(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updadteAnimData(AnimData data, float deltaTime, int maxFrame)
{
    // Update running time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{
    // Window Dimensions
    int windowsDimensions[2];
    windowsDimensions[0] = 512;
    windowsDimensions[1] = 380;

    // Initialize Window
    InitWindow(windowsDimensions[0], windowsDimensions[1], "Dapper Dasher");
    // Gravity (pixels / sec ) / sec
    const int gravity{1'000};

    // Nebula Variable
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    const int sizeOfnebulae{21};
    AnimData nebulae[sizeOfnebulae]{};

    for (int i = 0; i < sizeOfnebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;
        nebulae[i].pos.y = windowsDimensions[1] - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0 / 16.0;
        nebulae[i].pos.x = windowsDimensions[0] + i * 300;
    };

    float finishLine{nebulae[sizeOfnebulae - 1].pos.x + 160};

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

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};
    Texture2D midGround = LoadTexture("textures/back-buildings.png");
    float mgX{};
    Texture2D foreGround = LoadTexture("textures/foreground.png");
    float fgX{};

    // Check for collision variable
    bool collision{false};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Delta time (time since last frame)
        const float dT = GetFrameTime();

        // Begin Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Scroll Background
        bgX -= 20 * dT;
        if (bgX <= -background.width * 2)
        {
            bgX = 0.0;
        }
        // Scroll Midground
        mgX -= 40 * dT;
        if (mgX <= -midGround.width * 2)
        {
            mgX = 0.0;
        }
        // Scroll Foreground
        fgX -= 80 * dT;
        if (fgX <= -foreGround.width * 2)
        {
            fgX = 0.0;
        }

        // Draw Background
        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos{bgX + background.width * 2, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

        Vector2 mg1Pos{mgX, 0.0};
        DrawTextureEx(midGround, mg1Pos, 0.0, 2.0, WHITE);
        Vector2 mg2Pos{mgX + midGround.width * 2, 0.0};
        DrawTextureEx(midGround, mg2Pos, 0.0, 2.0, WHITE);

        Vector2 fg1Pos{fgX, 0.0};
        DrawTextureEx(foreGround, fg1Pos, 0.0, 2.0, WHITE);
        Vector2 fg2Pos{fgX + foreGround.width * 2, 0.0};
        DrawTextureEx(foreGround, fg2Pos, 0.0, 2.0, WHITE);

        // Game Logic Start
        // Perform Ground Check
        if (isOnground(scarfyData, windowsDimensions[1]))
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

        for (int i = 0; i < sizeOfnebulae; i++)
        {
            // Update Nebula Position
            nebulae[i].pos.x += nebVel * dT;
        }

        // Update finishLine
        finishLine += nebVel * dT;

        // Update Scarfy Position
        scarfyData.pos.y += velocity * dT;

        for (int i = 0; i < sizeOfnebulae; i++)
        {
            // Update Animation frame for Nebula
            nebulae[i] = updadteAnimData(nebulae[i], dT, 7);
        }

        for (AnimData nebula : nebulae)
        {
            float pad{50};
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2 * pad,
                nebula.rec.height - 2 * pad};
            Rectangle scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height};
            if (CheckCollisionRecs(nebRec, scarfyRec))
            {
                collision = true;
            }
        }

        if (collision)
        {
            // Lose The Game
            DrawText("Game Over!", windowsDimensions[0] / 4, windowsDimensions[1] / 2, 40, RED);
        }
        else if (scarfyData.pos.x >= finishLine)
        {
            // Win The Game
            DrawText("You Win!", windowsDimensions[0] / 4, windowsDimensions[1] / 2, 40, BLUE);
        }
        else
        {
            // Draw Nebula
            for (int i = 0; i < sizeOfnebulae; i++)
            {
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }

            // Draw Scarfy
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        }
        // Update Animation frame for Scarfy
        if (!isInAir)
        {
            scarfyData = updadteAnimData(scarfyData, dT, 5);
        }
        // Game Logic End
        // End Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midGround);
    UnloadTexture(foreGround);
    CloseWindow();
}