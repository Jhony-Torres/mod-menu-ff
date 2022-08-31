package curso.udemy;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.provider.Settings;
import android.widget.Toast;

import curso.udemy.modmenu.FloatingModMenuService;
import curso.udemy.modmenu.Preferences;

public class MainActivity extends Activity {

    public String GameActivity = "com.unity3d.player.UnityPlayerActivity";

    //Load lib
    static {
        // When you change the lib name, change also on Android.mk file
        // Both must have same name
        System.loadLibrary("curso");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Preferences.context = this;
        //To launch mod menu
        Start(this);

        //To load lib only
        //LoadLib(this);

        //To launch game activity
        try {
            //Start service
            MainActivity.this.startActivity(new Intent(MainActivity.this, Class.forName(MainActivity.this.GameActivity)));
        } catch (ClassNotFoundException e) {
            //Remova este comentário se você estiver seguindo o MÉTODO 2 de CHANGING FILES
            Toast.makeText(MainActivity.this, "Erro. A atividade principal do jogo não existe", Toast.LENGTH_LONG).show();
            e.printStackTrace();
            return;
        }
    }

    //Load mod menu
    public static void Start(final Context context) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M && !Settings.canDrawOverlays(context)) {
            Toast.makeText(context, "A permissão de sobreposição é necessária para mostrar o menu mod", Toast.LENGTH_LONG).show();
            Toast.makeText(context, "Reinicie o jogo depois de permitir a permissão", Toast.LENGTH_LONG).show();
            context.startActivity(new Intent("android.settings.action.MANAGE_OVERLAY_PERMISSION",
                    Uri.parse("package:" + context.getPackageName())));
        } else {
            final Handler handler = new Handler();
            handler.postDelayed(new Runnable() {
                @Override
                public void run() {
                        context.startService(new Intent(context, FloatingModMenuService.class));
                }
            }, 500);
        }
    }

    //Call toast only without mod menu
    public static void LoadLibOnly(final Context context) {
        new Handler().postDelayed(new Runnable() {
            public void run() {
                NativeToast.makeText(context.getApplicationContext(), 0);
            }
        }, 500);
    }
}
