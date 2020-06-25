#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <emscripten.h>

#define NUM_CIRCLES 700

struct Color
{
    float red;
    float green;
    float blue;
    float alpha;
};

struct HSVColor
{
    float h;
    float s;
    float v;
};

struct ColorAnimation
{
    int hVelocity;
    int hDirection;
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
struct HSVColor mainHSVColor;
struct ColorAnimation mainColorAnimation;

int getRandom(int max)
{
    return (rand() % (max + 1));
}

void initCircles(int maxWidth, int maxHeigth)
{
    for (int i = 0; i < NUM_CIRCLES; i++)
    {
        int r = getRandom(25);
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
        circlesAnimations[i].xVelocity = getRandom(5) + 1;
        circlesAnimations[i].yVelocity = getRandom(5) + 1;
        circlesAnimations[i].xDirection = 1 - 2 * getRandom(1);
        circlesAnimations[i].yDirection = 1 - 2 * getRandom(1);
    }
}

struct Color hsv2rgb(struct HSVColor color)
{
    float v = color.v / 100;
    float s = color.s / 100;
    float h = color.h;
    float hh, p, q, t, ff, r, g, b;
    long i;
    struct Color result;

    if (s <= 0)
    { // < is bogus, just shuts up warnings
        result.red = v * 255;
        result.green = v * 255;
        result.blue = v * 255;
        return result;
    }

    hh = h;
    if (hh >= 360)
        hh = 0;
    hh /= 60;
    i = (long)hh;
    ff = hh - i;
    p = v * (1 - s);
    q = v * (1 - (s * ff));
    t = v * (1 - (s * (1 - ff)));

    switch (i)
    {
    case 0:
        r = v;
        g = t;
        b = p;
        break;
    case 1:
        r = q;
        g = v;
        b = p;
        break;
    case 2:
        r = p;
        g = v;
        b = t;
        break;
    case 3:
        r = p;
        g = q;
        b = v;
        break;
    case 4:
        r = t;
        g = p;
        b = v;
        break;
    case 5:
    default:
        r = v;
        g = p;
        b = q;
        break;
    }

    result.red = r * 255;
    result.green = g * 255;
    result.blue = b * 255;
    return result;
}

void initMainColor()
{
    mainHSVColor.h = getRandom(361);
    mainHSVColor.s = 25.0;
    mainHSVColor.v = 100.0;

    struct Color convertedColor = hsv2rgb(mainHSVColor);
    mainColor.red = convertedColor.red;
    mainColor.green = convertedColor.green;
    mainColor.blue = convertedColor.blue;
    mainColor.alpha = 0.5;

    mainColorAnimation.hVelocity = 1 + getRandom(2);
    mainColorAnimation.hDirection = 1;
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

struct Circle *getCircles(int canvasWidth, int canvasHeigth, int repulsivePointX, int repulsivePointY)
{
    for (int i = 0; i < NUM_CIRCLES; i++)
    {
        if (repulsivePointX != -1 && repulsivePointY != -1)
        {
            float influenceZone = 300;
            float diffX = circles[i].x - repulsivePointX;
            float diffY = circles[i].y - repulsivePointY;
            float d = sqrt(diffX * diffX + diffY * diffY);

            if (d < influenceZone)
            {
                if (diffX * circlesAnimations[i].xDirection < 0)
                {
                    circlesAnimations[i].xDirection *= -1;
                }

                if (diffY * circlesAnimations[i].yDirection < 0)
                {
                    circlesAnimations[i].yDirection *= -1;
                }
            }
        }

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

struct Color getMainColor()
{
    int hDecay = mainColorAnimation.hDirection * mainColorAnimation.hVelocity;
    if (mainHSVColor.h + hDecay < 0 || mainHSVColor.h + hDecay > 360)
    {
        mainColorAnimation.hDirection *= -1;
    }

    mainHSVColor.h += mainColorAnimation.hVelocity * mainColorAnimation.hDirection;

    struct Color convertedColor = hsv2rgb(mainHSVColor);
    mainColor.red = convertedColor.red;
    mainColor.green = convertedColor.green;
    mainColor.blue = convertedColor.blue;

    return mainColor;
}