#include "raylib.h"

class Character
{
public:
    Character(int windowWidth,int windowHeight);
    Vector2 getWorldPosition() { return worldPosition; }
    void tick(float deltaTime);
    void undoMovement();

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPosition{};
    Vector2 worldPosition{};
    Vector2 worldPositionLastFrame{};
    // rightLeft = 1: Right, rightLeft = -1: Left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    int maxFrame{6};
    float updateTime{1.f / 12.f};
    float speed{0.5};
    float width;
    float height;
    float scale{8.f};
};