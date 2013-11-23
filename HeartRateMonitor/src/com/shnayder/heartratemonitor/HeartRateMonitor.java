package com.shnayder.heartratemonitor;

import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.hardware.Camera;
import android.os.Bundle;
import android.util.Log;
import android.widget.FrameLayout;

public class HeartRateMonitor extends Activity {
	public static String HRM_TAG = "HeartRateMonitor";

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
	
	private boolean checkFlashLight(Context context){
		if(context.getPackageManager().hasSystemFeature(PackageManager.FEATURE_CAMERA_FLASH)){
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

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		have_a_Camera = checkCameraHardware(this);
		have_a_Flashlight = checkFlashLight(this);
		if(!have_a_Flashlight)
			Log.e(HRM_TAG, "have no flash light");

		_camera = getCamera();

		if (_camera == null)
			return;

		_cameraPreview = new HeartRateMonitorPreview(this, _camera);
		FrameLayout framePreview = (FrameLayout) findViewById(R.id.cameraPreview);
		framePreview.addView(_cameraPreview);
	}

	@Override
	protected void onPause() {
		super.onPause();
		releaseCamera();
	}
}
