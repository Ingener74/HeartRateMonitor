package com.shnayder.heartratemonitor;

import java.io.IOException;
import java.util.List;

import android.content.Context;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.hardware.Camera;
import android.hardware.Camera.Parameters;
import android.hardware.Camera.PreviewCallback;
import android.hardware.Camera.Size;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.widget.ImageView;

public class HeartRateMonitorPreview extends SurfaceView implements
		SurfaceHolder.Callback, PreviewCallback {

	static {
		System.loadLibrary("HeartRateMonitor_cpp");
	}

	private native boolean hrmNativeStart();

	private native boolean hrmNativePassImage(int rows, int cols, int type,
			byte[] data);

	private native void hrmNativeStop();

	private SurfaceHolder _holder;
	private Camera _camera;
	private ImageView _heartRatePreview;
	private ImageView _cameraPreview;

	private void setMinResAndFlashOn() {
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
		_camera.setParameters(camPam);
	}

	private void drawHeartRate(final Bitmap bitmap) {
		if (bitmap.getWidth() == 0 || bitmap.getHeight() == 0)
			return;
		_heartRatePreview.post(new Runnable() {
			@Override
			public void run() {
				_heartRatePreview.setImageBitmap(bitmap);
			}
		});
	}

	private void drawCameraPreview(final Bitmap bitmap) {
		if (bitmap.getWidth() == 0 || bitmap.getHeight() == 0)
			return;
		_cameraPreview.post(new Runnable() {
			@Override
			public void run() {
				_cameraPreview.setImageBitmap(bitmap);
			}
		});
	}

	/**********************************************************************
	 * 
	 */
	public HeartRateMonitorPreview(Context context, Camera camera,
			ImageView HeartRatePreview, ImageView cameraPreview) {
		super(context);

		_camera = camera;

		_holder = getHolder();
		_holder.addCallback(this);
		_holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);

		_heartRatePreview = HeartRatePreview;
		_cameraPreview = cameraPreview;
	}

	public void start() throws IOException {
		if (!hrmNativeStart()) {
			Log.e(HeartRateMonitor.HRM_TAG, "native service start fail");
		}
		setMinResAndFlashOn();
		_camera.setPreviewDisplay(_holder);
		_camera.setPreviewCallback(this);
		_camera.startPreview();
	}

	public void stop() throws IOException {
		hrmNativeStop();
		_camera.setPreviewCallback(null);
		_camera.setPreviewDisplay(null);
	}

	@Override
	public void surfaceCreated(SurfaceHolder holder) {
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
	}

	@Override
	public void onPreviewFrame(byte[] data, Camera camera) {
		Parameters parm = camera.getParameters();
		Size size = parm.getPreviewSize();
		hrmNativePassImage(size.height, size.width, parm.getPreviewFormat(),
				data);
	}
}
