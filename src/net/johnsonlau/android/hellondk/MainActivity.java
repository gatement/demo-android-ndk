package net.johnsonlau.android.hellondk;

import android.app.Activity;
import android.widget.TextView;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.view.View.OnClickListener;
import android.view.View;

public class MainActivity extends Activity
{
    public native String myStr();
    static 
	{
        System.loadLibrary("hellondk");
    }

	private Button btnClick = null;
	private TextView tv = null;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        tv = (TextView)this.findViewById(R.id.tvMsg);
		btnClick = (Button) this.findViewById(R.id.btn_click);
        btnClick.setOnClickListener(new OnClickListener() {
			
			public void onClick(View v) {
				Log.i("JNIMsg", "start calling myStr");
				String val = myStr();
				Log.i("JNIMsg", "myStr returns: " + val);
				tv.setText(val);
			}
		});
    }
}
