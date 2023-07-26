#include "Prop.h"
#include "raymath.h"
#include "raylib.h"

Prop::Prop(Vector2 position, Texture2D texture):
worldPosition(position),
texture(texture)
{
}

void render(Vector2 knightposition){
    screenPosition = Vector2Subtract(worldPosition,knightposition);
    DrawTextureEx(texture,screenPosition,0.0,4.0,WHITE);
}

