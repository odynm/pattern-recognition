#include <stdio.h>
#include <stdlib.h>
#include "Drawing.h"

typedef struct SPoint {
    int x, y;
} Point;

typedef struct SStack {
    int pointer;
    double* stack;
} Stack;

void AddToStack(Stack* stack, double value)
{
    stack->stack[stack->pointer] = value;
    stack->pointer++;
}

double
Slope(Point p1, Point p2)
{
    double xd = (p2.x - p1.x);
    double yd = (p2.y - p1.y);
    if (xd == 0 || yd == 0) return 0;
    return yd / xd;
}

void
MarkColinears(Point* points, int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        double* slopePoints = (double*)malloc(sizeof(double) * 4);
        for (int j = 0; j < length; j++)
        {
            if (i == j) continue;
            slopePoints[j] = Slope(points[i], points[j]);
        }

        Sort(slopePoints);

        Stack colinearPoints = {};
        colinearPoints.stack = (double*)malloc(sizeof(double) * length);

        bool stackHasItems;
        for (int j = 0; j < length-1; j++)
        {
            if (slopePoints[i] == slopePoints[j])
            {
                stackHasItems = true;
                AddToStack(&colinearPoints, slopePoints[i]);// Add only i. J will wait.
            }
            else
            {
                if (stackHasItems)
                {
                    stackHasItems = false;
                    AddToStack(&colinearPoints, slopePoints[i]); // Add i (previous j that was no added before)

                    DrawStack(&colinearPoints);
                }
            }
        }
    }
}

int main(int argc, char* argv[])
{
    InitDrawSystem();

    Point* points = (Point*)malloc(sizeof(Point) * 4);

    // The points
    for (int i = 1; i < 5; i++)
    {
        points[i - 1].x = i * 50;
        points[i - 1].y = i * 40;
    }

    for (int i = 0; i < 4; i++)
    {
        DrawPoint(points[i].x, points[i].y, Colors::RED);
    }

    MarkColinears(points, 4);

    StopAndWait();

    return 0;
}