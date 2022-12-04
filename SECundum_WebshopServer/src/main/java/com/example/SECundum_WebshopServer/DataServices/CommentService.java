package com.example.SECundum_WebshopServer.DataServices;

import com.example.SECundum_WebshopServer.DataModels.Comment;
import com.google.api.core.ApiFuture;
import com.google.cloud.firestore.Firestore;
import com.google.cloud.firestore.QuerySnapshot;
import com.google.cloud.firestore.WriteResult;
import com.google.firebase.cloud.FirestoreClient;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;

@Service
public class CommentService {

    public List<Comment> getCommentsForCaff(String caffName) throws ExecutionException, InterruptedException {
        Firestore dbFireStore = FirestoreClient.getFirestore();
        ApiFuture<QuerySnapshot> future = dbFireStore.collection("comments").whereEqualTo("caff_name", caffName).get();
        Object document = future.get();

        if(document != null){
            List<Comment> commentList =
                    future.get().toObjects(Comment.class);
            return commentList;
        }

        return new ArrayList<>();
    }

    public Comment saveComment(Comment comment){
        Comment newComment = new Comment(comment.getCaff_name(), comment.getComment());
        Firestore dbFireStore = FirestoreClient.getFirestore();
        ApiFuture<WriteResult> collectionsApiFuture = dbFireStore.collection("comments").document(newComment.getId()).set(newComment);
        return newComment;
    }

    public String deleteComment(String id){
        Firestore dbFireStore = FirestoreClient.getFirestore();
        ApiFuture<WriteResult> writeResult = dbFireStore.collection("comments").document(id).delete();
        return "Comment deleted.";
    }

    
}
