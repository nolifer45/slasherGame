#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

const float speed{0.345};

Vector2 checkKeys(Vector2 direction)
{

    if (IsKeyDown(KEY_I))
        direction.y += 1;
    if (IsKeyDown(KEY_K))
        direction.y -= 1;
    if (IsKeyDown(KEY_J))
        direction.x += 1;
    if (IsKeyDown(KEY_L))
        direction.x -= 1;
    return direction;
}

float checkRightLeft(float xDirection)
{
    float rightLeft{1.f};
    xDirection > 0.f ? rightLeft = -1.f : rightLeft = 1.f;
    return rightLeft;
}

class Character
{
public:
    Vector2 getWorldPosition() { return worldPosition; }
    void setScreenPosition(int windowWidth, int windowHeight);
    void tick(float deltaTime);

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPosition{};
    Vector2 worldPosition{};
    // rightLeft = 1: Right, rightLeft = -1: Left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrame{6};
    const float updateTime{1.f / 12.f};
    const float speed{2.f};
};

Vector2 updateMapPos(Vector2 mapPos, Vector2 subVector)
{
    mapPos = Vector2Add(mapPos, Vector2Scale(Vector2Normalize(subVector), speed));
    if (mapPos.x > 0)
    {
        mapPos.x = 0;
    }
    else if (mapPos.x < -2304.0)
    {
        mapPos.x = -2304.0;
    }
    if (mapPos.y > 0)
    {
        mapPos.y = 0;
    }
    else if (mapPos.y < -2304.0)
    {
        mapPos.y = -2304.0;
    }
    return mapPos;
}

void Character::setScreenPosition(int windowWidth, int windowHeight)
{
    screenPosition = {
        windowWidth / 2 - 8.0F * (0.5F * (float)texture.width / 6),
        windowHeight / 2 - 8.0F * (0.5F * (float)texture.height)
    };
}
void Character::tick(float deltaTime)
{
    Vector2 direction{};
    if (IsKeyDown(KEY_I))
        direction.y += 1;
    if (IsKeyDown(KEY_K))
        direction.y -= 1;
    if (IsKeyDown(KEY_J))
        direction.x += 1;
    if (IsKeyDown(KEY_L))
        direction.x -= 1;
    if (Vector2Length(direction) != 0.0)
    {
        worldPosition = Vector2Subtract(worldPosition, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? rightLeft = 1.f : rightLeft = -1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    runningTime += GetFrameTime();

    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrame)
            frame = 0;
    }
    // Draw the knight
    Rectangle source{frame * (float)texture.width / 6, 0.f, rightLeft * (float)texture.width / 6, (float)texture.height};
    Rectangle dest{screenPosition.x, screenPosition.y, 4.0f * (float)texture.width / 6.0f, 4.0f * (float)texture.height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}
int main()
{
    const float windowDimensionVector[2]{768.0, 768.0};
    InitWindow(windowDimensionVector[0], windowDimensionVector[1], "slasher!");

    Texture2D map = LoadTexture("/Users/Niko/Documents/GameDev/ultimateSlash/nature_tileset/WorldMapv2.png");
    Vector2 mapPosition{};

    //Init player character
    Character knight;
    knight.setScreenPosition(windowDimensionVector[0],windowDimensionVector[1]);

    while (!WindowShouldClose())
    {
        // Start draw window
        BeginDrawing();
        ClearBackground(WHITE);

        mapPosition = Vector2Scale(knight.getWorldPosition(),-1.f);
        
        // Draw the map
        DrawTextureEx(map, mapPosition, 0.0, 4.0, WHITE);
        knight.tick(GetFrameTime());  

        EndDrawing();
    }
    // Unload program assets
    CloseWindow();
    UnloadTexture(map);
}