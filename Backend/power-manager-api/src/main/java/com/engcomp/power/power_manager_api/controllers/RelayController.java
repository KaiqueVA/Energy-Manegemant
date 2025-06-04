package com.engcomp.power.power_manager_api.controllers;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.Map;

@RestController
@RequestMapping("/relay")
public class RelayController {

    @PostMapping("/on")
    public ResponseEntity<Map<String, Integer>> turnOnRelay() {
        System.out.println("Relé LIGADO");

        return ResponseEntity.ok(Map.of("relay", 1));
    }

    @PostMapping("/off")
    public ResponseEntity<Map<String, Integer>> turnOffRelay() {
        System.out.println("Relé DESLIGADO");

        return ResponseEntity.ok(Map.of("relay", 0));
    }
}