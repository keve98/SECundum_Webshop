package com.example.SECundum_WebshopServer.DataModels;


import lombok.Getter;
import lombok.Setter;
import java.io.File;
import java.io.InputStream;

@Getter
@Setter
public class CAFF {
    private String content;
    private File caffFile;
    private File image;

    public CAFF(){}

    public CAFF(String content){
        this.content = content;
    }

    public CAFF(String content, File caffFile, File image) {
        this.content = content;
        this.caffFile = caffFile;
        this.image = image;
    }
}
