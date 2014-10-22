//
//  ServerHandler.h
//  ServerXcode
//
//  Created by James Lennon on 10/14/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#ifndef __ServerXcode__ServerHandler__
#define __ServerXcode__ServerHandler__

#include <stdio.h>
#include "PlayPhone.h"

namespace playphone {
    
    class Client;
    class PadConfig;
    class Server;
    class PadUpdateObject;
    
    class ServerHandler{
    public:
        Server* serv;
        
        virtual void onStart();
        virtual bool canJoin(Client* cli, string& why);
        virtual string getName();
        virtual string getDesc();
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
