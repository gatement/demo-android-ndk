package net.johnsonlau.android.hellondk;

import android.widget.Toast;
import android.util.Log;

public class TestProvider {

	public static String getTime() {
		Log.i("JNIMsg", "getTime(Java): " + "1");
		return String.valueOf(System.currentTimeMillis());
	}

	public void sayHello(String msg) {
		Log.i("JNIMsg", "sayHello(Java): " + msg);
	}
}
