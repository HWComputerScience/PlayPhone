#ifndef Request_H
#define Request_H

#include <stdio.h>
#include <string>
#include "PlayPhone.h"
#include "writer.h"
#include "document.h"
#include <vector>

using namespace rapidjson;
using namespace std;

namespace playphone {
    
    class Serializable {
        
    public:
        virtual void serializeJSON(Writer<StringBuffer>& w)=0;
        const char* getJSONString();
    };
    
    class Request : public Serializable{
        
    public:
        int operation;
        int timestamp;
        Document *root;
        
        Request();
        Request(int op);
        bool parseJSON(const char* json);
        void addExtra(Serializable* val);
        void serializeJSON(Writer<StringBuffer>& w);
    private:
        vector<Serializable*> extras;
    };
    
    class Response : public Serializable{
        
    public:
        int statusCode;
        const char* statusText;
        Document* root;
        
        Response();
        Response(int code, const char* text);
        bool parseJSON(const char* json);
        void serializeJSON(Writer<StringBuffer>& w);
    };
}
#endif
