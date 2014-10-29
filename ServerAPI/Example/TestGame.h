//
//  TestGame.h
//  ServerXcode
//
//  Created by James Lennon on 10/21/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#ifndef __ServerXcode__TestGame__
#define __ServerXcode__TestGame__

#include <stdio.h>
#include "PlayPhone.h"

using namespace playphone;

class Player {
public:
    Client* cli;
    
};

class TestGame : public ServerHandler {
    
public:
    TestGame();
    void setup();
    void startGame();
    
    void onStart();
    bool canJoin(Client* cli, string& why);
    string getName();
    string getDesc();
    int getFilledSlots();
    int getOpenSlots();
    void onJoin(Client* cli);
    PadConfig getDefaultControls();
    void onDisconnect(Client* cli);
    void onPadUpdate(Client* cli, PadUpdateObject update);
private:
    void printLobby();
    void startTurn();
    void printBoard();
    void doTurn(int loc, int player);
    
    int slots;
    bool hasStarted;
    map<string, Player> players;
    int board[3][3];
    int curturn;
};

#endif /* defined(__ServerXcode__TestGame__) */
