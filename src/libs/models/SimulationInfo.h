#ifndef PRODUCTION_LINE_CONTROL_SIMULATIONINFOCONFIG_H
#define PRODUCTION_LINE_CONTROL_SIMULATIONINFOCONFIG_H

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <cereal/cereal.hpp>

namespace Models {

    class SimulationInfo {
    public:
        SimulationInfo();
        SimulationInfo(const SimulationInfo &other);
        virtual ~SimulationInfo();

        SimulationInfo& operator=(const SimulationInfo& other);

        void deserialize(YAML::Node &simulationInfoNode);

        uint8_t getDurationInHours() const;

    private:
        uint8_t durationInHours;

        template <class Archive>
        void save(Archive& ar) const
        {
            ar(durationInHours);
        }

        template <class Archive>
        void load(Archive& ar)
        {
            ar(durationInHours);
        }

        friend class cereal::access;
    };

}

#endif //PRODUCTION_LINE_CONTROL_SIMULATIONINFOCONFIG_H
