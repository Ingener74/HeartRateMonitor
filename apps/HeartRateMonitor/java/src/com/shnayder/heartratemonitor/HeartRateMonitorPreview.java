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

	/**
	 * Native part
	 */
	static {
		System.loadLibrary("HeartRateMonitor_cpp");
	}
	private native boolean hrmNativeStart();
	private native boolean hrmNativePassImage(int rows, int cols, int type, byte[] data);
	private native void hrmNativeStop();
	/**
	 * end
	 */

	private SurfaceHolder _holder;
	private Camera _camera;
	private ImageView _imageView;
	
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
	private void drawBitmap(final Bitmap bitmap){
		if(bitmap.getWidth() == 0 || bitmap.getHeight() == 0)
			return;
		if(_imageView == null){
			return;
		}
		_imageView.post(new Runnable() {
			
			@Override
			public void run() {
				_imageView.setImageBitmap(bitmap);
			}
		});
	}
	/**********************************************************************
	 * 
	 */
	public HeartRateMonitorPreview(Context context, Camera camera, ImageView imageView) {
		super(context);
		
		_camera = camera;
		
		_holder = getHolder();
		_holder.addCallback(this);
		_holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
		
		_imageView = imageView;
	}
	
	public void start(){
		if(!hrmNativeStart()){
			Log.e(HeartRateMonitor.HRM_TAG, "native service start fail");
		}
		try {
			_camera.setPreviewDisplay(_holder);
			_camera.setPreviewCallback(this);
			_camera.startPreview();
		} catch (IOException e) {
			Log.e(HeartRateMonitor.HRM_TAG, "camera start fail: " + e.getMessage());
		}
		setMinResAndFlashOn();
	}
	public void stop(){
		hrmNativeStop();
		try {
			_holder.removeCallback(this);
			_camera.setPreviewCallback(null);
			_camera.setPreviewDisplay(null);
		} catch (Exception e) {
			Log.e(HeartRateMonitor.HRM_TAG, "camera stop fail: " + e.getMessage());
		}
	}
	
	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		Log.e(HeartRateMonitor.HRM_TAG, "called empty surfaceCreated(SurfaceHolder holder)");
	}
	
	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		Log.e(HeartRateMonitor.HRM_TAG, "called empty surfaceChanged()");
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		Log.e(HeartRateMonitor.HRM_TAG, "called empty surfaceDestroyed(SurfaceHolder holder)");
	}

	@Override
	public void onPreviewFrame(byte[] data, Camera camera) {
		Parameters parm = camera.getParameters();
		Size size = parm.getPreviewSize();
		hrmNativePassImage(size.height, size.width, parm.getPreviewFormat(), data);
	}
}
