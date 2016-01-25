package com.example.user.musicplayer;

import android.app.Service;
import android.content.ContentResolver;
import android.content.Intent;
import android.database.Cursor;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.os.Messenger;
import android.provider.MediaStore;

import java.io.IOException;


public class BoundPlayer extends Service {

    private SendParcel parcel;
    private Messenger messenger;
    private Cursor cursor;

    //player
    private MediaPlayer player = new MediaPlayer();;
    private int length;

    //volume
    boolean volumeUp = true;
    double leftVol = 0.5;
    double rightVol = 0.5;

    //queue array
    private int counter = 1;
    private String[] queue = new String[30];

    public static final int PLAY = 0;
    public static final int PAUSE = 1;
    public static final int QUEUE = 2;
    public static final int RESUME = 3;
    public static final int UP = 4;
    public static final int DOWN = 5;
    public static final int NEXT = 6;
    public static final int STOP = 7;

    private class MyHandler extends Handler {
        @Override
        //handle incoming messages
        public void handleMessage(Message message) {
            switch (message.what) {
                case PLAY:
                    parcel = message.getData().getParcelable("id");
                    playSong(parcel.id);
                    break;
                case PAUSE:
                    pauseSong();
                    break;
                case QUEUE:
                    parcel = message.getData().getParcelable("id");
                    queueSong(parcel.id);
                    break;
                case RESUME:
                    resumeSong();
                    break;
                case UP:
                    volume(volumeUp);
                    break;
                case DOWN:
                    volume(!volumeUp);
                    break;
                case NEXT:
                    next();
                    break;
                case STOP:
                    player.stop();
                    player.reset();
                default:
                    super.handleMessage(message);
            }
        }
    }

    //////////////////// media player methods ///////////////////////

    public void playSong(String id){

        //if song is selected for play, delete current position at 0, place this id at 0
        queue[0] = id;

        if(queue[0] != null) {

            //put this in or if play is pressed multiple times it starts at wrong place
            length = player.getCurrentPosition();

            //send broadcast to home page to say that song is playing (and so artwork and title must change)
            Intent intent = new Intent("android.intent.action.MAIN");
            intent.putExtra("playing", queue[0]);
            intent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT|Intent.FLAG_ACTIVITY_NEW_TASK);
            this.sendBroadcast(intent);

            //get data for that song
            String[] projection = new String[]{MediaStore.Audio.Media._ID, MediaStore.Audio.Media.DATA};

            //specify we want the row HAVING the same id
            String selection = MediaStore.Audio.Media._ID + " = " + queue[0];

            //get query results
            ContentResolver cr = getContentResolver();
            Cursor cursor = cr.query(MediaStore.Audio.Media.EXTERNAL_CONTENT_URI, projection, selection, null, null);

            String song = null;

            if (cursor != null) {
                cursor.moveToFirst();

                player.stop();
                player.reset();

                //play song
                try {
                    song = cursor.getString(cursor.getColumnIndex(MediaStore.Audio.Media.DATA));

                    player.setAudioStreamType(AudioManager.STREAM_MUSIC);
                    player.setDataSource(song);
                    player.prepare();
                    player.start();

                } catch (IllegalArgumentException e) {
                    e.printStackTrace();
                } catch (SecurityException e) {
                    e.printStackTrace();
                } catch (IllegalStateException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            //wait for song to finish
             player.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
                public void onCompletion(MediaPlayer mp) {
                    next();
                }

            });
        }

    }

    //queue song
    public void queueSong(String id){
        queue[counter] = id;
        counter++;
    }

    public void pauseSong(){

        player.pause();
        //find out at which position it paused so we can resume there
        length = player.getCurrentPosition();

    }

    public void resumeSong(){
        //resume at last paused position
        player.seekTo(length);
        player.start();
    }

    public void volume(boolean volumeUp){

        //if volume is to be turned up
        if (volumeUp && leftVol <= 1){
            leftVol = leftVol + 0.1;
            rightVol = rightVol + 0.1;
        } else if (leftVol >= 0) { //else turn it down
            leftVol = leftVol - 0.1;
            rightVol = rightVol - 0.1;
        }

        Float left = (float) leftVol;
        Float right = (float) rightVol;
        player.setVolume(left, right);
    }

    public void next(){
        //do this or the next song will play on top of the current on
        player.stop();
        player.reset();

        //shuffle queue along
        for (int i = 0; i < counter; i++) {
            queue[i] = queue[i+1];
        }

        if (counter > 1) {
            counter--;
        }

        playSong(queue[0]);
    }


    ///////////////////////////////// life cycle ////////////////////////
    @Override
    public void onCreate() {

        messenger = new Messenger(new MyHandler());
    }

    @Override
    public IBinder onBind(Intent intent)
    {
        return messenger.getBinder();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {

        throw new RuntimeException("Unable to start service");
    }

    @Override
    public void onDestroy() {
        player.stop();

        super.onDestroy();
    }

    @Override
    public void onRebind(Intent intent) {

        super.onRebind(intent);
    }


    @Override
    public boolean onUnbind(Intent intent) {
        player.stop();
        player.reset();

        if (cursor != null) {
            cursor.close();
        }

        return super.onUnbind(intent);
    }

}

