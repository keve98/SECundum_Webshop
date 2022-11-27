package com.example.SECundum_WebshopServer.DataModels;


import lombok.Getter;
import lombok.Setter;
import java.io.File;

@Getter
@Setter
public class CAFF {
    private String content;
    private File caffFile;

    public CAFF(){}

    public CAFF(String content){
        this.content = content;
    }

}
