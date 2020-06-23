#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <emscripten.h>

#define NUM_CIRCLES 200

struct Circle
{
    int x;
    int y;
    int r;
    int cr;
    int cg;
    int cb;
    float ca;
};

struct CircleAnimation
{
    int xVelocity;
    int yVelocity;
    
    int xDirection;
    int yDirection;
};

struct Circle circles[NUM_CIRCLES];
struct CircleAnimation circlesAnimations[NUM_CIRCLES];

int getRandom(int max)
{
    return (rand() % max);
}

void initCircles()
{
    srand(time(NULL));
    for (int i = 0; i < NUM_CIRCLES; i++)
    {
        int r = getRandom(50);
        circles[i].r = r;
        int x = getRandom(2000 - r); // TODO: passer la width du canvas
        int y = getRandom(2000 - r); // TODO: passer la width du canvas
        circles[i].x = x < r ? x + r : x; 
        circles[i].y = y < r ? y + r : y;

        // Color
        circles[i].cr = getRandom(255);
        circles[i].cg = getRandom(255);
        circles[i].cb = getRandom(255);
        circles[i].ca = 0.75;

        // Animation
        circlesAnimations[i].xVelocity = getRandom(10);
        circlesAnimations[i].yVelocity = getRandom(10);
        circlesAnimations[i].xDirection = 1 - 2 * getRandom(1);
        circlesAnimations[i].yDirection = 1 - 2 * getRandom(1);
    }
}

int main()
{
    printf("Rendering");
    initCircles();
    int circleStructSize = 7;
    EM_ASM({ render($0, $1); }, NUM_CIRCLES * circleStructSize, circleStructSize);
}

struct Circle *getCircles(int canvasWidth, int canvasHeigth)
{
    for (int i = 0; i < NUM_CIRCLES; i++)
    {
        if(circles[i].x + circles[i].r > canvasWidth || circles[i].x - circles[i].r < 0) {
            circlesAnimations[i].xDirection *= -1;
        }
        
        if(circles[i].y + circles[i].r > canvasHeigth || circles[i].y - circles[i].r < 0) {
            circlesAnimations[i].yDirection *= -1;
        }

        circles[i].x += circlesAnimations[i].xVelocity * circlesAnimations[i].xDirection;
        circles[i].y += circlesAnimations[i].yVelocity * circlesAnimations[i].yDirection;
    }

    return circles;
}