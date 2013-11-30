package com.shnayder.heartratemonitor;

import java.io.IOException;
import java.util.List;

import android.content.Context;
import android.content.pm.PackageManager;
import android.hardware.Camera;
import android.hardware.Camera.Parameters;
import android.hardware.Camera.PreviewCallback;
import android.hardware.Camera.Size;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class HeartRateMonitorPreview extends SurfaceView implements
		SurfaceHolder.Callback, PreviewCallback {

	static {
		System.loadLibrary("heartratemonitor");
	}

	private native boolean hrmNativeStart();
	private native void hrmNativeStop();

	private SurfaceHolder _holder;
	
	private Camera _camera;
	private boolean _cameraIsPresent;
	
//	public boolean start() {
//		if(!_cameraIsPresent){
//			Log.e(HeartRateMonitor.HRM_TAG, "have no camera");
//			return false;
//		}
//		
//		Log.i(HeartRateMonitor.HRM_TAG, "preview start");
//		if (_camera == null){
//			Log.e(HeartRateMonitor.HRM_TAG,
//					"preview start fail: camera is null");
//			return false;
//		}
//		
//		if(_holder.getSurface() == null){
//			Log.e(HeartRateMonitor.HRM_TAG,
//					"preview start fail: holder surface is null");
//			return false;
//		}
//		try {
//			_camera.setPreviewDisplay(_holder);
//			_camera.setPreviewCallback(this);
//			setFlashOn();
//			_camera.startPreview();
//
//		} catch (IOException e) {
//			Log.e(HeartRateMonitor.HRM_TAG,
//					"camera start fail: " + e.getMessage());
//			return false;
//		}
//		if(hrmNativeStart() == false){
//			Log.e(HeartRateMonitor.HRM_TAG,
//					"camera start fail: native start false");
//		}
//		return true;
//	}
	
	public void stop(){
		if(_camera != null){
			try {
				_camera.stopPreview();
				
			} catch (Exception e) {
				Log.e(HeartRateMonitor.HRM_TAG,
						"preview stop fail: " + e.getMessage());
			}
		}
	}
	
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

	private boolean cameraStart() {
		try {
			_camera.setPreviewDisplay(_holder);
			_camera.setPreviewCallback(this);
			setFlashOn();
			_camera.startPreview();

		} catch (IOException e) {
			Log.e(HeartRateMonitor.HRM_TAG, "camera start fail: " + e.getMessage());
			return false;
		}
		return true;
	}
	
	private void setFlashOn() {
		if(_camera == null)
			return;
		Parameters camPam = _camera.getParameters();

		camPam.setFlashMode(Camera.Parameters.FLASH_MODE_TORCH);

		int w = -1, h = -1;
		List<Size> prevSizes = camPam.getSupportedPreviewSizes();
		for (Size size : prevSizes) {
			if (w == -1)
				w = size.width;
			if (h == -1)
				h = size.height;
			if (size.height < h || size.width < w) {
				w = size.width;
				h = size.height;
			}
		}
		camPam.setPreviewSize(w, h);

		Log.i(HeartRateMonitor.HRM_TAG, "ps: " + w + " x " + h);

		_camera.setParameters(camPam);
	}

	/**********************************************************************
	 * 
	 */
	public HeartRateMonitorPreview(Context context) {
		super(context);
		
		_cameraIsPresent = checkCameraHardware(context);

		try {
			_camera = Camera.open();
		} catch (Exception e) {
			Log.e(HeartRateMonitor.HRM_TAG,
					"Camera.open(): fail " + e.getMessage());
		}

		_holder = getHolder();
		_holder.addCallback(this);
		_holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
	}
	
	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		Log.i(HeartRateMonitor.HRM_TAG, "HeartRateMonitorPreview -> surfaceCreated");
		star
	}
	
	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		Log.i(HeartRateMonitor.HRM_TAG, "hrm preview changed");
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		Log.i(HeartRateMonitor.HRM_TAG, "HeartRateMonitorPreview -> surfaceDestroyed");
		
		if (_camera == null)
			return;
		_camera.release();
		_camera = null;
	}

	@Override
	public void onPreviewFrame(byte[] data, Camera camera) {
	}
}
