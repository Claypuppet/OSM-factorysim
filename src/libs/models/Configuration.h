#ifndef PRODUCTION_LINE_CONTROL_CONFIG_H
#define PRODUCTION_LINE_CONTROL_CONFIG_H

#include <string>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <cereal/cereal.hpp>

#include "SimulationInfo.h"
#include "ProductionLine.h"

namespace Models {

    class Configuration {
    public:
        Configuration();
        Configuration(const Configuration &other);
        virtual ~Configuration();

        Configuration& operator=(const Configuration& other);

        void deserialize(YAML::Node &configurationNode);

        const std::string &getName() const;
        const SimulationInfo &getSimulationInfoConfiguration() const;
        const ProductionLine &getProductionLineConfiguration() const;


    private:
        std::string name;
        SimulationInfo simulationInfoConfiguration;
        ProductionLine productionLineConfiguration;

        template<class Archive>
        void save(Archive& ar) const
        {
            ar(name, simulationInfoConfiguration, productionLineConfiguration);
        }

        template<class Archive>
        void load(Archive& ar)
        {
            ar(name, simulationInfoConfiguration, productionLineConfiguration);
        }

        friend class ::cereal::access;
    };

}

#endif //PRODUCTION_LINE_CONTROL_CONFIG_H
