package com.playphone.android;

import java.util.UUID;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;

import com.playphone.android.model.UserData;

public class InfoActivity extends Activity {
	
	private String fname, lname, uname, uuid;
	private EditText fnameText, lnameText, unameText;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_info);
		fnameText = (EditText) findViewById(R.id.firstname);
		unameText = (EditText) findViewById(R.id.username);
		lnameText = (EditText) findViewById(R.id.lastname);

		UserData.load();
	}
	
	public void next(View v) {
		fname = fnameText.getText().toString();
		lname = lnameText.getText().toString();
		uname = unameText.getText().toString();
		uuid = UUID.randomUUID().toString();
		Log.d("PlayPhone", "generated UUID: "+uuid);
		UserData.put("firstname", fname);
		UserData.put("lastname", lname);
		UserData.put("username", uname);
		UserData.put("phoneid", uuid);
		
		Intent i = new Intent(this, GameListActivity.class);
		startActivity(i);
	}
}
