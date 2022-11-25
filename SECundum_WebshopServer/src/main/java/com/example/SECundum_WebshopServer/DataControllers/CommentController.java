package com.example.SECundum_WebshopServer.DataControllers;


import com.example.SECundum_WebshopServer.DataModels.Comment;
import com.example.SECundum_WebshopServer.DataServices.CommentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.concurrent.ExecutionException;

@RestController
public class CommentController {

    public CommentService commentService;

    @Autowired
    public CommentController(CommentService commentService) {
        this.commentService = commentService;
    }

    @PostMapping("/comment/save")
    public ResponseEntity<?> saveComment(@RequestBody Comment comment){
        return commentService.saveComment(comment);
    }

    @GetMapping("/comment/getAll")
    public ResponseEntity<?> getAllComments(@RequestParam String caffName) throws ExecutionException, InterruptedException {
        return commentService.getCommentsForCaff(caffName);
    }

    @DeleteMapping("/comment/delete")
    public ResponseEntity<?> deleteComment(@RequestParam String id){
        return commentService.deleteComment(id);
    }
}
