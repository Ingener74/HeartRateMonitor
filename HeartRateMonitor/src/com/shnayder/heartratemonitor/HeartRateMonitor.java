package com.shnayder.heartratemonitor;

//import android.R;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Bitmap.Config;
import android.hardware.Camera;
import android.os.Bundle;
import android.util.Log;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.widget.FrameLayout;
import android.widget.ImageView;

public class HeartRateMonitor extends Activity {
	public static String HRM_TAG = "Heart Rate Monitor Java";

	private HeartRateMonitorPreview _cameraPreview = null;
	private FrameLayout _previewFrameLayout = null;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		Log.i(HRM_TAG, "onCreate");
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		_cameraPreview = new HeartRateMonitorPreview(this);
		_previewFrameLayout = (FrameLayout)findViewById(R.id.previewFrame);
		_previewFrameLayout.addView(_cameraPreview);
	}

	@Override
	protected void onStart() {
		Log.i(HRM_TAG, "onStart");
		super.onStart();
	}

	@Override
	protected void onRestart() {
		Log.i(HRM_TAG, "onRestart");
		super.onRestart();
	}

	@Override
	protected void onResume() {
		Log.i(HRM_TAG, "onResume");
		super.onResume();
	}

	@Override
	protected void onPause() {
		Log.i(HRM_TAG, "onPause");
		super.onPause();
	}

	@Override
	protected void onStop() {
		Log.i(HRM_TAG, "onStop");
		super.onStop();
	}

	@Override
	protected void onDestroy() {
		Log.i(HRM_TAG, "onDestroy");
		super.onDestroy();
	}
}
