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
    public ResponseEntity<List<CAFF>> getAllCaff() throws Exception {
        return ResponseEntity.ok(caffService.getAllCaff());
    }

    @GetMapping("/caff/get")
    public ResponseEntity<CAFF> getCaffById(@RequestParam String name) throws Exception {
        return ResponseEntity.ok(caffService.getByName(name));
    }

    @PostMapping("/caff/save")
    public ResponseEntity<CAFF> saveCaff(@RequestParam("file") MultipartFile file) throws Exception {
        return ResponseEntity.ok(caffService.saveCaff(file));
    }

    @GetMapping("/caff/download")
    public ResponseEntity<CAFF> downloadCaff(@RequestParam String name) throws Exception {
        return ResponseEntity.ok(caffService.downloadCaff(name));
    }
}
