package com.hw.playphone.android.model;

        import org.json.JSONObject;

/**
 * Created by ethan on 10/30/14.
 */
public class Response {

    public JSONObject data;

    public Response(int code, String msg) {
        data = new JSONObject();
        try {
            JSONObject obj = new JSONObject();
            obj.put("code", code);
            obj.put("msg", msg);
            data.put("sts", obj);
        } catch (Exception e) {}
    }

    public Response(String json) throws Exception{
        data = new JSONObject(json);

    }
}
