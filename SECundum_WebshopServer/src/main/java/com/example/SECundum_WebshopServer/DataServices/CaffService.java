package com.example.SECundum_WebshopServer.DataServices;

import com.example.SECundum_WebshopServer.DataModels.CAFF;
import com.google.api.core.ApiFuture;
import com.google.cloud.firestore.*;
import com.google.firebase.cloud.FirestoreClient;
import org.apache.commons.io.FileUtils;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

import javax.imageio.ImageIO;
import javax.servlet.http.HttpServletRequest;
import java.awt.image.BufferedImage;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

@Service
public class CaffService {

    @Autowired
    private HttpServletRequest request;

    public List<CAFF> getAllCaff() throws Exception {
        Firestore dbFireStore = FirestoreClient.getFirestore();
        ApiFuture<QuerySnapshot> future = dbFireStore.collection("caffs").get();
        Object document = future.get();
        String uploadsDir = getUploadsDirPath();
        if(document != null){
            List<CAFF> caffList =
                    future.get().toObjects(CAFF.class);

            for(CAFF c : caffList){
                c.setCaffFile(new File(uploadsDir + c.getContent().replace(" ", "_") + ".caff"));
            }
            return caffList;
        }

        return new ArrayList<>();

    }

    public CAFF getByName(String name) throws Exception {
        Firestore dbFireStore = FirestoreClient.getFirestore();
        DocumentReference documentReference = dbFireStore.collection("caffs").document(name);
        ApiFuture<DocumentSnapshot> future = documentReference.get();
        DocumentSnapshot document = future.get();
        CAFF caff;
        String uploadsDir = getUploadsDirPath();
        if(document.exists()){
            caff = document.toObject(CAFF.class);
            caff.setCaffFile(new File(uploadsDir + caff.getContent().replace(" ", "_") + ".caff"));
            return caff;
        }
        throw new Exception("Cannot find image with name: " + name);

    }

    public CAFF saveCaff(MultipartFile file) throws Exception {
        CAFF caff = uploadedCaffHandle(file);
        Firestore dbFireStore = FirestoreClient.getFirestore();
        ApiFuture<WriteResult> collectionsApiFuture = dbFireStore.collection("caffs").document(caff.getContent()).set(caff);
        return caff;
    }

    public void deleteCaff(String name){
        Firestore dbFireStore = FirestoreClient.getFirestore();
        ApiFuture<WriteResult> writeResult = dbFireStore.collection("caffs").document(name).delete();
    }

    public String getUploadsDirPath(){
        return System.getProperty("user.dir") + "/uploads/";
    }

    public CAFF uploadedCaffHandle(MultipartFile file) throws Exception {
        if(!file.getOriginalFilename().contains(".caff")){
            throw new Exception("Extension of the file is not caff");
        }

        String projectPath = System.getProperty("user.dir");
        String realPathtoUploads = getUploadsDirPath();
        if(! new File(realPathtoUploads).exists())
        {
            new File(realPathtoUploads).mkdir();
        }

        String orgName = file.getOriginalFilename();
        String filePath = realPathtoUploads + orgName; //feltöltött fájl teljes elérési útja, parsernek kell beadni

        // save given caff file to uploads directory
        File dest = new File(filePath);
        file.transferTo(dest);

        //parse caff file to json and bmp with cmd commands
        caffParsing(filePath);

        String pathToParsedFiles = projectPath;
        pathToParsedFiles = pathToParsedFiles.replace("SECundum_WebshopServer", "");
        pathToParsedFiles += "SECundum_WebshopParser\\out\\build\\x64-Debug\\SECundum_WebshopParser";


        String caffJsonPath = pathToParsedFiles + "\\myCaff.json";

        //get caffsContentName
        String caffName = getCaffNameFromJson(caffJsonPath);


        // get created bmp image and store in image variable
        String caffImagePath = pathToParsedFiles + "\\myCaff_0.bmp";

        //convert bmp to png
        BufferedImage bmpImage = ImageIO.read(new File(caffImagePath));
        String outputpath = pathToParsedFiles + "\\"+ caffName.replace( " ", "_") + ".png";
        File outputFile = new File(outputpath);
        ImageIO.write(bmpImage, "PNG", outputFile);

        File uploads = new File(projectPath.replace("SECundum_WebshopServer", "SECundum_WebshopClient") + "\\SECundumWebshopClient\\src\\assets\\caff_pictures\\" + caffName.replace( " ", "_") + ".png");

        FileUtils.copyFile(outputFile, uploads);

        //rename caff file in upload directory
        Path source = Paths.get(filePath);
        Files.move(source, source.resolveSibling(caffName.replace(" ", "_") + ".caff"));


        CAFF caff = new CAFF(caffName);
        return caff;
    }

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

    public void caffParsing(String filePath) throws IOException, InterruptedException {
        String[] command = new String[3];
        command[0] = "cmd";
        command[1] = "/c";
        command[2] = "cd.. & cd SECundum_WebshopParser\\out\\build\\x64-Debug\\SECundum_WebshopParser & SECundum_WebshopParser.exe \""+filePath +"\"";

        Process process = Runtime.getRuntime().exec(command);


        int exitCode = process.waitFor();
        System.out.println("\nExited with error code : " + exitCode);
    }
}
