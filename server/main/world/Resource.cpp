//
// Created by armanddu on 02/07/16.
//

#include "Resource.h"

namespace zappy {

    Resource::Resource(int id, const std::string &name): id(id), name(name) {}

    bool Resource::operator<(const Resource &b) const {
        return this->id < b.id;
    }

    std::ostream &operator<<(std::ostream &os, const Resource &r) {
        os << r.name;
        return os;
    }


}
