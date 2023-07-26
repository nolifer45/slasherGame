#include "raylib.h"

class Prop
{
private:
    Texture2D texture;
    Vector2 worldPosition;
    float scale;
    Vector2 screenPosition;
public:
    Prop(Vector2 position,Texture2D texture);
    void render(Vector2 knightPosition);
};


