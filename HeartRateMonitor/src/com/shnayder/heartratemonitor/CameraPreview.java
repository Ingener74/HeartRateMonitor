package com.shnayder.heartratemonitor;

import java.io.IOException;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.hardware.Camera;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class CameraPreview extends SurfaceView implements
		SurfaceHolder.Callback {

	private SurfaceHolder _holder;
	private Camera _camera;

	public CameraPreview(Context context, Camera camera) {
		super(context);
		// TODO Auto-generated constructor stub

		_camera = camera;

		_holder = getHolder();
		_holder.addCallback(this);
		_holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {

		if (_holder.getSurface() == null) {
			return;
		}
		try {
			_camera.stopPreview();

		} catch (Exception e) {
			// TODO: handle exception
		}

		try {
			_camera.setPreviewDisplay(_holder);
			_camera.startPreview();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void surfaceCreated(SurfaceHolder holder) {

		try {
			_camera.setPreviewDisplay(_holder);
			_camera.startPreview();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		// TODO Auto-generated method stub

	}
}
