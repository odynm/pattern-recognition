#include <stdio.h>
#include "Drawing.h"

int main(int argc, char* argv[])
{
	InitDrawSystem();

	DrawPoint(10, 10, Colors::RED);
	DrawLine(0, 0, 100, 100, Colors::BLUE);

	StopAndWait();

	return 0;
}