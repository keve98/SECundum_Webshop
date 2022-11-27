package com.example.SECundum_WebshopServer.DataModels;


import lombok.Getter;
import lombok.Setter;

import java.util.concurrent.atomic.AtomicInteger;

@Getter
@Setter
public class Comment {
    private static AtomicInteger ID_GENERATOR = new AtomicInteger(0);

    private String id;
    private String caff_name;
    private String comment;

    public Comment(){}

    public Comment(String caff_name, String comment) {
        this.id = String.valueOf(ID_GENERATOR.getAndIncrement());
        this.caff_name = caff_name;
        this.comment = comment;
    }
}
