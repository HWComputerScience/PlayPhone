package com.hw.playphone.android.model;

import android.os.AsyncTask;
import android.util.Log;

import com.hw.playphone.android.GameConnection;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashSet;

/**
 * Created by ethan on 10/27/14.
 */

public class NetworkManager {
    static final int start_port = 47810, num_ports = 10;

    static ServerDiscoveryListener listener;
    static HashSet<String> hosts = new HashSet<String>();

    public static void findServers(ServerDiscoveryListener listener) {
        NetworkManager.listener = listener;
        new DiscoverTask().execute();
    }

    static class DiscoverTask extends AsyncTask<Void, Void, Void> {

        @Override
        protected Void doInBackground(Void... params) {
            try {
                final DatagramSocket socket = new DatagramSocket();
                socket.setBroadcast(true);
                byte[] data = new byte['a'];
                DatagramPacket packet = new DatagramPacket(data, data.length,
                        InetAddress.getByName("255.255.255.255"), 9999);

                for (int i = 0; i < 10; i++) {
                    socket.send(packet);
                }

                while (true) {
                    socket.receive(packet);
                    if (packet.getPort() == 9999) {
                        data = packet.getData();
                        int port = (data[0] & 0xFF) * 256 + (data[1] & 0xFF);

                        String addr = packet.getAddress().toString() + ":" + port;
                        if(!hosts.contains(addr)) {
                            new ConnectTask().execute(packet.getAddress(), port);
                            hosts.add(addr);
                        }
                        Log.d("PlayPhone", "Found a server at: " + addr);
                    }
                    break;
                }
                socket.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
            return null;
        }

    }

    static class ConnectTask extends AsyncTask<Object, Void, Void> {

        @Override
        protected Void doInBackground(Object... params) {
            try {
                InetAddress addr = (InetAddress) params[0];
                Integer port = (Integer) params[1];
                GameConnection gc = new GameConnection(new Socket(addr, port));
                gc.sendDiscovery();
            } catch (Exception e) {
                try {
                } catch (Exception e1) {
                    e1.printStackTrace();
                }
                e.printStackTrace();
            }
            return null;
        }

    }

    public static interface ServerDiscoveryListener {
        public void setGames(ArrayList<GameConnection> games);
    }
}
