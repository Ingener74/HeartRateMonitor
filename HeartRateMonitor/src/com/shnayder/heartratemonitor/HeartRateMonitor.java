package com.shnayder.heartratemonitor;

import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.hardware.Camera;
import android.os.Bundle;
import android.util.Log;
import android.widget.FrameLayout;

public class HeartRateMonitor extends Activity {
	public static String HRM_TAG = "Heart Rate Monitor Java";

	private boolean have_a_Camera = false;
	private Camera _camera = null;
	private HeartRateMonitorPreview _cameraPreview = null;

	private boolean have_a_Flashlight = false;

	private boolean checkCameraHardware(Context context) {
		if (!context.getPackageManager().hasSystemFeature(
				PackageManager.FEATURE_CAMERA)) {
			return false;
		}
		return true;
	}

	private boolean checkFlashLight(Context context) {
		if (context.getPackageManager().hasSystemFeature(
				PackageManager.FEATURE_CAMERA_FLASH)) {
			return true;
		}
		return false;
	}

	public static Camera getCamera() {
		Camera c = null;
		try {
			c = Camera.open();

		} catch (Exception e) {
			// TODO: handle exception
		}
		return c;
	}

	private void releaseCamera() {
		if (_camera == null)
			return;
		_camera.release();
		_camera = null;
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		
		Log.i(HRM_TAG, "onCreate");

		have_a_Camera = checkCameraHardware(this);
		have_a_Flashlight = checkFlashLight(this);
//		if (!have_a_Flashlight)
//			Log.e(HRM_TAG, "have no flash light");
//
//		_camera = getCamera();
//
//		if (_camera == null)
//			return;
//
//		_cameraPreview = new HeartRateMonitorPreview(this, _camera);
//		FrameLayout framePreview = (FrameLayout) findViewById(R.id.cameraPreview);
//		framePreview.addView(_cameraPreview);
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
//		releaseCamera();
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
