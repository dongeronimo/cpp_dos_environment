#include "GAMEOBJS.H"

GameObject::GameObject(uint32_t w, uint32_t h, uint8_t *image)
    : mWidth(w), mHeight(h), mImage(image), mX(0), mY(0)
{
}

