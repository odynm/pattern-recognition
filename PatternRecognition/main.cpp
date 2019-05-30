#include <stdio.h>
#include <stdlib.h>
#include "Drawing.h"

#define NUMBER_OF_POINTS 10
#define MIN_NUM_COLINEARS 3

typedef struct SPoint {
    int x, y;
} Point;

typedef struct SSlopeCalcPoint {
    int x, y;
    double slope;
} SlopeCalcPoint;

inline double
Slope(Point p1, Point p2)
{
    double xd = (p2.x - p1.x);
    double yd = (p2.y - p1.y);
    if (xd == 0 || yd == 0) return 0;
    return yd / xd;
}

void
DrawColinear(Point* points)
{
    DrawLine(points[0].x, points[0].y, points[1].x, points[1].y, Colors::BLUE);
}

void Merge(SlopeCalcPoint* arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    SlopeCalcPoint* L = (SlopeCalcPoint*)malloc(sizeof(SlopeCalcPoint) * n1);
    SlopeCalcPoint* R = (SlopeCalcPoint*)malloc(sizeof(SlopeCalcPoint) * n2);

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].slope <= R[j].slope)
        {
            if (L[i].slope == R[j].slope)
            {
                if (L[i].x <= R[j].x)
                {
                    arr[k] = L[i];
                    i++;
                }
                else
                {
                    arr[k] = R[i];
                    j++;
                }
            }
            else
            {
                arr[k] = R[i];
                j++;
            }
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(SlopeCalcPoint* arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);

        Merge(arr, l, m, r);
    }
}

void
ColinearSort(SlopeCalcPoint* points, int length)
{
    MergeSort(points, 0, length - 1);
}

void
MarkColinears(Point* points, int length)
{
    for (int i = 0; i < length - 1; i++)
    //for (int i = 0; i < 1; i++)
    {
        SlopeCalcPoint* pointsCalc = (SlopeCalcPoint*)calloc(sizeof(SlopeCalcPoint) * length - 1, sizeof(int));

        int realIndex = 0;
        for (int j = 0; j < length; j++)
        {
            if (i == j) continue;
            pointsCalc[realIndex].x = points[j].x;
            pointsCalc[realIndex].y = points[j].y;
            pointsCalc[realIndex].slope = Slope(points[i], points[j]);
            realIndex++;
        }

        ColinearSort(pointsCalc, length - 1);

        Point* colinearPoints = (Point*)calloc(sizeof(Point) * 2, sizeof(int));

        int numColinears = 0;
        for (int j = 0; j < length - 1; j++)
        {
            if (i == j) continue;
            if (pointsCalc[j].slope == pointsCalc[j + 1].slope)
            {
                double slope = pointsCalc[i].slope;  // Current slope
                colinearPoints[0] = points[i];       // Add point we're computing
                numColinears++;

                // Search for more colinears
                while (j < length - 1 && slope != pointsCalc[j + 1].slope)
                {
                    numColinears++;
                    // Set end
                    colinearPoints[1].x = pointsCalc[j + 1].x;
                    colinearPoints[1].y = pointsCalc[j + 1].y;
                    j++;
                }

                if (numColinears >= MIN_NUM_COLINEARS) DrawColinear(colinearPoints);
            }
        }

    }
}

int main(int argc, char* argv[])
{
    InitDrawSystem();

    Point* points = (Point*)calloc(sizeof(Point) * NUMBER_OF_POINTS, sizeof(int));

    // The points
    for (int i = 1; i < 5; i++)
    {
        points[i - 1].x = i * 50;
        points[i - 1].y = i * 40;
    }

    for (int i = 5; i < 10; i++)
    {
        points[i - 1].x = i * 50;
        points[i - 1].y = i * 80;
    }

    Point p = {};
    p.x = 500; p.y = 350;
    points[10] = p;

    for (int i = 0; i < NUMBER_OF_POINTS; i++)
    {
        DrawPoint(points[i].x, points[i].y, Colors::RED);
    }

    MarkColinears(points, NUMBER_OF_POINTS);

    StopAndWait();

    return 0;
}