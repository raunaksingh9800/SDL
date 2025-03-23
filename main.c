#include <SDL.h>
#include <stdio.h>

#define WIDTH 900
#define HEIGHT 600
#define GRAVITY 9.8
#define TIME_STEP 0.016/2 // Approx. 60 FPS
#define LINE_WIDTH 1
#define RAY_COUNT 400
#define BLEED 300

struct Circle {
    double x;
    double y;
    double r;
    double vy; // velocity-y
    double BOUNCE_DAMPING;
};

struct Line{
    double x1;
    double y1;

    double x2;
    double y2;
}; // (x1, y1) . (x2,y2)


struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b; 
};

struct RGB COLOR_WHITE = {255, 255, 255};
struct RGB COLOR_YELLOW = {255, 230, 102}; // {255, 230, 102}->yellow




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

void DrawLine(SDL_Surface* surface, struct Line* line, struct RGB* rgb, struct Circle* col_c, int count) {
    int x1 = line->x1;
    int y1 = line->y1;
    int x2 = line->x2;
    int y2 = line->y2;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        
        double dist_sq = (x1 - col_c->x) * (x1 - col_c->x) + (y1 - col_c->y) * (y1 - col_c->y);
        if (dist_sq <= col_c->r * col_c->r) {
            if (count) {
            
            }
           
            SDL_Rect pixel = {x1, y1, LINE_WIDTH, LINE_WIDTH};
            SDL_FillRect(surface, &pixel, SDL_MapRGB(surface->format, rgb->r, rgb->g, rgb->b));
            break; 
        } else {
            if (count) {
                
            }
            SDL_Rect pixel = {x1, y1, LINE_WIDTH, LINE_WIDTH};
            SDL_FillRect(surface, &pixel, SDL_MapRGB(surface->format, rgb->r, rgb->g, rgb->b));
        }

        // If we've reached the end point, break out
        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}


void CastRay(SDL_Surface* surface, struct Circle* c, struct Line* l, struct RGB* color, struct Circle* col_c, int count){
    double angle_step = (2 * M_PI) / RAY_COUNT;
    for (int i = 0; i < RAY_COUNT; i++) {
        double angle = i * angle_step;
        l->x2 = c->x + cos(angle) * (WIDTH+BLEED);
        l->y2 = c->y + sin(angle) * (HEIGHT+BLEED);
        DrawLine(surface, l, color,col_c,count);
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
    struct Circle circle = {300, 300, 60, 0, 0.9}; 
    struct Circle circle_bigger = {500, 100, 80, 0, 0.75};

    struct Line line= {circle_bigger.x,circle_bigger.y, WIDTH,HEIGHT};
    
     // Initialize with default values

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
                    line.x1 = circle_bigger.x;
                    line.y1 = circle_bigger.y;
                }
            }
        }

        // _______GRAVITY_______
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
        line.x1 = circle_bigger.x;
        line.y1 = circle_bigger.y;
        // _______GRAVITY_______

        SDL_FillRect(surface, &e_rect, SDL_MapRGB(surface->format, 0, 0, 0));
        
        COLOR_YELLOW.g = grad;
        
        DrawCircle(surface, &circle_bigger, &COLOR_YELLOW); 
        CastRay(surface, &circle_bigger, &line, &COLOR_YELLOW, &circle, 1);
        
        DrawCircle(surface, &circle, &COLOR_WHITE); 
        SDL_UpdateWindowSurface(window);
        SDL_Delay(10); 

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
