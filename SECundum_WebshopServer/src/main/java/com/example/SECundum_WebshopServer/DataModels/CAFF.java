package com.example.SECundum_WebshopServer.DataModels;


import lombok.Getter;
import lombok.Setter;
import org.springframework.web.multipart.MultipartFile;

import java.awt.*;

@Getter
@Setter
public class CAFF {
    private String content;
    private MultipartFile caffFile;
    private Image image;

    public CAFF(){}

    public CAFF(String content, MultipartFile caffFile, Image image) {
        this.content = content;
        this.caffFile = caffFile;
        this.image = image;
    }
}
