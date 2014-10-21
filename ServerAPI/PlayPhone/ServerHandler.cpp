//
//  ServerHandler.cpp
//  ServerXcode
//
//  Created by James Lennon on 10/14/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#include "ServerHandler.h"
using namespace playphone;

bool ServerHandler::canJoin(playphone::Client *cli, string &why){
    return true;
}

const char* ServerHandler::getName(){
    return "";
}

const char* ServerHandler::getDesc(){
    return "";
}

int ServerHandler::getFilledSlots(){
    return 0;
}

int ServerHandler::getOpenSlots(){
    return 0;
}

void ServerHandler::onJoin(playphone::Client *cli){}

PadConfig ServerHandler::getDefaultControls(){ return PadConfig::PadConfig(); }

void ServerHandler::onDisconnect(playphone::Client *cli){}

void ServerHandler::onPadUpdate(playphone::Client *cli, playphone::PadUpdateObject update){}

