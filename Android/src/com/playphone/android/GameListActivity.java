package com.playphone.android;

import com.playphone.android.model.NetworkManager;

import android.app.Activity;
import android.os.Bundle;

public class GameListActivity extends Activity {
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		NetworkManager.findServers(null);
	}

}
