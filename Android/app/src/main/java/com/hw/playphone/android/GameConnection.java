package com.hw.playphone.android;

import android.util.Log;

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
    private Thread thread;


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
            id.put("fbuid", "");
            r.data.put("id", id);

            r.data.put("APIVersion", 1);

            outputStream.write(r.toString().getBytes());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private int strlen(byte[] bytes, int off){
        for(int i = 0; i < bytes.length-off; i++){
            if(bytes[i+off]==0)return i;
        }
        return bytes.length-off;
    }

    private void handleMsg(String msg){
        Log.d("", "received msg: "+msg);
    }

    public void listen() {
        thread = new Thread(new Runnable() {
            @Override
            public void run() {
                byte[] buffer = new byte[1024];
                String cur = "";
                try {
                    while (socket.isConnected()) {
                        int amt = inputStream.read(buffer);

                        int bytesProcessed = 0;
                        do {
                            int length = (int) strlen(buffer, bytesProcessed);
                            cur += new String(buffer, bytesProcessed, length);
                            if(bytesProcessed+length < amt) {
                                handleMsg(cur);
                                cur = "";
                            }
                            bytesProcessed += length + 1;
                        } while (bytesProcessed < amt);
                    }
                } catch (Exception e){
                    e.printStackTrace();
                }
            }
        });
        thread.start();
    }
}