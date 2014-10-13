//
//  HWPPServer.h
//  HWConsoleServer
//
//  Created by James Lennon on 10/9/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#ifndef Server_H
#define Server_H

#include "PracticalSocket.h"
#include "PlayPhone.h"
#include <mutex>
#include <map>


namespace playphone {
    
    class Client;
    class Server;
    class Serializable;
    class Request;
    class Response;
    
    void sendMsg(TCPSocket* sock, Serializable& r);
    string recvMsg(TCPSocket* sock);
    
    class Client {
        
    public:
        int clientID;
        TCPSocket* sock;
        Server* serv;
        bool shouldRun;
        
        Client(TCPSocket* sock, int id, Server* serv);
        void send(Serializable &s);
        void run();
    private:
        
    };
    
    class Server {
        
    public:
        int currentClientID;
        map<int, Client&> clients;
        bool shouldRun;
        
        Server();
        void start();
        void broadcast(Serializable &s, int except=-1);
        bool send(Serializable& s, int clientID);
        Response handleRequest(Request& r, Client* cli);
        void handleResponse(Response& r, Client* cli);
    private:
        mutex mut;
        
        int getClientID();
        void handleClient(TCPSocket* sock);
        void listenForSockets(TCPServerSocket *serverSock);
    };
    
}
#endif /* defined(__HWConsoleServer__HWPPServer__) */
