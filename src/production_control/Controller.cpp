//
// Created by sven on 22-4-18.
//

#include "Controller.h"


core::Controller::Controller() : executing(false) {

}

void core::Controller::execute() {
	executing = true;
	while(executing){
		application.run();
	}
}

void core::Controller::stop() {
	executing = false;
}
