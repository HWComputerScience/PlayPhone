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
    
    class ServerHandler{
    public:
        bool canJoin(Client& cli, string& why);
        const char* getName();
        const char* getDesc();
        int getFilledSlots();
        int getOpenSlots();
    private:
    };
    
}

#endif /* defined(__ServerXcode__ServerHandler__) */
