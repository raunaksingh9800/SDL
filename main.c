#include <SDL.h>
#include <stdio.h>

#define WIDTH 900
#define HEIGHT 600
#define GRAVITY 9.8
#define TIME_STEP 0.016 // Approx. 60 FPS

struct Circle {
    double x;
    double y;
    double r;
    double vy; // velocity-y
    double BOUNCE_DAMPING;
};

struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b; 
};

struct RGB COLOR_WHITE = {255, 255, 255};
struct RGB COLOR_YELLOW = {255, 230, 0}; // {255, 230, 102}->yellow

void DrawCircle(SDL_Surface* surface, struct Circle* c,  struct RGB* rgb) {
    int rad_sq = c->r * c->r; 
    for (int x = c->x - c->r; x <= c->x + c->r; x++) {
        for (int y = c->y - c->r; y <= c->y + c->r; y++) {
            int dist_sq = (x - c->x) * (x - c->x) + (y - c->y) * (y - c->y);
            if (dist_sq < rad_sq) {
                SDL_Rect pixel = {x, y, 1, 1};  
                SDL_FillRect(surface, &pixel, SDL_MapRGB(surface->format, rgb->r, rgb->g, rgb->b));
            }
        }
    }
}

int main() {
    int grad=0;
    int cycle = 1;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WIDTH, HEIGHT,
                                          SDL_WINDOW_SHOWN);
    
    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface = SDL_GetWindowSurface(window);
    if (!surface) {
        printf("SDL_GetWindowSurface Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Rect e_rect = {0, 0, WIDTH, HEIGHT};
    struct Circle circle = {200, 200, 40, 0, 0.75}; 
    struct Circle circle_bigger = {400, 100, 80, 0, 0.9};

    SDL_Event e;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
            if (e.type == SDL_MOUSEMOTION && e.motion.state != 0) {
                if (
                    circle.x - circle.r < e.motion.x 
                    && 
                    circle.x + circle.r > e.motion.x 
                    
                    &&
                    
                    circle.y - circle.r < e.motion.y 
                    && 
                    circle.y + circle.r > e.motion.y
                ) {
                    circle.x = e.motion.x;
                    circle.y = e.motion.y;
                }
                if (
                    circle_bigger.x - circle_bigger.r < e.motion.x 
                    && 
                    circle_bigger.x + circle_bigger.r > e.motion.x 
                    
                    &&
                    
                    circle_bigger.y - circle_bigger.r < e.motion.y 
                    && 
                    circle_bigger.y + circle_bigger.r > e.motion.y
                ) {
                    circle_bigger.x = e.motion.x;
                    circle_bigger.y = e.motion.y;
                }
            }
        }

        
        if (circle.y + circle.r < HEIGHT) { 
            circle.vy += GRAVITY * TIME_STEP; 
            circle.y += circle.vy; 
        } else { 
            circle.y = HEIGHT - circle.r; 
            circle.vy = -circle.vy * circle.BOUNCE_DAMPING; 
            circle.y += circle.vy;
           
            if (circle.vy > -1 && circle.vy < 1) {
                circle.vy = 0;
            }
        }
        if (circle_bigger.y + circle_bigger.r < HEIGHT) { 
            circle_bigger.vy += GRAVITY * TIME_STEP; 
            circle_bigger.y += circle_bigger.vy; 
        } else { 
            circle_bigger.y = HEIGHT - circle_bigger.r; 
            circle_bigger.vy = -circle_bigger.vy * circle_bigger.BOUNCE_DAMPING; 
            circle_bigger.y += circle_bigger.vy;
            
            if (circle_bigger.vy > -1 && circle_bigger.vy < 1) {
                circle_bigger.vy = 0;
            }
        }

        SDL_FillRect(surface, &e_rect, SDL_MapRGB(surface->format, 0, 0, 0));
        DrawCircle(surface, &circle, &COLOR_WHITE); 
        COLOR_YELLOW.r = grad;
        COLOR_WHITE.r = grad;
        DrawCircle(surface, &circle_bigger, &COLOR_YELLOW); 
        SDL_UpdateWindowSurface(window);
        SDL_Delay(16); 
        if (cycle%2!=0)
        {
            if (grad==255){
                cycle++;
            }
            grad++;
        }
        if( cycle%2==0) {
            if (grad==0)
            {
                cycle++;
            }
            grad--;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
