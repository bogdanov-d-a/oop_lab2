// ExtraSpaceRemover.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RemoveExtraSpacesMachine.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::string tmpLine;
	while (std::getline(std::cin, tmpLine))
	{
		std::cout << CRemoveExtraSpacesMachine::RemoveExtraSpaces(tmpLine) << std::endl;
	}

	return 0;
}
