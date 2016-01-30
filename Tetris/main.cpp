#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;
enum load_errors {
    INIT_FAILED = 1,
    WINDOW_DRAW_FAILED
};
enum key_surfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Window* window = NULL;
SDL_Surface* screen_surface = NULL;
SDL_Surface* blocks[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* current_surface = NULL;

bool init();
void drawInitialScreen();
void drawImage(SDL_Surface*);
SDL_Surface* loadImage(char*);

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL failed to initialize. Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

bool createWindow() {
    window = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Could not create window. Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void drawInitialScreen() {
    screen_surface = SDL_GetWindowSurface(window);
    SDL_FillRect(screen_surface, NULL,
        SDL_MapRGB(screen_surface->format,
            0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
}

SDL_Surface* loadImage(char* location) {
    SDL_Surface* image = SDL_LoadBMP(location);
    if (image == NULL) {
        printf("Failed to load resource \"%s\".", location);
    }

    return image;
}

void drawImage(SDL_Surface* image) {
    SDL_BlitSurface(image, NULL, screen_surface, NULL);
    SDL_UpdateWindowSurface(window);
}

void gameLoop() {
    SDL_Event e;
    bool quit = false;

    blocks[KEY_PRESS_SURFACE_DEFAULT] = loadImage("images/orange_block.bmp");
    blocks[KEY_PRESS_SURFACE_LEFT] = loadImage("images/red_block.bmp");
    blocks[KEY_PRESS_SURFACE_RIGHT] = loadImage("images/blue_block.bmp");
    blocks[KEY_PRESS_SURFACE_UP] = loadImage("images/yellow_block.bmp");
    blocks[KEY_PRESS_SURFACE_DOWN] = loadImage("images/green_block.bmp");

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_w:
                    current_surface = blocks[KEY_PRESS_SURFACE_UP];
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    current_surface = blocks[KEY_PRESS_SURFACE_DOWN];
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    current_surface = blocks[KEY_PRESS_SURFACE_LEFT];
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    current_surface = blocks[KEY_PRESS_SURFACE_RIGHT];
                    break;
                default:
                    current_surface = blocks[KEY_PRESS_SURFACE_DEFAULT];
                    break;
                }
            }
        }
        SDL_BlitSurface(current_surface, NULL, screen_surface, NULL);
        SDL_UpdateWindowSurface(window);
    }
}

int main(int argc, char* args[]) {
    if (!init()) {
        return INIT_FAILED;
    }
    if (!createWindow()) {
        return WINDOW_DRAW_FAILED;
    }
    SDL_Surface* background_image = loadImage("C:/Users/bry/Documents/Visual Studio 2015/Projects/Project1/Project1/x.bmp");
    drawInitialScreen();

    drawImage(background_image);

    gameLoop();

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}