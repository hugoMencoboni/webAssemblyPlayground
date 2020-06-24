#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <emscripten.h>

#define NUM_CIRCLES 500

struct Color
{
    float red;
    float green;
    float blue;
    float alpha;
};

struct ColorAnimation
{
    int rVelocity;
    int gVelocity;
    int bVelocity;

    int rDirection;
    int gDirection;
    int bDirection;
};

struct Circle
{
    float x;
    float y;
    float r;
    struct Color color;
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
struct Color mainColor;
struct ColorAnimation mainColorAnimation;

int getRandom(int max)
{
    return (rand() % (max + 1));
}

void initCircles(int maxWidth, int maxHeigth)
{
    for (int i = 0; i < NUM_CIRCLES; i++)
    {
        int r = getRandom(50);
        circles[i].r = r;
        int x = getRandom(maxWidth - r);
        int y = getRandom(maxHeigth - r);
        circles[i].x = x < r ? x + r : x;
        circles[i].y = y < r ? y + r : y;

        // Color
        circles[i].color.red = getRandom(255);
        circles[i].color.green = getRandom(255);
        circles[i].color.blue = getRandom(255);
        circles[i].color.alpha = 1.0 / (1 + getRandom(3));

        // Animation
        circlesAnimations[i].xVelocity = getRandom(10) + 1;
        circlesAnimations[i].yVelocity = getRandom(10) + 1;
        circlesAnimations[i].xDirection = 1 - 2 * getRandom(1);
        circlesAnimations[i].yDirection = 1 - 2 * getRandom(1);
    }
}

void initMainColor()
{
    mainColor.red = getRandom(255);
    mainColor.green = getRandom(255);
    mainColor.blue = getRandom(255);
    mainColor.alpha = 0.5;

    mainColorAnimation.rVelocity = getRandom(2);
    mainColorAnimation.gVelocity = getRandom(2);
    mainColorAnimation.bVelocity = getRandom(2);

    mainColorAnimation.rDirection = 1;
    mainColorAnimation.gDirection = 1;
    mainColorAnimation.bDirection = 1;
}

int main()
{
    printf("WA Loaded");
    srand(time(NULL));
    EM_ASM({ onWALoaded(); });
}

void initDrawing(int canvasWidth, int canvasHeigth)
{
    int circleStructSize = 7;
    int colorStructSize = 4;
    initMainColor();
    initCircles(canvasWidth, canvasHeigth);
    EM_ASM({ render($0, $1, $2); }, NUM_CIRCLES * circleStructSize, circleStructSize, colorStructSize);
}

struct Circle *getCircles(int canvasWidth, int canvasHeigth)
{
    for (int i = 0; i < NUM_CIRCLES; i++)
    {
        if (circles[i].x + circles[i].r > canvasWidth || circles[i].x - circles[i].r < 0)
        {
            circlesAnimations[i].xDirection *= -1;
        }

        if (circles[i].y + circles[i].r > canvasHeigth || circles[i].y - circles[i].r < 0)
        {
            circlesAnimations[i].yDirection *= -1;
        }

        circles[i].x += circlesAnimations[i].xVelocity * circlesAnimations[i].xDirection;
        circles[i].y += circlesAnimations[i].yVelocity * circlesAnimations[i].yDirection;
    }

    return circles;
}

struct Color getColor()
{
    int rDecay = mainColorAnimation.rDirection * mainColorAnimation.rVelocity;
    if (mainColor.red + rDecay < 0 || mainColor.red + rDecay > 255)
    {
        mainColorAnimation.rDirection *= -1;
    }

    int gDecay = mainColorAnimation.gDirection * mainColorAnimation.gVelocity;
    if (mainColor.green + gDecay < 0 || mainColor.green + gDecay > 255)
    {
        mainColorAnimation.gDirection *= -1;
    }

    int bDecay = mainColorAnimation.bDirection * mainColorAnimation.bVelocity;
    if (mainColor.blue + bDecay < 0 || mainColor.blue + bDecay > 255)
    {
        mainColorAnimation.bDirection *= -1;
    }

    mainColor.red += mainColorAnimation.rDirection * mainColorAnimation.rVelocity;
    mainColor.green += mainColorAnimation.gDirection * mainColorAnimation.gVelocity;
    mainColor.blue += mainColorAnimation.bDirection * mainColorAnimation.bVelocity;

    return mainColor;
}