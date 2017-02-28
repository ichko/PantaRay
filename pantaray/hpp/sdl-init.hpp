#pragma once


int init(unsigned width, unsigned height, PantaRay::Image* buffer) {

    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            auto c = buffer->Sample(float(x), float(y)).Legalize().Scale(255);
            SDL_SetRenderDrawColor(renderer, (Uint8)c.r, (Uint8)c.g, (Uint8)c.b, 255);
            SDL_RenderDrawPoint(renderer, int(x), int(y));
        }
    }

    SDL_RenderPresent(renderer);

    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;

}
