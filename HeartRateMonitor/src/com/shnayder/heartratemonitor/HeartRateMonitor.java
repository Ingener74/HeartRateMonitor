package com.shnayder.heartratemonitor;

import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.hardware.Camera;
import android.os.Bundle;
import android.widget.FrameLayout;

public class HeartRateMonitor extends Activity
{
	public String HRM_TAG = "HeartRateMonitor";
	
	private boolean hasCamera = false;
	private Camera _camera = null;
	private CameraPreview _cameraPreview = null;
	
	private boolean checkCameraHardware(Context context){
		if(!context.getPackageManager().hasSystemFeature(PackageManager.FEATURE_CAMERA)){
			return false;
		}
		return true;
	}

	public static Camera getCamera(){
		Camera c = null;
		try {
			c = Camera.open();
			
		} catch (Exception e) {
			// TODO: handle exception
		}
		return c;
	}
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        hasCamera = checkCameraHardware(getBaseContext());
        
        _camera = getCamera();
        
        if(_camera == null)
        	return;
        
        _cameraPreview = new CameraPreview(this, _camera);
        FrameLayout framePreview = (FrameLayout)findViewById(R.id.cameraPreview);
        framePreview.addView(_cameraPreview);
    }
}
