#include "ConfigurationReader.h"
#include "Configuration.h"

int main(int argc, char** argv) {
    const std::string fileName = argv[1];
    ConfigurationReader configurationReader = ConfigurationReader::getInstance(fileName);
	return 0;
}
