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

bool DebugGame::canJoin(Client *cli, string &why){
    if(cli->clientID->firstname == "Christian"){
        why = "Get outta here Christian";
        return false;
    }else{
        return true;
    }
}

string DebugGame::getName(){
    return "Debug Game";
}

string DebugGame::getDesc(){
    return "Game program to debug openpad server";
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
    ButtonControl *btn1 = new ButtonControl(.5, .5, .25, 0, BUTTON_A);
    DPadControl *dpad = new DPadControl(0, 0, .2, 1);
    
    conf.controls.push_back(btn1);
    conf.controls.push_back(dpad);
    
    return conf;
}

void DebugGame::onDisconnect(Client *cli){
    printf("%s disconnected\n", cli->clientID->username.c_str());
}

void DebugGame::onPadUpdate(Client *cli, PadUpdateObject update){
    //Player controller action
    printf("Player did something with controll %d\n", update.controlid);
}