package jp.coe.capp;

import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;

import java.util.Observer;

import jp.coe.capp.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity implements MainActivityHandlers,MainActivityInterface {

    private static final String TAG = "MainActivity";
    private ActivityMainBinding mBinding;
    private long mNativeContext; // ここにC++クラスのポインタアドレスを保持

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        ActivityMainBinding binding = DataBindingUtil.setContentView(this,R.layout.activity_main);
        binding.setHandlers(this);
        init();
    }

    @Override
    public void showDiarog(){
        Log.d(TAG,"showDiarog");

    }

    @Override
    public void connect() {
        //TODO:connectした
        Log.d(TAG,"connect");
        connectCallback();
    }

    @Override
    public void dismiss(){
        Log.d(TAG,"dismiss");

    }

    @Override
    public void playSound(){
        Log.d(TAG,"playSound");

    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native void onClickFromJNI();

    //http://stackoverflow.com/questions/20270120/how-to-implement-the-observer-pattern-in-jni
    public native void init();
    public native void connectCallback();


    @Override
    public void onSampleButtonClick(View view) {
        onClickFromJNI();
    }

    public interface Listener {
        public void eventOccurred();
    }

}
