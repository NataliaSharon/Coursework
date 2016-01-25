package com.example.user.musicplayer;

import android.content.ContentResolver;
import android.content.Context;
import android.os.Environment;
import android.database.Cursor;
import android.provider.MediaStore;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.*;

public class SongList extends AppCompatActivity {

    private ListView view;
    private Context context;

    private String sortOrder;
    private String[] projection;
    private String[] selection;
    private int[] resources;
    private Cursor cursor;
    private ContentResolver cr;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_song_list);

        //find view of list
        view = (ListView) findViewById(R.id.songList);
        context = getApplicationContext();

        readAllMusic();

    }

    public void readAllMusic() {

        //get external storage state to check if media is available
        if(Environment.MEDIA_MOUNTED.equals(Environment.getExternalStorageState()) || Environment.MEDIA_MOUNTED_READ_ONLY.equals(Environment.getExternalStorageState())) {

            projection = new String[]{MediaStore.Audio.Media._ID,
                    MediaStore.Audio.Media.TITLE,
                    MediaStore.Audio.Media.ARTIST,
                    MediaStore.Audio.Media.ALBUM_ID};


            selection = new String[]{
                    MediaStore.Audio.Media.TITLE,
                    MediaStore.Audio.Media.ARTIST,
                    MediaStore.Audio.Media.ALBUM_ID,
                    MediaStore.Audio.Media._ID};


            resources = new int[]{R.id.text1, R.id.text2, R.id.albumArt};

            cr = getContentResolver();

            //default sort
            onSortSongClick(view.findViewById(R.id.sortSong));
        } else {
            ImageView noSongsImage = (ImageView) findViewById(R.id.noSongs);
            noSongsImage.setVisibility(View.VISIBLE);
            TextView noSongsText = (TextView) findViewById(R.id.text);
            noSongsText.setVisibility(View.VISIBLE);
        }

    }

    //if sort settings are changed, change the cursor order and update the list
    public void onSortArtistClick(View view){

        sortOrder = MediaStore.Audio.Media.ARTIST + " COLLATE NOCASE";
        cursor = cr.query(MediaStore.Audio.Media.EXTERNAL_CONTENT_URI, projection, null, null, sortOrder);

        adapt();

    }

    //default sort
    public void onSortSongClick(View view){

        sortOrder = MediaStore.Audio.Media.TITLE + " COLLATE NOCASE";
        cursor = cr.query(MediaStore.Audio.Media.EXTERNAL_CONTENT_URI, projection, null, null, sortOrder);

        cursor.moveToFirst();
        //THESE ARE RETURNING JUST FINE
        while(!cursor.isLast()) {
            Log.d("THEIDIS: ", cursor.getString(cursor.getColumnIndex(MediaStore.Audio.Media._ID)));
            cursor.moveToNext();
        }

        adapt();

    }

    public void adapt(){
        //place data into list using adapter
        Adapter adapter = new Adapter(context, R.layout.song_list_item, cursor, selection, resources, 0);

        //place adapted list into view
        view.setAdapter(adapter);

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        cursor.close();
    }

}

