#ifndef Request_H
#define Request_H

#include <stdio.h>
#include <string>
#include "openpad.h"
#include "writer.h"
#include "document.h"
#include <vector>

using namespace rapidjson;
using namespace std;

namespace openpad {
    
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
        void set(float x, float y, float w, float h);
        
        double x,y,w,h;
    };
    
    class ControlObject : public Serializable{
    public:
        virtual Value& serializeJSON(Document::AllocatorType& a);
        virtual bool parseJSON(Value& v);
        
        int type;
        FrameObject frame;
        int controlID;
        string img;
    };
    
    class PadConfig : public Serializable{
    public:
        PadConfig();
        PadConfig(const PadConfig& other);
        PadConfig& operator=(const PadConfig& other);
        
        Value& serializeJSON(Document::AllocatorType& a);
        bool parseJSON(Value& v);
        void addControl(ControlObject* c);
        
        vector<ControlObject*> controls;
        string bgimg;
    private:
    };
    
    class PadUpdateObject{
    public:
        bool parseJSON(Value& v);
        
        int controlid,action;
        float x,y;
    };
    
    class ButtonControl : public ControlObject{
    public:
        ButtonControl(float x, float y, float w, int controlid, int btntype);
        virtual Value& serializeJSON(Document::AllocatorType& a);
        
        int btntype;
    };
    
    class DPadControl : public ControlObject{
    public:
        DPadControl(float x, float y, float w, int controlid);
        
    };
    
    class JoystickControl : public ControlObject{
    public:
        JoystickControl(float x, float y, float w, int controlid);
        
    };
}
#endif
