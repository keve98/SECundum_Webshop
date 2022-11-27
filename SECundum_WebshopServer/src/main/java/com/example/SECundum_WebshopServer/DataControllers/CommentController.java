package com.example.SECundum_WebshopServer.DataControllers;


import com.example.SECundum_WebshopServer.DataModels.Comment;
import com.example.SECundum_WebshopServer.DataServices.CommentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.concurrent.ExecutionException;

@RestController
public class CommentController {

    public CommentService commentService;

    @Autowired
    public CommentController(CommentService commentService) {
        this.commentService = commentService;
    }

    @PostMapping("/comment/save")
    public ResponseEntity<Comment> saveComment(@RequestBody Comment comment){

        return ResponseEntity.ok(commentService.saveComment(comment));
    }

    @GetMapping("/comment/getAll")
    public ResponseEntity<List<Comment>> getAllComments(@RequestParam String caffName) throws ExecutionException, InterruptedException {
        return ResponseEntity.ok(commentService.getCommentsForCaff(caffName));
    }

    @DeleteMapping("/comment/delete")
    public ResponseEntity<String> deleteComment(@RequestParam String id){
        return ResponseEntity.ok(commentService.deleteComment(id));
    }
}
