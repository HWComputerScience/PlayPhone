//
//  Request.cpp
//  HWConsoleServer
//
//  Created by James Lennon on 10/10/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#include "Request.h"

using namespace rapidjson;
using namespace std;
using namespace playphone;

const char* Serializable::getJSONString(){
    StringBuffer out;
    Writer<StringBuffer> writer(out);
    this->serializeJSON(writer);
    
    return out.GetString();
}

Request::Request(){
    operation = -1;
}

Request::Request(int op){
    Request();
    this->operation = op;
}

void Request::addExtra(playphone::Serializable* val){
    extras.push_back(val);
}

void Request::serializeJSON(Writer<StringBuffer>& w){
    w.StartObject();
    w.Key("op");
    w.Int(operation);
    w.Key("ts");
    w.Int((int)time(0));
    
    for (int i=0; i<extras.size(); i++) {
        extras[i]->serializeJSON(w);
    }
    
    w.EndObject();
}

bool Request::parseJSON(const char *json){
    root = new Document;
    root->Parse(json);
    if(root->HasParseError())return false;
    if(!root->HasMember("op"))return false;
    if(!root->HasMember("ts"))return false;
    
    operation = (*root)["op"].GetInt();
    timestamp = (*root)["ts"].GetInt();
    return true;
}

Response::Response(){
    statusCode = -1;
    statusText = NULL;
}

Response::Response(int code, const char* text){
    Response();
    statusText = text;
    statusCode = code;
}

bool Response::parseJSON(const char *json){
    root = new Document;
    root->Parse(json);
    if(root->HasParseError())return false;
    if(!root->HasMember("sts"))return false;
    Value& sts = (*root)["sts"];
    if(!sts.IsObject())return false;
    if(!sts.HasMember("code"))return false;
    if(!sts.HasMember("text"))return false;
    statusCode = sts["code"].GetInt();
    statusText = sts["text"].GetString();
    return true;
}

void Response::serializeJSON(Writer<StringBuffer> &w){
    w.StartObject();
    w.Key("sts");
    
    w.StartObject();
    w.Key("code");
    w.Int(statusCode);
    w.Key("text");
    w.String(statusText);
    w.EndObject();
    
    w.EndObject();
}