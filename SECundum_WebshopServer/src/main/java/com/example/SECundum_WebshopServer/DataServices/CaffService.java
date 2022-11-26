package com.example.SECundum_WebshopServer.DataServices;

import com.example.SECundum_WebshopServer.DataModels.CAFF;
import com.example.SECundum_WebshopServer.DataModels.User;
import com.fasterxml.jackson.annotation.JsonValue;
import com.fasterxml.jackson.databind.util.JSONPObject;
import com.google.api.client.json.Json;
import com.google.api.core.ApiFuture;
import com.google.cloud.firestore.*;
import com.google.firebase.cloud.FirestoreClient;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.JSONValue;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpServletRequest;
import javax.swing.*;
import java.awt.*;
import java.io.*;
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
        ApiFuture<WriteResult> collectionsApiFuture = dbFireStore.collection("caffs").document(caff.getContent()).set(caff);
        return collectionsApiFuture.get().getUpdateTime().toString();

    }

    public void deleteCaff(String id){
        Firestore dbFireStore = FirestoreClient.getFirestore();
        ApiFuture<WriteResult> writeResult = dbFireStore.collection("caffs").document(id).delete();
    }

    public ResponseEntity<?> storeFile(MultipartFile file) throws IOException, InterruptedException, ParseException {
        String uploadsDir = "/uploads/";
        String projectPath = System.getProperty("user.dir");
        String realPathtoUploads = projectPath + uploadsDir;
        if(! new File(realPathtoUploads).exists())
        {
            new File(realPathtoUploads).mkdir();
        }

        String orgName = file.getOriginalFilename();
        String filePath = realPathtoUploads + orgName; //feltöltött fájl teljes elérési útja, parsernek kell beadni
        File dest = new File(filePath);
        file.transferTo(dest);
        caffParsing(filePath, projectPath);

        String pathToParsedFiles = projectPath;
        pathToParsedFiles = pathToParsedFiles.replace("SECundum_WebshopServer", "");
        pathToParsedFiles += "SECundum_WebshopParser\\out\\build\\x64-Debug\\SECundum_WebshopParser";

        ClassLoader classLoader = getClass().getClassLoader();

        String caffJsonPath = pathToParsedFiles + "\\myCaff.json";

        String caffName = getCaffNameFromJson(caffJsonPath);


        String caffImagePath = pathToParsedFiles + "\\myCaff_0.bmp";

        Image image = new ImageIcon(caffImagePath).getImage();


        return ResponseEntity.ok().body(new InputStreamReader());
    }


    //TODO
    private String getCaffNameFromJson(String caffJsonPath) throws IOException, ParseException {
        File file = new File(caffJsonPath);
        JSONParser parser = new JSONParser();
        Object obj = parser.parse(new FileReader(file));

        JSONObject object = (JSONObject) obj;
        JSONObject data = (JSONObject) object.get("Data");
        JSONArray animations = (JSONArray) data.get("Animations");
        JSONObject animation = (JSONObject) animations.get(0);
        JSONObject ciff = (JSONObject) animation.get("CIFF");
        JSONObject header = (JSONObject) ciff.get("Header");
        String caption = (String) header.get("Caption");

        return caption;
    }

    public void caffParsing(String filePath, String projectPath) throws IOException, InterruptedException {
        String[] command = new String[3];
        command[0] = "cmd";
        command[1] = "/c";
        command[2] = "cd.. & cd SECundum_WebshopParser\\out\\build\\x64-Debug\\SECundum_WebshopParser & SECundum_WebshopParser.exe \""+filePath +"\"";

        Process process = Runtime.getRuntime().exec(command);


        int exitCode = process.waitFor();
        System.out.println("\nExited with error code : " + exitCode);
    }
}
