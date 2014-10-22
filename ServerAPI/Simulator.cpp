//
//  Simulator.cpp
//  HWConsoleServer
//
//  Created by James Lennon on 10/10/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#include "Simulator.h"
#include "PlayPhone.h"
#include "rapidjson.h"
#include "document.h"
#include "writer.h"

#include <unistd.h>
#include <thread>
#include <iostream>

using namespace playphone;

TCPSocket *sock;
char buf[1024];
mutex mut;
IDObject id1, id2;

void sendBadRequest(){
    Request r;
    sendMsg(sock, r);
}

void sendDiscovReq(IDObject& id){
    Request r(0);
    Document d;
    Value& obj = r.serializeJSON(d.GetAllocator());
    Value& idval = id.serializeJSON(d.GetAllocator());
    obj.AddMember("id", idval, d.GetAllocator());
    obj.AddMember("APIVersion", 1, d.GetAllocator());
    
    sendMsg(sock, r);
}

void sendJoinReq(){
    Request r(2);
    sendMsg(sock, r);
}

void sendDisconnectReq(){
    Request r(3);
    sendMsg(sock, r);
}

void handle(const char* msg, int len){
    mut.lock();
    if(PP_DEBUG)cout << "simulator got: " << msg << endl;
    mut.unlock();
}

void getResponses(){
    string msg;
    while (true) {
        int amt = sock->recv(buf, BUFFER_LENGTH-1);
        buf[amt] = 0;
        
        int bytesProcessed = 0;
        do {
            int len = (int)strlen(buf+bytesProcessed);
            msg.append(buf+bytesProcessed, len);
            if(bytesProcessed+len<amt){
                handle(msg.c_str(), msg.length());
                msg = "";
            }
            bytesProcessed+=len+1;
        } while (bytesProcessed<amt);
    }

}

void simulate(){
    sleep(3);
    unsigned short currentPort = START_PORT;
    while (true) {
        try {
            sock = new TCPSocket("0.0.0.0", currentPort);
            break;
        } catch (SocketException ex) {
            currentPort++;
        }
    }
    if(PP_DEBUG)printf("Simulator connected on port %d\n", currentPort);
    
    thread t(getResponses);
    t.detach();
    
    id1.firstname = "James";
    id1.lastname = "Lennon";
    id1.username = "j_lennon";
    id1.phoneid = "a";
    sendDiscovReq(id1);
    sendJoinReq();
    sendDisconnectReq();
    
    sleep(2);
}