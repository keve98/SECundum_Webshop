package com.example.SECundum_WebshopServer.DataModels;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class User {
    private String username;
    private String password;

    private String email;
    private String verificationCode;
    private boolean isEnabled;

    private boolean isAdmin;

    public User(){}

    public User(String username, String password, String email) {
        this.username = username;
        this.password = password;
        this.email = email;
        this.verificationCode = "";
        this.isEnabled = false;
        this.isAdmin = false;
    }
}
