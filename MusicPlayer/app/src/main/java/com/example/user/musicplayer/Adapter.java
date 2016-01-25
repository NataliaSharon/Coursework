package com.example.user.musicplayer;

import android.app.Activity;
import android.content.ComponentName;
import android.content.ContentUris;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.os.IBinder;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;
import android.provider.MediaStore;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.SimpleCursorAdapter;
import android.widget.TextView;

public class Adapter extends SimpleCursorAdapter {

    public Context context;
    public Cursor cursor;
    public int layout;
    public String[] selection;
    public int[] resources;

    public View convertView;

    private ImageButton playButton;
    private ImageButton queueButton;
    private TextView songName;
    private TextView artist;
    private ImageView albumArt;

    public Messenger messenger;
    static IBinder thisService;

    public Adapter(Context context, int layout, Cursor cursor, String[] selection, int[] resources, int flags) {
        super(context, layout, cursor, selection, resources, flags);
        this.context = context;
        this.layout = layout;
        this.cursor = cursor;
        this.resources = resources;
        this.selection = selection;

    }

    @Override
    public View newView(Context context, Cursor cursor, ViewGroup parent) {
        //inflates list
        LayoutInflater inflater = (LayoutInflater) context.getSystemService(Activity.LAYOUT_INFLATER_SERVICE);
        convertView = inflater.inflate(layout,parent,false);

        songName = (TextView) convertView.findViewById(resources[0]);
        artist = (TextView) convertView.findViewById(resources[1]);
        albumArt = (ImageView) convertView.findViewById(resources[2]);

        //bind service
        context.bindService(new Intent(this.context, BoundPlayer.class), serviceConnection, Context.BIND_AUTO_CREATE);

        return convertView;
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

    @Override
    public void bindView(View view, final Context context, final Cursor cursor) {
        super.bindView(view, context, cursor);



        final Context thisContext = context;

        playButton = (ImageButton)  convertView.findViewById(R.id.listPlay);
        queueButton = (ImageButton) convertView.findViewById(R.id.listQueue);

        //set artist and text
        songName.setText(cursor.getString(cursor.getColumnIndex(selection[0])));
        artist.setText(cursor.getString(cursor.getColumnIndex(selection[1])));


        //artwork
        final Uri ART_CONTENT_URI = Uri.parse("content://media/external/audio/albumart");

        try {
            Uri albumArtUri = ContentUris.withAppendedId(ART_CONTENT_URI, cursor.getLong(cursor.getColumnIndex(selection[2])));
            Bitmap songCoverArt = MediaStore.Images.Media.getBitmap(context.getContentResolver(), albumArtUri);
            albumArt.setImageBitmap(songCoverArt);
        }catch (Exception e){

        }

        /////////////  note that I recieved help on this by asking a question on stack overflow
        ////// BUT THE CODE IS MINE AND I WROTE IT MYSELF!!!!!!!!!!!!!!!!!!!!!!!!!!!
        ///////however there is now a copy of it on stack overflow with someone elses recommendation of the tag below
        //////// http://stackoverflow.com/questions/33746010/android-studio-list-view-image-button-returning-wrong-positions/33746312?noredirect=1#comment55272175_33746312
        ////////// just letting you know in case it comes up during plagiarising checks.

        playButton.setTag(cursor.getString(cursor.getColumnIndex(selection[3])));
        //if play button is selected
        playButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                //must send intent for home to open before sending data to bound player
                //as reciever only works when activity is open
                //and we need the home to recieve the broadcast so that the UI changes

                //get id of song based on that position
                String stringID = (String) v.getTag();
                //create bundle to send
                Bundle bundle = new Bundle();
                //add position to bundle
                bundle.putString("ID", stringID);
                Intent intent = new Intent(thisContext, Home.class);
                intent.putExtras(bundle);
                //flag to allow this out of activty context
                intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                thisContext.startActivity(intent);

            }
        });


        //on queue, send message to home, add to array
        //when song is finished, service plays from array
        //service must send message to home to change the UI to fit song
        queueButton.setTag(cursor.getString(cursor.getColumnIndex(selection[3])));
        queueButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                //get id of song based on that position
                String stringID = (String) v.getTag();

                //send it to binder to be placed in queue
                Message message = Message.obtain(null, BoundPlayer.QUEUE, 0, 0);
                SendParcel parcel = new SendParcel();
                parcel.id = stringID;

                Bundle bundle = new Bundle();
                bundle.putParcelable("id", (SendParcel) parcel);
                message.setData(bundle);

                try {
                    messenger.send(message);

                } catch (RemoteException e) {
                    e.printStackTrace();
                }

            }
        });
    }

}