#ifndef PRODUCTION_LINE_CONTROL_CONFIG_H
#define PRODUCTION_LINE_CONTROL_CONFIG_H

#include <string>
#include <memory>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <cereal/cereal.hpp>

#include "SimulationInfo.h"
#include "ProductionLine.h"

namespace Models {

    class Configuration;
    typedef std::shared_ptr<Configuration> ConfigurationPtr;

    class Configuration {
    public:
        /**
         * Default constructor
         */
        Configuration();

        /**
         * Copy constructor
         * @param other : Configuration object to copy
         */
        Configuration(const Configuration &other);

        /**
         * The destructor
         */
        virtual ~Configuration();

        /**
         * Asignment operator
         * @param other : other Configuration object
         * @return new Configuration object
         */
        Configuration& operator=(const Configuration& other);

        /**
         * A function to deserialize a configuartion node
         * @param configurationNode : the configuration node to deserialise
         */
        void deserialize(YAML::Node &configurationNode);

        /**
         * Getter for name
         * @return name
         */
        const std::string &getName() const;

        /**
         * Getter for simulationInfoConfiguration
         * @return simulationInfoConfiguration
         */
        const SimulationInfo &getSimulationInfoConfiguration() const;

        /**
         * Getter for productionLineConfiguration
         * @return productionLineConfiguration
         */
        const ProductionLine &getProductionLineConfiguration() const;


    private:
        std::string name;
        SimulationInfo simulationInfoConfiguration;
        ProductionLine productionLineConfiguration;

        /**
         * Function to save class as archive
         * @tparam Archive
         * @param ar : Archive to store class in
         */
        template<class Archive>
        void save(Archive& ar) const
        {
            ar(name, simulationInfoConfiguration, productionLineConfiguration);
        }

        /**
         * Function to load class from archive
         * @tparam Archive
         * @param ar : The archive to load
         */
        template<class Archive>
        void load(Archive& ar)
        {
            ar(name, simulationInfoConfiguration, productionLineConfiguration);
        }

        friend class ::cereal::access;
    };

}

#endif //PRODUCTION_LINE_CONTROL_CONFIG_H
