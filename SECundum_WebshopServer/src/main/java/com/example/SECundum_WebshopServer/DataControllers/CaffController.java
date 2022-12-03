package com.example.SECundum_WebshopServer.DataControllers;


import com.example.SECundum_WebshopServer.DataModels.CAFF;
import com.example.SECundum_WebshopServer.DataServices.CaffService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.io.Resource;
import org.springframework.core.io.UrlResource;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;


@RestController
@CrossOrigin(origins = "http://localhost:4200")
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

    @GetMapping ("/caff/get")
    public ResponseEntity<CAFF> getCaffById(@RequestParam String name) throws Exception {
        name = name.replace("_", " ");
        return ResponseEntity.ok(caffService.getByName(name));
    }

    @PostMapping("/caff/save")
    public ResponseEntity<CAFF> saveCaff(@RequestParam("file") MultipartFile file) throws Exception {
        return ResponseEntity.ok(caffService.saveCaff(file));
    }

    @GetMapping("/caff/download")
    @ResponseBody
    public ResponseEntity<?> getFile(@RequestParam String filename) throws Exception {
        caffService.downloadCaff(filename.replace("_", " "));
        Path root = Paths.get("uploads");
        filename += ".caff";
        Path file = root.resolve(filename);
        Resource r = new UrlResource(file.toUri());
        return ResponseEntity.ok().body(r);
    }
}
