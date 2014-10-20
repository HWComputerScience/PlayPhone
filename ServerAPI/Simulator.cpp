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

void sendBadRequest(){
    Request r;
    sendMsg(sock, r);
}

void sendDiscovReq(){
    Request r(0);
    IDObject id;
    id.firstname = "James";
    id.lastname = "Lennon";
    id.username = "j_lennon";
    Document d;
    Value& obj = r.serializeJSON(d.GetAllocator());
    Value& idval = id.serializeJSON(d.GetAllocator());
    obj.AddMember("id", idval, d.GetAllocator());
    obj.AddMember("APIVersion", 1, d.GetAllocator());
    
    sendMsg(sock, r);
}

void sendGameReq(){
    Request r(1);
    GameObject game;
    game.name = "WOW";
    game.desc = "blah blah blah";
    Document d;
    Value& obj = r.serializeJSON(d.GetAllocator());
    Value& gval = game.serializeJSON(d.GetAllocator());
    obj.AddMember("game", gval, d.GetAllocator());
    
    sendMsg(sock, r);
    
}

void handle(const char* msg, int len){
    mut.lock();
    cout << "simulator got: " << msg << endl;
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
    printf("Simulator connected on port %d\n", currentPort);
    
    thread t(getResponses);
    t.detach();
    
    sendDiscovReq();
    sendGameReq();
    
    sleep(200);
}