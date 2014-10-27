package com.playphone.android.model;

import org.json.JSONException;
import org.json.JSONObject;

public class UserData {
	private static JSONObject data;
	
	public static void load(){
		if(data == null){
			data = new JSONObject();
		}
	}
	
	public static String getValue(String key){
		try {
			return data.getString(key);
		} catch (JSONException e) {
			e.printStackTrace();
			return null;
		}
	}
	
	public static void put(String key, String val){
		try {
			data.put(key, val);
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
}
