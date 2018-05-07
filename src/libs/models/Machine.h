#ifndef PRODUCTION_LINE_CONTROL_MACHINECONFIGURATION_H
#define PRODUCTION_LINE_CONTROL_MACHINECONFIGURATION_H

// standard includes
#include <memory>
#include <string>

// library includes
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <cereal/cereal.hpp>

// other includes
#include "MachineConfiguration.h"

namespace Models {

    class Machine;
    typedef std::shared_ptr<Machine> MachinePtr;

    class Machine {
    public:
        Machine();
        Machine(uint16_t aId, std::string aName);
        Machine(const Machine &other);
        virtual ~Machine();

        Machine& operator=(const Machine& other);

        void deserialize(YAML::Node &machineNode);

        /**
        * A function to get the id of the machine
        * @return The id of the machine
        */
        uint16_t getId() const;

        const std::string &getName() const;
        const std::vector<MachineConfiguration> &getConfigurations() const;

    protected:
        uint16_t id;
        std::string name;
        std::vector<MachineConfiguration> configurations;

    private:
        template<class Archive>
        void save(Archive& ar) const
        {
            ar(id, name, configurations);
        }

        template<class Archive>
        void load(Archive& ar){
            ar(id, name, configurations);
        };

        friend class ::cereal::access;
    };

}

#endif //PRODUCTION_LINE_CONTROL_MACHINECONFIGURATION_H
