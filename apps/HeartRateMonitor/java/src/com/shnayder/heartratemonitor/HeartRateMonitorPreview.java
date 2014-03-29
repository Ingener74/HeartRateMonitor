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
	private native boolean hrmNativePassImage(int rows, int cols, int type, byte[] data);
	private native void hrmNativeStop();

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
//		_outputBitmap = Bitmap.createBitmap(0, 0, Bitmap.Config.ARGB_8888);
	}
	
	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		
		if(!hrmNativeStart()){
			Log.e(HeartRateMonitor.HRM_TAG, "native service start fail");
		}
		try {
			_camera.setPreviewDisplay(_holder);
			_camera.setPreviewCallback(this);
			_camera.startPreview();
		} catch (IOException e) {
			Log.e(HeartRateMonitor.HRM_TAG, "camera start preview fail: " + e.getMessage());
		}
		setMinResAndFlashOn();
	}
	
	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		
		hrmNativeStop();
		
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
			_camera.setPreviewCallback(this);
			_camera.startPreview();
		} catch (Exception e) {
			Log.e(HeartRateMonitor.HRM_TAG, "camera restart preview fail: " + e.getMessage());
		}
		
		setMinResAndFlashOn();
		
		if(!hrmNativeStart()){
			Log.e(HeartRateMonitor.HRM_TAG, "native service restart fail");
		}
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		hrmNativeStop();
		try {
			_camera.setPreviewCallback(null);
			_camera.stopPreview();
		} catch (Exception e) {
			Log.e(HeartRateMonitor.HRM_TAG, "camera destroy preview fail: " + e.getMessage());
		}
		_camera.release();
	}

	@Override
	public void onPreviewFrame(byte[] data, Camera camera) {
		Parameters parm = camera.getParameters();
		Size size = parm.getPreviewSize();
		hrmNativePassImage(size.height, size.width, parm.getPreviewFormat(), data);
	}
}
