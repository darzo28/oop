#include "CShapeController.h"

int main()
{
	CShapeController controller(std::cin, std::cout);
	controller.ProcessCommands();
	controller.PrintShapesInfo();
}