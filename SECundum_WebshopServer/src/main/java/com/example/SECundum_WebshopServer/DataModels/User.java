package com.example.SECundum_WebshopServer.DataModels;

import lombok.Getter;
import lombok.Setter;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;

import javax.management.relation.Role;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

@Getter
@Setter
public class User implements Serializable, UserDetails {

    private static final long serialVersionUID = 5926468583005150707L;


    private String username;
    private String password;
    private String email;

    private String verificationCode;
    private boolean isEnabled;
    private boolean isAdmin;
    private String jwtToken;

    public User(){}

    public User(String username, String password, String email) {
        this.username = username;
        this.password = password;
        this.email = email;
        this.verificationCode = "";
        this.isEnabled = false;
        this.isAdmin = false;
        this.jwtToken = "";
    }

    @Override
    public Collection<? extends GrantedAuthority> getAuthorities() {
        List<GrantedAuthority> list = new ArrayList<GrantedAuthority>();
        if(isAdmin){
            list.add(new SimpleGrantedAuthority("ROLE_ADMIN"));
        }else{
            list.add(new SimpleGrantedAuthority("ROLE_USER"));
        }
        return list;
    }

    @Override
    public boolean isAccountNonExpired() {
        return false;
    }

    @Override
    public boolean isAccountNonLocked() {
        return false;
    }

    @Override
    public boolean isCredentialsNonExpired() {
        return false;
    }
}
