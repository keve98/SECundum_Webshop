package com.example.SECundum_WebshopServer.DataControllers;

import com.example.SECundum_WebshopServer.DataModels.User;
import com.example.SECundum_WebshopServer.DataServices.UserService;
import com.example.SECundum_WebshopServer.RandomString;
import com.example.SECundum_WebshopServer.Security.Config.JwtTokenUtil;
import com.example.SECundum_WebshopServer.Security.model.JwtResponse;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Lazy;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.concurrent.ExecutionException;

@RestController
@CrossOrigin(origins = "http://localhost:4200")
public class UserController {

    public UserService userService;

    @Autowired
    private JwtTokenUtil jwtTokenUtil;

    @Autowired
    public UserController(UserService userService) {
        this.userService = userService;
    }

    @PostMapping("/user/save")
    public ResponseEntity<?> saveUser(@RequestBody User user) throws Exception {

        String username = user.getUsername();
        String password = user.getPassword();

        User userObj = null;

        if(username != null && password != null){
            userObj = userService.getUser(username);
        }

        if(userObj != null){
            throw new Exception("User with name '" + username +"' already exists!");
        }

        User newUserEntity = new User(username, password, user.getEmail());

        String randomCode = RandomString.make(64);
        newUserEntity.setVerificationCode(randomCode);

        userService.sendVerificationEmail(newUserEntity);

        return userService.saveUser(newUserEntity);
    }

    @GetMapping("/user/get")
    public User getUser(@RequestParam String username) throws Exception {

        User user = userService.getUser(username);
        if(user == null){
            throw new Exception("User not found.");
        }
        return user;
    }

    @GetMapping("/user/verify")
    public String verifyUser(@RequestParam String code) throws Exception {
        User user = userService.getUserByVerificationCode(code);
        if(user == null){
            throw new Exception("Invalid verification code");
        }
        user.setEnabled(true);
        userService.updateUser(user);
        return "Successfully verification for user: " + user.getUsername();

    }

    @PutMapping("/user/update")
    public String getUser(@RequestBody User user) throws InterruptedException, ExecutionException{
        return userService.updateUser(user);
    }

    @PostMapping("/user/login")
    public ResponseEntity<?> loginUser(@RequestBody User user) throws Exception {
        User loggedInUser = userService.login(user);
        final String token = jwtTokenUtil.generateToken(loggedInUser);
        loggedInUser.setJwtToken(token);
        userService.updateUser(loggedInUser);
        return ResponseEntity.ok(new JwtResponse(token));
    }
}