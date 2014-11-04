//
//  DebugGame.h
//  ServerXcode
//
//  Created by James Lennon on 10/31/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#ifndef __ServerXcode__DebugGame__
#define __ServerXcode__DebugGame__

#include <stdio.h>
#include "openpad.h"

using namespace openpad;

class DebugGame: public ServerHandler {
    int numPlayers, maxPlayers;
    
public:
    DebugGame(int maxPlayers);
    
    //Override Methods
    void onStart();
    bool canJoin(Client* cli, string& why);
    string getName();
    string getDesc();
    int getFilledSlots();
    int getOpenSlots();
    void onJoin(Client* cli);
    PadConfig getDefaultControls();
    virtual string getIconFilePath();
    void onDisconnect(Client* cli);
    void onPadUpdate(Client* cli, PadUpdateObject update);
};

#endif
