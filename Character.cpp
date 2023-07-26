#include "Character.h"
#include "raymath.h"

Character::Character(int windowWidth,int windowHeight){
    width = (float)texture.width / maxFrame;
    height  = (float)texture.height;
     screenPosition = {
       static_cast<float>(windowWidth) / 2 - scale * (0.5F * width),
        static_cast<float>(windowHeight) / 2 - scale * (0.5F * height)
    };
}

void Character::tick(float deltaTime)
{
    worldPositionLastFrame = worldPosition;
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
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{screenPosition.x, screenPosition.y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}
void Character::undoMovement()
{
    worldPosition = worldPositionLastFrame;
}