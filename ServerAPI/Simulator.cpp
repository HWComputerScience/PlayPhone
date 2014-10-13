//
//  Simulator.cpp
//  HWConsoleServer
//
//  Created by James Lennon on 10/10/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#include "Simulator.h"
#include "PlayPhone.h"
#include "PracticalSocket.h"
#include "rapidjson.h"
#include "document.h"
#include "writer.h"

#include <unistd.h>

using namespace playphone;

TCPSocket *sock;
char buf[1024];

class myextra : public Serializable{
    
public:
    void serializeJSON(Writer<StringBuffer> &w){
        w.Key("extra");
        w.StartObject();
        w.Key("score");
        w.Int(1000);
        w.EndObject();
    }
};

void sendInfoRequest(){
    using namespace rapidjson;
    Request req(0);
    myextra m;
    req.addExtra(&m);
    sendMsg(sock, req);
}

void sendBadRequest(){
    Request r;
    sendMsg(sock, r);
}

void sendResponse1(){
    Response r(200, "OK");
    sendMsg(sock, r);
}

void getResponse(){
    string r = recvMsg(sock);
    if(r=="")return;
    printf("simulator: %s\n", r.c_str());
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
    
    sendBadRequest();
    getResponse();
    sendInfoRequest();
    getResponse();
    
    sendResponse1();
    
    sleep(200);
}