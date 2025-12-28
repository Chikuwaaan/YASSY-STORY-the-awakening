#include "ScreenShot.h"
#include "namespace.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


void ScreenShot::SaveScreenShot() {
    int w, h;
    SDL_GetRendererOutputSize(settings::renderer, &w, &h);

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA32);

    if (!surface) return;

    SDL_RenderReadPixels(settings::renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
    IMG_SavePNG(surface, "screenshot.png");
    SDL_FreeSurface(surface);

    std::cout << "スクリーンショットを保存しました" << std::endl;
}
