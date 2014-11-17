//
//  ServerHandler.h
//  OpenPad
//
//  Created by James Lennon on 10/14/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#ifndef __ServerHandler_H__
#define __ServerHandler_H__

#include <stdio.h>
#include "openpad.h"

namespace openpad {
    
    class Client;
    class PadConfig;
    class Server;
    class PadUpdateObject;
    
    class ServerHandler{
    public:
        Server* serv;
        
        virtual void onStart();
        virtual bool canJoin(Client* cli);
        virtual string whyIsBanned(Client* cli);
        virtual string getName();
        virtual string getDesc();
        virtual string getIconFilePath();
        virtual int getFilledSlots();
        virtual int getOpenSlots();
        virtual void onJoin(Client* cli);
        virtual PadConfig getDefaultControls();
        virtual void onDisconnect(Client* cli);
        virtual void onPadUpdate(Client* cli, PadUpdateObject update);
    private:
    };
    
}

#endif /* defined(__ServerXcode__ServerHandler__) */
