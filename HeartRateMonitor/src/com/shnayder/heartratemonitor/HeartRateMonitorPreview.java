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
		System.loadLibrary("HeartRateMonitor");
	}

	private native boolean hrmNativeStart();
	private native void hrmNativeStop();

	private SurfaceHolder _holder;
	private Camera _camera;
	
//	private boolean _cameraIsPresent;
//	
//	private void setFlashOn() {
//		if(_camera == null)
//			return;
//		Parameters camPam = _camera.getParameters();
//
//		camPam.setFlashMode(Camera.Parameters.FLASH_MODE_TORCH);
//
//		int w = -1, h = -1;
//		List<Size> prevSizes = camPam.getSupportedPreviewSizes();
//		for (Size size : prevSizes) {
//			if (w == -1)
//				w = size.width;
//			if (h == -1)
//				h = size.height;
//			if (size.height < h || size.width < w) {
//				w = size.width;
//				h = size.height;
//			}
//		}
//		camPam.setPreviewSize(w, h);
//
//		Log.i(HeartRateMonitor.HRM_TAG, "ps: " + w + " x " + h);
//
//		_camera.setParameters(camPam);
//	}
	
	/**********************************************************************
	 * 
	 */
	public HeartRateMonitorPreview(Context context, Camera camera) {
		super(context);
		
		_camera = camera;
		
		_holder = getHolder();
		_holder.addCallback(this);
		_holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
	}
	
	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		try {
			_camera.setPreviewDisplay(_holder);
			_camera.startPreview();
		} catch (IOException e) {
			Log.e(HeartRateMonitor.HRM_TAG, "camera start preview fail: " + e.getMessage());
		}
	}
	
	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		if(_holder.getSurface() == null){
			return;
		}
		try {
			_camera.stopPreview();
		} catch (Exception e) {
			Log.e(HeartRateMonitor.HRM_TAG, "camera stop preview fail: " + e.getMessage());
		}
		try {
			_camera.setPreviewDisplay(_holder);
			_camera.startPreview();
		} catch (Exception e) {
			Log.e(HeartRateMonitor.HRM_TAG, "camera restart preview fail: " + e.getMessage());
		}
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
	}

	@Override
	public void onPreviewFrame(byte[] data, Camera camera) {
	}
}
