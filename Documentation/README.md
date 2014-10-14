Documentation
=============

Documentation files go here.

Objects
<game>:{
    "name":<string>,
    "openslots":#,
    "filledslots":#,
    "icon":<base64>,
    "desc":<string>
}
<id>:{
    "phoneID":<string>,
    "firstname":<string>,
    "lastname":<string>,
    "fbuid":<string>,
    "username":<string>
}
<control>:{
    "type":#,
    "frame":{
        "x":#,
        "y":#,
        "w":#,
        "h":#
        (these coordinates are from 0.0 to 1.0)
    },
    "id":#
}
<padconfig>:{
    "bgimg":<base64>,
    "controls":[<control>,<control>,...],

}

Operation 0: Discovery
Request:
{
    "op":0,
    "ts":#,
    "id":<id>,
    "APIVersion":#,
    "capabilities":{
        "resolution":{
            "h":#,
            "w":#
        }
    }
}
Response:
{
    "sts":{
        "code":#,
        "msg":<string>
    },
    "game":<game>,
    "banned":{
        "is":<boolean>,
        "why":<string>
    }
}

Operation 1: Game Refresh
Request:
{
    "op":1,
    "ts":#,
    "game":<game>
}
Response:
std

Operation 2: Join
Request:
{
    "op":2,
    "ts":#
}
Response:
{
    "sts":{
        "code":#,
        "msg":<string>
    },
    "accepted":<boolean>
    "padconfig":<padconfig>
}
