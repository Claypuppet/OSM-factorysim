//
// Created by klei on 4/11/18.
//

#include <iostream>
#include "BetterObject.h"

BetterObject::BetterObject(uint8_t timesBetter): mTimesBetter(timesBetter) {

}

void BetterObject::shoutOut() {
	std::cout << "I'm BetterObject, and i'm " << mTimesBetter << " times better than the other Object!" << std::endl;
}
