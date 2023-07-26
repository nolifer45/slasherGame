#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include "Character.h"
#include "Prop.h"


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

bool checkBoundary(Vector2 mapPos)
{
    bool knightHitMapBoundary = false;
    if (mapPos.x < 0 || mapPos.x > 2295.0 || mapPos.y < 0 || mapPos.y > 2295.0)
    {
        knightHitMapBoundary = true;
    }
    return knightHitMapBoundary;
}
int main()
{
    const float windowDimensionVector[2]{768.0, 768.0};
    InitWindow(windowDimensionVector[0], windowDimensionVector[1], "slasher!");

    Texture2D map = LoadTexture("/Users/Niko/Documents/GameDev/ultimateSlash/nature_tileset/WorldMapv2.png");
    Vector2 mapPosition{};

    //Init player character
    Character knight(windowDimensionVector[0],windowDimensionVector[1]);

    //Inite props
    Prop stone(mapPosition,LoadTexture(/Users/Niko/Documents/GameDev/ultimateSlash/nature_tileset/Rock.png));

    while (!WindowShouldClose())
    {
        // Start draw window
        BeginDrawing();
        ClearBackground(WHITE);

        mapPosition = Vector2Scale(knight.getWorldPosition(),-1.f);
        if (checkBoundary(knight.getWorldPosition())){
            knight.undoMovement();
        }
        // Draw the map
        DrawTextureEx(map, mapPosition, 0.0, 4.0, WHITE);
        knight.tick(GetFrameTime());  
        stone.render(knight.getWorldPosition();)
        EndDrawing();
        
    }
    // Unload program assets
    CloseWindow();
    UnloadTexture(map);
}