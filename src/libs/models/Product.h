#ifndef PRODUCTION_LINE_CONTROL_PRODUCTCONFIGURATION_H
#define PRODUCTION_LINE_CONTROL_PRODUCTCONFIGURATION_H

#include <string>
#include <cstdint>
#include <memory>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <cereal/cereal.hpp>

namespace Models {

    class Product;
    typedef std::shared_ptr<Product> ProductPtr;

    class Product {
    public:
        Product();
        Product(const Product &other);
        virtual ~Product();

        Product& operator=(const Product& other);

        void deserialize(YAML::Node &productNode);

        uint16_t getId() const;
        const std::string &getName() const;
        uint16_t getProportion() const;

    private:
        uint16_t id;
        std::string name;
        uint16_t proportion;

        template <class Archive>
        void save(Archive& ar) const
        {
            ar(id, name, proportion);
        }

        template<class Archive>
        void load(Archive& ar)
        {
            ar(id, name, proportion);
        }

        friend class cereal::access;
    };

}

#endif //PRODUCTION_LINE_CONTROL_PRODUCTCONFIGURATION_H
