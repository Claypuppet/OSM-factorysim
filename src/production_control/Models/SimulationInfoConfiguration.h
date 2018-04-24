#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONINFOCONFIG_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONINFOCONFIG_H

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>

namespace models {

    class SimulationInfoConfiguration {
    public:
        SimulationInfoConfiguration();

        SimulationInfoConfiguration(const SimulationInfoConfiguration &other);

        virtual ~SimulationInfoConfiguration();

        void deserialize(YAML::Node &simulationInfoConfigurationNode);

        uint8_t getDurationInHours() const;

    private:
        uint8_t durationInHours;
    };

}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONINFOCONFIG_H
