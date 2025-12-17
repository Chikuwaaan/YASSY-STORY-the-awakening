#include "Input.h"

void Input::GetKey() {
    keystate = SDL_GetKeyboardState(NULL);
}