//
// Created by armanddu on 27/06/16.
//

#ifndef ZAPPY_CLIENT_CLIENT_H
#define ZAPPY_CLIENT_CLIENT_H

#include <sys/socket.h>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <list>
#include <memory>

#include "../world/Timeout.h"
#include "Socket.h"

namespace my_tcp {
    class Client{

    public:

        enum Status {
            Unset,
            Disconnected,
            Connected
        };
        class Session {

        private:
            Client  &client_;

        public:
            Session(Client &client);

        public:
            inline const Client &getClient() const {return client_;}
            inline std::string getId() const {return client_.getId();}

        public:
            void send(const std::string &message);
            inline void disconnect() { client_.setToDisconnect(true); }

        };

    private:
        static const int BUFF_SIZE = 256;
        static int count;
    private:
        int id;
        Socket socket_;
        Status status;
        std::list<std::string> outBuffer;
        std::string partialContent;
        bool toDisconnect_;

    public:
        Client();
        Client(int fd, sockaddr_in clientData);

    public:
        void disconnect();
        bool connect(int fd, sockaddr_in clientData);

        bool isDisconnected() const;
        int getSocketFd() const;
        std::string getIp() const;
        int getPort() const;
        std::string getMessage();
        Status getStatus() const;
        void sendMessage(const std::string &message);
        std::list<std::string> getOutBuffer();
        const std::list<std::string> &getOutBuffer() const;

        unsigned long pushOutBuffer(const std::string message);

        bool popOutBuffer(std::string &res);
        void setStatus(Status s);

        std::string getId() const;

        bool canDisconnect() const;
        bool toDisconnect() const;

        void setToDisconnect(bool t);

        Session getSession();

    public:
        bool operator<(const Client &b) const;
        bool operator==(const Client &b) const;
    public:
        friend std::ostream &operator<<(std::ostream &os, const Client &c);

    private:
        void purifyMessage(std::string &message) const;


    };

}

#endif //ZAPPY_CLIENT_CLIENT_H
