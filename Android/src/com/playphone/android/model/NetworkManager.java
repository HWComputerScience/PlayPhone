package com.playphone.android.model;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Scanner;

import android.os.AsyncTask;
import android.util.Log;

public class NetworkManager {
	static final int start_port = 47810, num_ports = 10;
	
	static ServerDiscoveryListener listener;
	
	public static void findServers(ServerDiscoveryListener listener){
		NetworkManager.listener = listener;
		new DiscoverTask().execute();
	}

	static class DiscoverTask extends AsyncTask<Void, Void, Void>{

		@Override
		protected Void doInBackground(Void... params) {
			try {
				final DatagramSocket udpsock = new DatagramSocket();
				DatagramPacket packet = new DatagramPacket(new byte[]{'a'}, 1, InetAddress.getByName("10.0.1.9"), 9999);
				
				for(int i=0; i<10; i++){
					udpsock.send(packet);
				}
				
				while(udpsock.isConnected()){
					udpsock.receive(packet);
					Log.d("PlayPhone", "found server at: "+ packet.getAddress());
					new ConnectTask().execute(packet.getAddress());
					break;
				}
				udpsock.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
			return null;
		}
		
	}
	
	static class ConnectTask extends AsyncTask<InetAddress, Void, Void>{

		@Override
		protected Void doInBackground(InetAddress... params) {
			for(int i=0; i<num_ports; i++){
				try {
					GameDesc curGame = new GameDesc();
					curGame.s = new Socket(params[0], start_port + i);
					
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
			}
			return null;
		}
		
	}
	
	public static interface ServerDiscoveryListener{
		public void setGames(ArrayList<GameDesc> games);
	}
	
	public static class GameDesc{
		public String name, desc;
		public int openslots,filledslots;
		public Socket s;
	}
}
