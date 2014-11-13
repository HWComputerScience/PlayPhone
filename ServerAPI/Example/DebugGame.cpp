//
//  DebugGame.cpp
//  ServerXcode
//
//  Created by James Lennon on 10/31/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#include "DebugGame.h"

using namespace openpad;

DebugGame::DebugGame(int maxPlayers){
    numPlayers = 0;
    this->maxPlayers = maxPlayers;
}

void DebugGame::onStart(){
    printf("Game started\n");
}

bool DebugGame::canJoin(Client *cli){
    if(cli->clientID->firstname == "Christian"){
        return false;
    }else{
        return true;
    }
}

string DebugGame::whyIsBanned(openpad::Client *cli){
    if(cli->getID().firstname == "Christian"){
        return "Get outta here Christian";
    }
    return "";
}

string DebugGame::getName(){
    return "Debug Game";
}

string DebugGame::getDesc(){
    return "Game program to debug openpad server";
}

string DebugGame::getIconFilePath(){
    return "DebugSmall.png";
}

int DebugGame::getFilledSlots(){
    return numPlayers;
}

int DebugGame::getOpenSlots(){
    return maxPlayers-numPlayers;
}

void DebugGame::onJoin(Client *cli){
    printf("Client joined: %s\n", cli->clientID->username.c_str());
}

PadConfig DebugGame::getDefaultControls(){
    PadConfig conf;
    ButtonControl *btn1 = new ButtonControl(.2, .2, .1, 0, BUTTON_A);
    DPadControl *dpad = new DPadControl(.5, .75, .2, 1);
    
    conf.addControl(btn1);
    conf.addControl(dpad);
    
    return conf;
}

void DebugGame::onDisconnect(Client *cli){
    printf("%s disconnected\n", cli->clientID->username.c_str());
}

void DebugGame::onPadUpdate(Client *cli, PadUpdateObject update){
    //Player controller action
    printf("Player did something with control %d\n", update.controlid);
}