#ifndef Request_H
#define Request_H

#include <stdio.h>
#include <string>
#include "PlayPhone.h"
#include "writer.h"
#include "document.h"

using namespace rapidjson;
using namespace std;

namespace playphone {
    
    const char* getStringFromJSON(Value& v);
    
    class Serializable {
        
    public:
        virtual Value& serializeJSON(Document::AllocatorType& a)=0;
        const char* getJSONString();
        
        Value JSONvalue;
        bool hasSerialized=false;
    };
    
    class Request : public Serializable{
        
    public:
        int operation;
        int timestamp;
        Document *root;
        
        Request();
        Request(int op);
        bool parseJSON(const char* json);
        Value& serializeJSON(Document::AllocatorType& a);
    private:
    };
    
    class Response : public Serializable{
        
    public:
        int statusCode;
        string statusMsg;
        Document* root;
        
        Response();
        Response(int code, const char* text);
        bool parseJSON(const char* json);
        Value& serializeJSON(Document::AllocatorType& a);
    private:
    };
    
    class IDObject : public Serializable{
    public:
        IDObject();
        Value& serializeJSON(Document::AllocatorType& a);
        bool parseJSON(Value& v);
        
        string phoneid;
        string firstname;
        string lastname;
        string username;
        string fbuid;
    };
    
    class GameObject : public Serializable{
    public:
        GameObject();
        Value& serializeJSON(Document::AllocatorType& a);
        bool parseJSON(Value& v);
        
        string name;
        int openslots, filledslots;
        string icon, desc;
    };
    
    class FrameObject : public Serializable{
    public:
        Value& serializeJSON(Document::AllocatorType& a);
        bool parseJSON(Value& v);
        
        int x,y,w,h;
    };
}
#endif
