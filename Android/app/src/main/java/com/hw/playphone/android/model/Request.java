package com.hw.playphone.android.model;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by ethan on 10/27/14.
 */
public class Request {
    public JSONObject data;

    public Request(int op){
        try {
            data.put("op", op);
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    public String toString(){
        return data.toString() + (char)0;
    }
}
