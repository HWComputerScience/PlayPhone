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
    class ServerHandler;
//    class IDObject;
    
    void sendMsg(TCPSocket* sock, Serializable& r);
    
    class Client {
        
    public:
        int socketID;
        TCPSocket* sock;
        Server* serv;
        bool shouldRun;
//        IDObject* clientID:
        
        Client(TCPSocket* sock, int sockID, Server* serv);
        void send(Serializable &s);
        void run();
    private:
        void handleMsg(string msg);
    };
    
    class Server {
        
    public:
        int currentClientID;
        map<int, Client&> clients;
        bool shouldRun;
        
        Server(ServerHandler& handler);
        void start();
        void broadcast(Serializable &s, int except=-1);
        bool send(Serializable& s, int clientID);
        Response handleRequest(Request& r, Client* cli);
        void handleResponse(Response& r, Client* cli);
    private:
        mutex mut;
        ServerHandler& handler;
        
        int getClientID();
        void handleClient(TCPSocket* sock);
        void listenForSockets(TCPServerSocket *serverSock);
    };
    
}
#endif /* defined(__HWConsoleServer__HWPPServer__) */
