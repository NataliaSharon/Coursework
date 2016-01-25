package com.example.user.musicplayer;

import android.os.Parcel;
import android.os.Parcelable;

public class SendParcel implements Parcelable {

    String id;

    public SendParcel(Parcel parcel)
    {
        readFromParcel(parcel);
    }

    public SendParcel() {

    }

    @Override
    public int describeContents()
    {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel out, int flags)
    {
        out.writeString(this.id);

    }

    private void readFromParcel(Parcel parcel)
    {

        this.id = parcel.readString();

    }

    public static final Parcelable.Creator<SendParcel> CREATOR = new Parcelable.Creator<SendParcel>() {

        public SendParcel createFromParcel(Parcel parcel) {
            return new SendParcel(parcel);
        }

        public SendParcel[] newArray(int size) {
            return new SendParcel[size];
        }

    };

}
