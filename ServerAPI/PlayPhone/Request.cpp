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

const char* playphone::getStringFromJSON(Value& v){
    StringBuffer out;
    Writer<StringBuffer> writer(out);
    v.Accept(writer);
    
    return out.GetString();
}

const char* Serializable::getJSONString(){
    StringBuffer out;
    Writer<StringBuffer> writer(out);
    if(!hasSerialized){
        Document d;
        this->serializeJSON(d.GetAllocator());
        hasSerialized = true;
    }
    JSONvalue.Accept(writer);
    
    return out.GetString();
}

Request::Request(){
    operation = -1;
}

Request::Request(int op){
    Request();
    this->operation = op;
}

Value& Request::serializeJSON(Document::AllocatorType& a){
    hasSerialized = true;
    JSONvalue.SetObject();
    JSONvalue.AddMember("op", operation, a);
    JSONvalue.AddMember("ts", (int)time(0), a);
    return JSONvalue;
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
}

Response::Response(int code, const char* text): statusMsg(text), statusCode(code){
    Response();
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
    statusMsg = sts["msg"].GetString();
    return true;
}

Value& Response::serializeJSON(Document::AllocatorType &a){
    hasSerialized = true;
    Value sts;
    JSONvalue.SetObject();
    
    sts.SetObject();
    sts.AddMember("code", statusCode, a);
    sts.AddMember("msg", statusMsg, a);
    
    JSONvalue.AddMember("sts", sts, a);
    return JSONvalue;
}

IDObject::IDObject(): phoneid(""), firstname(""), lastname(""), username(""),fbuid("") {}

Value& IDObject::serializeJSON(Document::AllocatorType &a){
    hasSerialized = true;
    JSONvalue.SetObject();
    JSONvalue.AddMember("phoneID", phoneid, a);
    JSONvalue.AddMember("firstname", firstname, a);
    JSONvalue.AddMember("lastname", lastname, a);
    JSONvalue.AddMember("username", username, a);
    JSONvalue.AddMember("fbuid", fbuid, a);
    
    return JSONvalue;
}

bool IDObject::parseJSON(Value& v){
    if(!v.HasMember("phoneID")&&v["phoneID"].IsString())return false;
    if(!v.HasMember("firstname")&&v["firstname"].IsString())return false;
    if(!v.HasMember("lastname")&&v["lastname"].IsString())return false;
    if(!v.HasMember("username")&&v["username"].IsString())return false;
    if(!v.HasMember("fbuid")&&v["fbuid"].IsString())return false;
    
    phoneid = v["phoneID"].GetString();
    firstname = v["firstname"].GetString();
    lastname = v["lastname"].GetString();
    fbuid = v["fbuid"].GetString();
    username = v["username"].GetString();
    return true;
}

GameObject::GameObject():openslots(0),filledslots(0){}

Value& GameObject::serializeJSON(Document::AllocatorType &a){
    hasSerialized = true;
    JSONvalue.SetObject();
    JSONvalue.AddMember("name", name, a);
    JSONvalue.AddMember("openslots", openslots, a);
    JSONvalue.AddMember("filledslots", filledslots, a);
    JSONvalue.AddMember("icon", icon, a);
    JSONvalue.AddMember("desc", desc, a);
    
    return JSONvalue;
}

bool GameObject::parseJSON(Value &v){
    try {
        name = v["name"].GetString();
        openslots = v["openslots"].GetInt();
        filledslots = v["filledslots"].GetInt();
        icon = v["icon"].GetString();
        desc = v["desc"].GetString();
        
        return true;
    } catch (exception e) {
        return false;
    }
}

bool FrameObject::parseJSON(Value &v){
    try {
        x = v["x"].GetDouble();
        y = v["y"].GetDouble();
        w = v["w"].GetDouble();
        h = v["h"].GetDouble();
        return true;
    } catch (exception ex) {
        return false;
    }
}

Value& FrameObject::serializeJSON(Document::AllocatorType &a){
    JSONvalue.SetObject();
    JSONvalue.AddMember("x", x, a);
    JSONvalue.AddMember("y", y, a);
    JSONvalue.AddMember("w", w, a);
    JSONvalue.AddMember("h", h, a);
    
    return JSONvalue;
}

bool ControlObject::parseJSON(Value &v){
    try {
        type = v["type"].GetInt();
        controlID = v["type"].GetInt();
        img = v["img"].GetString();
        if(!frame.parseJSON(v["frame"]))return false;
        return true;
    } catch (exception ex) {
        return false;
    }
}

Value& ControlObject::serializeJSON(Document::AllocatorType &a){
    JSONvalue.SetObject();
    JSONvalue.AddMember("type", type, a);
    
    Value& fr = frame.serializeJSON(a);
    JSONvalue.AddMember("frame", fr, a);
    JSONvalue.AddMember("id", controlID, a);
    if(img.length()>0){
        JSONvalue.AddMember("img", img, a);
    }
    
    return JSONvalue;
}

Value& PadConfig::serializeJSON(Document::AllocatorType &a){
    JSONvalue.SetObject();
    JSONvalue.AddMember("bgimg", bgimg, a);
    
    Value ctrls;
    ctrls.SetArray();
    for(int i=0; i<controls.size(); i++){
        ctrls.PushBack(controls[i]->serializeJSON(a), a);
    }
    JSONvalue.AddMember("controls", ctrls, a);
    
    return JSONvalue;
}

bool PadUpdateObject::parseJSON(Value &v){
    try {
        action = v["action"].GetInt();
        controlid = v["controlid"].GetInt();
        Value& pos = v["position"];
        x = pos["x"].GetInt();
        y = pos["y"].GetInt();
        
        return true;
    } catch (exception ex) {
        return false;
    }
}

ButtonControl::ButtonControl(){
    this->type = BUTTON;
}

DPadControl::DPadControl(){
    this->type = DPAD;
}

JoystickControl::JoystickControl(){
    this->type = JOYSTICK;
}