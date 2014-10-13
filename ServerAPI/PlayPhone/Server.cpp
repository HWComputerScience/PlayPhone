//
//  HWServer.c
//  HWConsoleServer
//
//  Created by James Lennon on 10/9/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#include "Server.h"
#include <thread>
#include <sstream>
#include <stdio.h>
#include <cstdio>

using namespace playphone;

void playphone::sendMsg(TCPSocket* sock, Serializable& r){
    const char* msg = r.getJSONString();
    int len = strlen(msg);
    
    char head[2];
    head[0] = len%255;
    head[1] = len/255;
    sock->send(head, 2);
    sock->send(msg, len);
}

string playphone::recvMsg(TCPSocket* sock){
    string msg;
    char buf[BUFFER_LENGTH];
    if(sock->recv(buf, 2)<=0)return "";
    int len = buf[0]+buf[1]*255;
    int curBytes = 0;
    while(curBytes<len){
        int amt = sock->recv(buf, min(BUFFER_LENGTH,len-curBytes));
        if(amt<=0)return "";
        msg.append(buf, amt);
        curBytes += amt;
    }
    return msg;
}

Server::Server(){
    currentClientID = 0;
    this->shouldRun = true;
}

void Server::start(){
    TCPServerSocket* serverSock = nullptr;
    unsigned short currentPort = START_PORT;
    while(serverSock==nullptr){
        try {
            //See if currentPort is in use
            serverSock = new TCPServerSocket("0.0.0.0", currentPort);
            break;
        } catch (SocketException ex) {
            printf("Port %d in use\n", currentPort);
            currentPort++;
        }
    }
    printf("Successfully connected to port %d\n", currentPort);
    listenForSockets(serverSock);
    
//    thread listenThread(&Server::listenForSockets, this, serverSock);
//    listenThread.detach();
}

void Server::listenForSockets(TCPServerSocket *serverSock){
    while (shouldRun) {
        //Accept new client, spawn thread to handle it
        TCPSocket *sock = serverSock->accept();
        thread t(&Server::handleClient, this, sock);
        t.detach();
    }
    delete serverSock;
    serverSock = NULL;
}

int Server::getClientID(){
    mut.lock();
    int val = currentClientID++;
    mut.unlock();
    return val;
}

void Server::handleClient(TCPSocket* sock){
    Client cli(sock, getClientID(), this);
    clients.insert(std::pair<int,Client&>(cli.clientID, cli));
    cli.run();
}

bool Server::send(Serializable &s, int clientID){
    map<int, Client&>::iterator it = clients.find(clientID);
    if(it!=clients.end()){
        it->second.send(s);
        return true;
    }
    return false;
}

void Server::broadcast(Serializable &s, int except){
    for(map<int, Client&>::iterator it = clients.begin(); it != clients.end(); ++it){
        if(it->first != except){
            it->second.send(s);
        }
    }
}

Response Server::handleRequest(playphone::Request &r, Client* cli){
    //handle requests here
    printf("received operation %d\n", r.operation);
    
    Response resp(200, "OK");
    return resp;
}

void Server::handleResponse(playphone::Response &r, Client* cli){
    //handle responses here
    printf("received a response\n");
}

Client::Client(TCPSocket* sock, int id, Server* serv){
    this->clientID = id;
    this->sock = sock;
    this->serv = serv;
    shouldRun = true;
}

void Client::send(playphone::Serializable &s){
    sendMsg(sock, s);
}

void Client::run(){
    //TODO: confirm buffer length
    char input[BUFFER_LENGTH];
    
    while (shouldRun) {
        string in = recvMsg(sock);
        if(in==""){
            //client disconnected
            break;
        }
        printf("server received: %s\n", in.c_str());
        
        Request req;
        Response resp;
        if(req.parseJSON(in.c_str())){
            Response resp = serv->handleRequest(req, this);
            sendMsg(sock, resp);
        }else if(resp.parseJSON(in.c_str())){
            serv->handleResponse(resp, this);
        }else{
            Response resp(404,"bad json");
            sendMsg(sock, resp);
        }
    }
    printf("client disconnected\n");
    serv->clients.erase(serv->clients.find(clientID));
    delete sock;
    sock=NULL;
}