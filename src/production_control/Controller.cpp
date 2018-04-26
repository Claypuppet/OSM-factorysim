//
// Created by sven on 22-4-18.
//

#include "Controller.h"


Core::Controller::Controller() : executing(false) {

}

void Core::Controller::execute() {
	executing = true;
	while(executing){
		run();
	}

}
