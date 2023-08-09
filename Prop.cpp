#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 position, Texture2D texture):
    worldPosition(position),
    texture(texture)
{

}

void Prop::Render(Vector2 knightPosition){
    Vector2 screenPosition{ Vector2Subtract(worldPosition,knightPosition)};
    DrawTextureEx(texture,screenPosition,0.f,scale,WHITE);
}