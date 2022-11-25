package com.example.SECundum_WebshopServer.DataServices;


import com.example.SECundum_WebshopServer.DataModels.User;
import com.google.api.core.ApiFuture;
import com.google.cloud.firestore.*;
import com.google.firebase.cloud.FirestoreClient;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.mail.javamail.JavaMailSender;
import org.springframework.mail.javamail.MimeMessageHelper;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;

import javax.mail.MessagingException;
import javax.mail.internet.MimeMessage;
import java.io.UnsupportedEncodingException;
import java.util.List;
import java.util.concurrent.ExecutionException;

@Service
public class UserService implements UserDetailsService {
    private BCryptPasswordEncoder bCryptPasswordEncoder;

    @Autowired
    private JavaMailSender mailSender;

    @Autowired
    public UserService(BCryptPasswordEncoder bCryptPasswordEncoder){
        this.bCryptPasswordEncoder = bCryptPasswordEncoder;
    }

    public User login(User u) throws Exception {
        if(u.getUsername() == null){
            throw new Exception("Given username is null.");
        }


        String username = u.getUsername();

        if(u.getPassword() == null){
            throw new Exception("Given password for username: "+ username +" is null.");
        }

        User user = getUser(username);

        if(user == null){
            throw new Exception("Cannot find user with username: " + username);
        }

        if(user.isEnabled() == false){
            throw new Exception("Account is not verified for username: " + username);
        }

        if(bCryptPasswordEncoder.matches(u.getPassword(), user.getPassword())) {
            return user;
        }else{
            throw new Exception("Invalid password for username: " + username);
        }
    }

    public ResponseEntity<?> saveUser(User user) throws ExecutionException, InterruptedException {
        User user_tmp = getUser(user.getUsername());
        if(user_tmp == null) {
            user.setPassword(bCryptPasswordEncoder.encode(user.getPassword()));
            Firestore dbFireStore = FirestoreClient.getFirestore();
            ApiFuture<WriteResult> collectionsApiFuture = dbFireStore.collection("users").document(user.getUsername()).set(user);
            return ResponseEntity.ok(user);
        }
        return (ResponseEntity<?>) ResponseEntity.notFound();
    }

    public User getUser(String username) throws ExecutionException, InterruptedException {
        Firestore dbFireStore = FirestoreClient.getFirestore();
        DocumentReference documentReference = dbFireStore.collection("users").document(username);
        ApiFuture<DocumentSnapshot> future = documentReference.get();
        DocumentSnapshot document = future.get();
        User user;
        if(document.exists()){
            user = document.toObject(User.class);
            return user;
        }
        return null;
    }

    public String updateUser(User user) throws ExecutionException, InterruptedException {
        Firestore dbFireStore = FirestoreClient.getFirestore();
        ApiFuture<WriteResult> collectionsApiFuture = dbFireStore.collection("users").document(user.getUsername()).set(user);
        return collectionsApiFuture.get().getUpdateTime().toString();
    }

    public User getUserByVerificationCode(String code) throws ExecutionException, InterruptedException {
        Firestore dbFireStore = FirestoreClient.getFirestore();
        ApiFuture<QuerySnapshot> future = dbFireStore.collection("users").whereEqualTo("verificationCode", code).get();
        Object document = future.get();

        User user;
        if(document != null){
            List<User> userList =
                    future.get().toObjects(User.class);
            user = userList.get(0);
            return user;
        }

        return null;

    }

    public ResponseEntity<?> getUserByToken(String code) throws ExecutionException, InterruptedException {
        Firestore dbFireStore = FirestoreClient.getFirestore();
        ApiFuture<QuerySnapshot> future = dbFireStore.collection("users").whereEqualTo("jwtToken", code).get();
        Object document = future.get();

        User user;
        if(document != null){
            List<User> userList =
                    future.get().toObjects(User.class);
            user = userList.get(0);
            return ResponseEntity.ok(user);
        }

        return (ResponseEntity<?>) ResponseEntity.notFound();
    }

    public void sendVerificationEmail(User user) throws MessagingException, UnsupportedEncodingException {
        String toAddress = user.getEmail();
        String fromAddress = "secsecundumundum@gmail.com";
        String senderName = "SECundum Webshop";
        String subject = "Verify your email address";


        MimeMessage message = mailSender.createMimeMessage();
        MimeMessageHelper helper = new MimeMessageHelper(message);

        helper.setFrom(fromAddress, senderName);
        helper.setTo(toAddress);
        helper.setSubject(subject);


        String verifyURL = "http://localhost:8080/" + "user/verify?code=" + user.getVerificationCode();

        String content = "Dear "+user.getUsername()+",<br><br>"
                + "Please click the link below to verify your registration:<br>"
                +"<a href=\""+verifyURL+"\">Verify now</a>"
                + "<br><br>Thank you,<br>"
                + "SECundum Team";


        helper.setText(content, true);

        mailSender.send(message);


    }

    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        UserDetails u = null;
        try {
            u = getUser(username);
        } catch (ExecutionException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return u;
    }
}
