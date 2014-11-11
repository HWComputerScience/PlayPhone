# Protocol Documentation

## Overview

Client-server communication is done over a single bidirectional socket.

Request strings (in JSON) are sent across the stream, followed by a single \0 null character.

All requests contain an "op" key.

All responses contain a "sts" key.

Each endpoint *must* send a response for every request, in the order they were received.


## Operations

All operations are request-response pairs.  

Each request will have "op" and "ts" integer fields.  "op" indicates the operation ID, and "ts" indicates the UNIX timestamp of the request.

Each response will have a "sts" dictionary that contains "code" (the integer status code) and "msg" (the string description of the code).


### Discovery (op: 0)

The discovery request is initiated by the client when the socket is first opened.

```
Request:
{
    "op":0,
    "ts":#
    "id":<id>,           /* Contains ID info about the client */
    "APIVersion":#,      /* Indicates the API version */
    "capabilities": {    /* Holds various capabilities of the client */
        "resolution": {  /* Tells the server what resolution the client is */
            "h":#,
            "w":#
        }
    }
}
```

A server responds to the discovery request with:

```
Response:
{
    "sts":{
        "code":#,
        "msg":<string>
    },
    "game":<game>,       /* Information about the game this server belongs to */
    "banned":{           /* Indicates that the player is banned for whatever reason */
        "is":<boolean>,
        "why":<string>
    }
}
```

### Game Refresh (op: 1)

This request is initiated by the server when the state of the game changes.  It should be send to all connected clients, regardless of their join state.

```
Request:
{
    "op":1,
    "ts":#,
    "game":<game>  /* The updated game info */
}
```

The client must send back a standard response.

```
Response:
{
    "sts":{
        "code":#,
        "msg":<string>
    }
}
```

### Join (op: 2)

If the client sees there are open slots in the game, it may initiate a join request to the server.  Note - this method simply requests that a client become a functioning gamepad on the server.

```
Request:
{
    "op":2,
    "ts":#
}
```

The responds to tell the client if the join was accepted, and sends the initial gamepad configuration.

```
Response:
{
    "sts":{
        "code":#,
        "msg":<string>
    },
    "accepted":<boolean>     /* Connection accepted? true or false */
    "padconfig":<padconfig>  /* Initial pad configuration */
}
```

### Disconnect (op: 3) 

This request can be initiated by either client or server to perform a clean disconnect (with a message).  The socket should be expected to close after this command is received.

```
Request: 
{
    "op":3
    "ts":#
    "msg":<String>
}
```

This response is optional, since the socket will likely close after disconnect.

```
Response:
{
    "sts":{
        "code":#,
        "msg":<string>
    }
}
```

### Update Pad Config (op: 4)

This request is initiated by the server any time the pad configuration should be updated.  It allows the gamepad to be dynamically configured while a game is in progress.


```
Request:
{
    "op":4
    "ts":#
    "padconfig":<padconfig>
}
```

```
Response:
{
    "sts":{
        "code":#,
        "msg":<string>
    }
}
```

### Pad State Change (op: 5) 

The client initiates this request any time an action occurs on any interactive part of the gamepad.


```
Request:
{
    "op":5
    "ts":#
    "controlid":#   /* Each control on the pad has a unique ID.  This number reflects the ID of the affected control */
    "action":0,1,2  /* Supported actions: 0: touch up; 1: touch down; 2: touch moved */
    "position": {   /* The relative x,y positions inside the control */
        "x":#
        "y":#
    }
}
```



```
Response:
{
    "sts":{
        "code":#,
        "msg":<string>
    }
}
```


## JSON Objects

These JSON objects are referenced in the above protocol specification.


### game

```
<game>: {             /* Contains game information */
    "name":<string>,  /* Name of the game/server */
    "openslots":#,    /* How many slots are open for new gamepads to join */
    "filledslots":#,  /* How many slots are already occupied by gamepads */
    "icon":<base64>,  /* The base-64 image data (.png) for the game icon */
    "desc":<string>   /* A longer string description of the game */
}
```

```
<id>: {                   /* Phone information */
    "phoneID":<string>,   /* This should be a UUID that is generated once on install and always the same */
    "firstname":<string>, /* User info */
    "lastname":<string>,
    "fbuid":<string>,
    "username":<string>
}
```

```
<control>: {             /* One specific control on the gamepad */    
    "type":#,            /* 0: button; 1: D-pad; 2: analog joystick; 3: static image */
    "frame": {           /* The frame the control sits in */
        "x":#,
        "y":#,
        "w":#,
        "h":#
         /* (these coordinates are from 0.0 to 1.0) */
    },
    "id":#               /* The ID of this control */
    "img":<base64>       /* Optional: an image (.png) to skin the control with */
    /* if this control is a button, it has a "btntype" value (0=>A, 1=>B, 2=>X, 3=>Y) */
}
```

```
<padconfig>:{                              /* The entire pad configuration */
    "bgimg":<base64>,                      /* Background image */
    "controls":[<control>,<control>,...],  /* Array of all controls for the pad */

}
```
