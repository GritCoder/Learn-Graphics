package com.example.studyandroides;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.widget.Toast;

public class MainActivity extends Activity {

    private GLSurfaceView glSurfaceView;
    private boolean rendererSet = false;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
//        当 Android 程序被编译，会自动生成一个 R 类，其中包含了所有 res/ 目录下资源的
//        ID，如layout布局文件，字符串string键值，drawable图片等资源的ID等。
//        在写java代码需要用这些资源的时候，你可以使用 R
//        setContentView(R.layout.activity_main);
        glSurfaceView = new GLSurfaceView(this);

        final ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        final ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();
        final boolean supportsEs2 = configurationInfo.reqGlEsVersion >= 0x20000;
        if (supportsEs2){
            // Request an OpenGL ES 2.0 compatible context.
            glSurfaceView.setEGLContextClientVersion(2);
            // Assign our renderer.
            glSurfaceView.setRenderer((GLSurfaceView.Renderer) new OurRenderer(this));
            rendererSet = true;
        }
        else {
            Toast.makeText(this, "This device does not support OpenGL ES 2.0.",
                    Toast.LENGTH_LONG).show();
            return;
        }
        setContentView(glSurfaceView);
    }
    @Override
    protected void onPause() {
        super.onPause();
        if (rendererSet) {
            glSurfaceView.onPause();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (rendererSet) {
            glSurfaceView.onResume();
        }
    }
}