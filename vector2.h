#include <iostream>

struct Vector2
{
public:
    int x;
    int y;
    Vector2()
    {
        x = 0;
        y = 0;
    }

    Vector2(int xc, int yc)
    {
        x = xc;
        y = yc;
    }

    void ensureBox(int xMin, int yMin, int xMax, int yMax)
    {
        if (x <= xMin)
	  x = (xMax - 1)-1;

        if (x >= xMax-1)
            x = xMin+1;

        if (y <= yMin)
	  y = (yMax - 1)-1;

        if (y >= yMax-1)
            y = yMin+1;
    }

    void print()
    {
       std::cout << "(" << x << "," << y << ")" << std::endl;
    }

    bool equals(Vector2 other)
    {
        return x == other.x && y == other.y;
    }
    void randomInBox(int xMin, int yMin, int xMax, int yMax)
    {
	x = std::max(xMin+1,rand() % (xMax-1));
	y = std::max(yMin+1,rand() % (yMax-1));
    }
};

Vector2 vector2sum(Vector2 a, Vector2 b)
{
    Vector2 c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}
