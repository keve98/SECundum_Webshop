package com.example.SECundum_WebshopServer.DataServices;

import com.example.SECundum_WebshopServer.DataModels.CAFF;
import com.example.SECundum_WebshopServer.DataModels.User;
import com.google.api.core.ApiFuture;
import com.google.cloud.firestore.*;
import com.google.firebase.cloud.FirestoreClient;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpServletRequest;
import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.concurrent.ExecutionException;

@Service
public class CaffService {

    @Autowired
    private HttpServletRequest request;

    public List<CAFF> getAllCaff() throws ExecutionException, InterruptedException {
        Firestore dbFireStore = FirestoreClient.getFirestore();
        ApiFuture<QuerySnapshot> future = dbFireStore.collection("caffs").get();
        Object document = future.get();

        if(document != null){
            List<CAFF> caffList =
                    future.get().toObjects(CAFF.class);
            return caffList;
        }
        return null;

    }

    public CAFF getById(String id) throws ExecutionException, InterruptedException {
        Firestore dbFireStore = FirestoreClient.getFirestore();
        DocumentReference documentReference = dbFireStore.collection("caffs").document(id);
        ApiFuture<DocumentSnapshot> future = documentReference.get();
        DocumentSnapshot document = future.get();
        CAFF caff;
        if(document.exists()){
            caff = document.toObject(CAFF.class);
            return caff;
        }
        return null;

    }

    public CAFF downloadCaff(String id) throws ExecutionException, InterruptedException {
        CAFF caff = getById(id);
        deleteCaff(id);
        return caff;
    }

    public String saveCaff(CAFF caff) throws ExecutionException, InterruptedException {
        Firestore dbFireStore = FirestoreClient.getFirestore();
        ApiFuture<WriteResult> collectionsApiFuture = dbFireStore.collection("caffs").document(caff.getId()).set(caff);
        return collectionsApiFuture.get().getUpdateTime().toString();

    }

    public void deleteCaff(String id){
        Firestore dbFireStore = FirestoreClient.getFirestore();
        ApiFuture<WriteResult> writeResult = dbFireStore.collection("caffs").document(id).delete();
    }

    public String storeFile(MultipartFile file) throws IOException {

        String uploadsDir = "/uploads/";
        String realPathtoUploads =  request.getServletContext().getRealPath(uploadsDir);
        if(! new File(realPathtoUploads).exists())
        {
            new File(realPathtoUploads).mkdir();
        }



        String orgName = file.getOriginalFilename();
        String filePath = realPathtoUploads + orgName;
        File dest = new File(filePath);
        file.transferTo(dest);

        return "redirect:/";
    }
}
