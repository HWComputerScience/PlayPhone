//
//  main.cpp
//  HWConsoleServer
//
//  Created by James Lennon on 10/9/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "PlayPhone/PlayPhone.h"
#include <cstdio>
#include <sstream>
#include <thread>
#include <unistd.h>

#include "Simulator.h"

using namespace rapidjson;

//Value addControl(Document& root, const char* type, int x, int y, int w, int h, int id){
//    Document::AllocatorType& a = root.GetAllocator();
//    
//    Value ctl;
//    ctl.SetObject();
//    ctl.AddMember("type", StringRef(type), a);
//    ctl.AddMember("id", id, a);
//    
//    Value frame;
//    frame.SetObject();
//    frame.AddMember("x", x, a);
//    frame.AddMember("y", y, a);
//    frame.AddMember("w", w, a);
//    frame.AddMember("h", h, a);
//    ctl.AddMember("frame", frame, a);
//    
//    return ctl;
//}

void doServer(){
    using namespace playphone;
    ServerHandler h;
    Server serv(h);
    serv.start();
}

int main(){
    thread t(doServer);
    t.detach();
    simulate();
    
    return 0;
}