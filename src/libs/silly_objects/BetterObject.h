//
// Created by klei on 4/11/18.
//

#ifndef PRODUCTION_LINE_SIMULATOR_BETTEROBJECT_H
#define PRODUCTION_LINE_SIMULATOR_BETTEROBJECT_H

#include <cstdint>

class BetterObject {
public:

	explicit BetterObject(uint8_t timesBetter);

	void shoutOut();
private:
	uint16_t mTimesBetter;
};

#endif //PRODUCTION_LINE_SIMULATOR_BETTEROBJECT_H
