//
//  ServerHandler.cpp
//  OpenPad
//
//  Created by James Lennon on 10/14/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#include "ServerHandler.h"

using namespace openpad;

void ServerHandler::onStart(){}

bool ServerHandler::canJoin(Client *cli, string &why){
    return true;
}

string ServerHandler::getName(){
    return "";
}

string ServerHandler::getDesc(){
    return "";
}

int ServerHandler::getFilledSlots(){
    return 0;
}

int ServerHandler::getOpenSlots(){
    return 0;
}

void ServerHandler::onJoin(Client *cli){}

PadConfig ServerHandler::getDefaultControls(){ return PadConfig::PadConfig(); }

void ServerHandler::onDisconnect(Client *cli){}

void ServerHandler::onPadUpdate(Client *cli, PadUpdateObject update){}

