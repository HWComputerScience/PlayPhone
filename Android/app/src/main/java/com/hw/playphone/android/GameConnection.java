package com.hw.playphone.android;

import com.hw.playphone.android.model.Request;
import com.hw.playphone.android.model.UserData;

import org.json.JSONObject;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

/**
 * Created by ethan on 10/29/14.
 */
public class GameConnection {
    Socket socket;
    InputStream inputStream;
    OutputStream outputStream;


    public GameConnection(Socket socket) {
       this.socket = socket;
       try {
            inputStream = socket.getInputStream();
            outputStream = socket.getOutputStream();
       } catch (Exception ex) {
            ex.printStackTrace();
       }
    }

    public void sendDiscovery() {
        try {
            Request r = new Request(0);
            JSONObject id = new JSONObject();
            id.put("phoneID", UserData.getValue("phoneID"));
            id.put("firstname", UserData.getValue("firstname"));
            id.put("lastname", UserData.getValue("lastname"));
            id.put("username", UserData.getValue("username"));
            r.data.put("id", id);

            r.data.put("APIVersion", 1);

            outputStream.write(r.toString().getBytes());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
