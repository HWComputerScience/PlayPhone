package com.hw.playphone.android.model;

import android.os.AsyncTask;
import android.util.Log;

import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * Created by ethan on 10/27/14.
 */

public class NetworkManager {
    static final int start_port = 47810, num_ports = 10;

    static ServerDiscoveryListener listener;

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

                while (!socket.isClosed()) {
                    socket.receive(packet);
                    if (packet.getPort() == 9999) {
                        data = packet.getData();
                        int port = (data[0] & 0xFF) * 256 + (data[1] & 0xFF);

                        Log.d("PlayPhone", "Found a server at: " + packet.getAddress() + ". Using port: " + port);

                        new ConnectTask().execute(packet.getAddress(), port);

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
                GameDesc curGame = new GameDesc();
                InetAddress addr = (InetAddress) params[0];
                Integer port = (Integer) params[1];
                curGame.s = new Socket(addr, port);

                Request r = new Request(0);
                PrintWriter out = new PrintWriter(curGame.s.getOutputStream());
                Scanner in = new Scanner(curGame.s.getInputStream());
                out.print(r);

                curGame.s.close();
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
        public void setGames(ArrayList<GameDesc> games);
    }

    public static class GameDesc {
        public String name, desc;
        public int openslots, filledslots;
        public Socket s;
    }
}
