/*
 * Copyright (c) 2015-2016 Joost Kraaijeveld. See license.txt for details.
 * For information, bug reports and additions send an e-mail to ProjectTemplate@Askesis.nl.
 *
 * Author: jkr
 */


#include <iostream>

#include "silly_objects/Lib1.hpp"
#include "SimulationController.h"


int main( 	int argc,
			char** argv)
{
	std::cout << "Hello from app production control!" << std::endl;
	Lib1::print();

    Core::SimulationController simController = Core::SimulationController();
    Core::Controller controller = Core::Controller();
	return 0;
}
