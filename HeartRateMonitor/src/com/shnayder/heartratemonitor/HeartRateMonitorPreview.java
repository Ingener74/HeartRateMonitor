package com.shnayder.heartratemonitor;

import java.io.IOException;
import java.util.List;

import android.content.Context;
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
		System.load("heartratemonitor");
	}
	native boolean hrmNativeStart();
	native void    hrmNativeStop();

	private SurfaceHolder _holder;
	private Camera _camera;

	public HeartRateMonitorPreview(Context context, Camera camera) {
		super(context);

		_camera = camera;

		_holder = getHolder();
		_holder.addCallback(this);
		_holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
	}

	private void setFlashOn() {
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

	private boolean cameraStart() {
		try {
			_camera.setPreviewDisplay(_holder);
			_camera.setPreviewCallback(this);
			setFlashOn();
			_camera.startPreview();

		} catch (IOException e) {
			e.printStackTrace();
			return false;
		}
		return true;
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		Log.i(HeartRateMonitor.HRM_TAG, "hrm preview changed");

		if (_holder.getSurface() == null) {
			return;
		}
		try {
			_camera.stopPreview();

		} catch (Exception e) {
			Log.e(HeartRateMonitor.HRM_TAG, "camera stop preview exception: "
					+ e.getMessage());
		}
		cameraStart();
	}

	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		Log.i(HeartRateMonitor.HRM_TAG, "hrm preview created");
		cameraStart();
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		Log.i(HeartRateMonitor.HRM_TAG, "hrm preview destroyed");
	}

	@Override
	public void onPreviewFrame(byte[] data, Camera camera) {
	}
}
