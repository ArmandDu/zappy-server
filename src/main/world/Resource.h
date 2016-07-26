//
// Created by armanddu on 02/07/16.
//

#ifndef ZAPPY_CLIENT_RESOURCE_H
#define ZAPPY_CLIENT_RESOURCE_H


#include <vector>
#include <string>

namespace zappy {
    class Resource {

    private:
        int id;
        std::string name;

    public:
        inline int getId() const {return id;}
        inline std::string getName() const {return name;}
    public:
        Resource(int id, const std::string &name);

    public:
        bool operator<(const Resource &b) const ;

    public:
        friend std::ostream &operator<<(std::ostream &os, const Resource &r);

    };
}

#endif //ZAPPY_CLIENT_RESOURCE_H
