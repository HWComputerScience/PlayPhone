package com.playphone.android.model;

import org.json.JSONException;
import org.json.JSONObject;

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
