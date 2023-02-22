#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

Vector2 checkKeys(Vector2 direction)
{

    if (IsKeyDown(KEY_I)) direction.y += 1;
    if (IsKeyDown(KEY_K)) direction.y -= 1;
    if (IsKeyDown(KEY_J)) direction.x += 1;
    if (IsKeyDown(KEY_L)) direction.x -= 1;
    return direction;
}
                                                                                                                                                                                                                
Vector2 updateMapPos(Vector2 mapPos, Vector2 subVector,float movementSpeed,bool updateKnight) 
{
    mapPos = Vector2Add(mapPos, Vector2Scale(Vector2Normalize(subVector),movementSpeed));
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

Vector2 updateKnightPos(Vector2 knightPos,Vector2 subVector,float movementSpeed) {
    subVector = {-subVector.x,-subVector.y};
    knightPos = Vector2Add(knightPos, Vector2Scale(Vector2Normalize(subVector),movementSpeed));
    return knightPos;
}

float checkRightLeft(float xDirection) {
    float rightLeft{1.f};
     xDirection > 0.f ? rightLeft = -1.f : rightLeft = 1.f;
     return rightLeft;
}
int main()
{
    const float windowDimensions[2]{768.0,768.0};
    float speed{0.345};
    InitWindow(windowDimensions[0],windowDimensions[1],"slasher!");

    Texture2D map = LoadTexture("/Users/Niko/Documents/GameDev/ultimateSlash/nature_tileset/WorldMapv2.png");
    Vector2 mapPos{};

    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos{
        windowDimensions[0]/2 - 8.0F*(0.5F*(float)knight.width/6),
        windowDimensions[1]/2 - 8.0F*(0.5F*(float)knight.height)
    };

    bool shouldUpdateKnight = true;
    float rightLeft{1.f};

    while(!WindowShouldClose())
    {
        //Start draw window
        BeginDrawing();
        ClearBackground(WHITE);
        Vector2 direction{};

        
        direction = checkKeys(direction);


        if (Vector2Length(direction) != 0.0)
        {
            mapPos = updateMapPos(mapPos,direction,speed,shouldUpdateKnight);
            knightPos = updateKnightPos(knightPos,direction,speed);

            //Set direction left/right
            if (direction.x != 0) {
                rightLeft = checkRightLeft(direction.x);
            }
        }
       
        
        
        
        //Draw the map      
        DrawTextureEx(map,mapPos,0.0,4.0,WHITE);
        
        //Draw the knight
        Rectangle source {0.f,0.f, rightLeft * (float)knight.width/6 ,(float)knight.height};
        Rectangle dest {knightPos.x,knightPos.y,4.0f*(float)knight.width/6.0f,4.0f*(float)knight.height};
        DrawTexturePro(knight,source,dest,Vector2{},0.f,WHITE);
        
        EndDrawing();
    }
    //Unload program assets 
    CloseWindow();
    UnloadTexture(map);
    UnloadTexture(knight);
}