package com.example.user.musicplayer;

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.ContentResolver;
import android.content.ContentUris;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.IBinder;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;
import android.provider.MediaStore;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

///////////////////ALL ICONS ARE TAKEN FROM THE OFFICIAL ANDROID MATERIAL ICONS WEBSITE
////////////////// https://www.google.com/design/icons/#ic_home

public class Home extends AppCompatActivity {

    //views
    private TextView nameText;
    private TextView artistText;
    private ImageView albumArt;

    public Messenger messenger;
    private Cursor cursor;
    static IBinder thisService;

    private String IDRecieved = "";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home);

        //bind service
        this.bindService(new Intent(this, BoundPlayer.class), serviceConnection, Context.BIND_AUTO_CREATE);
    }

    //////////////////////////// SERVICE ////////////////////////

    private ServiceConnection serviceConnection = new ServiceConnection()
    {

        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            thisService = service;
            messenger = new Messenger(service);
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            messenger = null;
        }
    };

    //this runs if button for selecting music is pressed
    public void intentList (View v){
        //start activity to present list of songs
        Intent intent = new Intent(Home.this, SongList.class);
        Home.this.startActivity(intent);
    }


    //setting visibility of information to visible when songs start to play
    public void setVisibility(){
        TextView text1 = (TextView) findViewById(R.id.text1);
        TextView text3 = (TextView) findViewById(R.id.text3);

        nameText.setVisibility(View.VISIBLE);
        artistText.setVisibility(View.VISIBLE);
        albumArt.setVisibility(View.VISIBLE);
        text1.setVisibility(View.VISIBLE);
        text3.setVisibility(View.VISIBLE);
    }

///////////////////////MEDIA PLAYER BUTTONS//////////////////////

    public void play(String songID){

        //send a message to the service with the id of the song to play
        Message message = Message.obtain(null, BoundPlayer.PLAY, 0, 0);
        SendParcel parcel = new SendParcel();
        parcel.id = songID;

        Bundle bundle = new Bundle();
        bundle.putParcelable("id", (SendParcel) parcel);
        message.setData(bundle);

        try {
            messenger.send(message);
        } catch (RemoteException e) {
            e.printStackTrace();
        }

    }

    //play button has been pressed after pause has - resume song playing
    public void resume(View v){
        Message message = Message.obtain(null, BoundPlayer.RESUME, 0, 0);
        try {
            messenger.send(message);
        } catch (RemoteException e) {
            e.printStackTrace();
        }


    }

    //pause music
    public void pause(View v){
        Message message = Message.obtain(null, BoundPlayer.PAUSE, 0, 0);
        try {
            messenger.send(message);
        } catch (RemoteException e) {
            e.printStackTrace();
        }


    }

    //play next song in queue
    public void next(View v){
        Message message = Message.obtain(null, BoundPlayer.NEXT, 0, 0);
        try {
            messenger.send(message);
        } catch (RemoteException e) {
            e.printStackTrace();
        }

    }

    //volume up
    public void up (View v){
        Message message = Message.obtain(null, BoundPlayer.UP, 0, 0);
        try {
            messenger.send(message);
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }

    //volume down
    public void down (View v){
        Message message = Message.obtain(null, BoundPlayer.DOWN, 0, 0);
        try {
            messenger.send(message);
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }

    //update the album artwork and song playing based on what id is being played
    public void changeUI(String songID){

        String[] projection = new String[]{ MediaStore.Audio.Media._ID,
                MediaStore.Audio.Media.TITLE,
                MediaStore.Audio.Media.ARTIST,
                MediaStore.Audio.Media.ALBUM_ID};

        //specify we want the row HAVING the same id
        String selection = MediaStore.Audio.Media._ID + " = " + songID;

        ContentResolver cr = getContentResolver();
        cursor = cr.query(MediaStore.Audio.Media.EXTERNAL_CONTENT_URI, projection, selection, null, null);

        //set artist, song name and album art
        nameText = (TextView) findViewById(R.id.text2);
        artistText = (TextView) findViewById(R.id.text4);
        albumArt = (ImageView) findViewById(R.id.albumArt);

        if (cursor != null) {
            cursor.moveToFirst();
            nameText.setText(cursor.getString(cursor.getColumnIndex(MediaStore.Audio.Media.TITLE)));
            artistText.setText(cursor.getString(cursor.getColumnIndex(MediaStore.Audio.Media.ARTIST)));

            //artwork
            //NOTE I USED AN ANSWER FROM STACK OVERFLOW TO ASSIST ME WITH CONVERTING THE ALBUM ART ID INTO A BITMAP BELOW
            ///// http://stackoverflow.com/questions/20089317/how-to-display-album-art
            final Uri ART_CONTENT_URI = Uri.parse("content://media/external/audio/albumart");

            try {
                Uri albumArtUri = ContentUris.withAppendedId(ART_CONTENT_URI, cursor.getLong(cursor.getColumnIndex(MediaStore.Audio.Media.ALBUM_ID)));
                Bitmap songCoverArt = MediaStore.Images.Media.getBitmap(this.getContentResolver(), albumArtUri);
                albumArt.setImageBitmap(songCoverArt);
            } catch (Exception e) {
                //if no artwork was found then ensure no artwork is displayed
                albumArt.setImageResource(android.R.color.transparent);
            }
        }

        setVisibility();
    }

    //note that when broadcast message is receieved, it means that a new song is playing
    //hence we know to update the UI
    private BroadcastReceiver receiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            IDRecieved = intent.getStringExtra("playing");
            changeUI(IDRecieved);
        }
    };

    //////////////////////// LIFE CYCLE //////////////////////////////

    @Override
    protected void onDestroy() {
        super.onDestroy();

        Message message = Message.obtain(null, BoundPlayer.STOP, 0, 0);
        try {
            messenger.send(message);
        } catch (RemoteException e) {
            e.printStackTrace();
        }

        //unbind from service when activiy is destroyed
        if(serviceConnection!=null) {
            unbindService(serviceConnection);
            serviceConnection = null;
        }

        if (cursor != null) {
            cursor.close();
        }

    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        //incoming intent means user pressed play on a song
        setIntent(intent);

        messenger = new Messenger(thisService);

        //handle intent id from songList
        Bundle extras = getIntent().getExtras();
        if (extras != null) {
            String IDRecieved = extras.getString("ID");
            play(IDRecieved);
        }
    }

    @Override
    protected void onPause() {
        super.onPause();

        //unregister the receiver
        this.unregisterReceiver(this.receiver);
    }

    @Override
    protected void onResume() {
        super.onResume();

        //initiate broadcast receiever
        IntentFilter intentFilter = new IntentFilter(
                "android.intent.action.MAIN");

        //registering our receiver
        this.registerReceiver(receiver, intentFilter);

        //update UI on return
        if (IDRecieved != "") {
            changeUI(IDRecieved);
        }

    }

    @Override
    protected void onStart() {
        super.onStart();
    }

    @Override
    protected void onStop() {
        super.onStop();
    }
}
