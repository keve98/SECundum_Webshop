package com.example.SECundum_WebshopServer.DataControllers;


import com.example.SECundum_WebshopServer.DataModels.CAFF;
import com.example.SECundum_WebshopServer.DataServices.CaffService;
import org.json.simple.parser.ParseException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.util.List;
import java.util.concurrent.ExecutionException;

@RestController
public class CaffController {

    public CaffService caffService;

    @Autowired
    public CaffController(CaffService caffService) {
        this.caffService = caffService;
    }

    @GetMapping("/caff/getAll")
    public List<CAFF> getAllCaff() throws ExecutionException, InterruptedException {
        return caffService.getAllCaff();
    }

    @GetMapping("/caff/get")
    public CAFF getCaffById(@RequestParam String id) throws ExecutionException, InterruptedException {
        return caffService.getById(id);
    }

    @PostMapping("/caff/save")
    public ResponseEntity<?> saveCaff(@RequestParam("file") MultipartFile file) throws ExecutionException, InterruptedException, IOException, ParseException {
        return caffService.storeFile(file);
    }

    @GetMapping("/caff/download")
    public CAFF downloadCaff(@RequestParam String id) throws ExecutionException, InterruptedException {
        return caffService.downloadCaff(id);
    }
}
