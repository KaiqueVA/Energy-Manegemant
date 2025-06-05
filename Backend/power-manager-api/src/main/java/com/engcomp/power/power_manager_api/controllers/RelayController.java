package com.engcomp.power.power_manager_api.controllers;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.Map;

@RestController
@RequestMapping("/relay")
public class RelayController {

    private int currentState; // Assuming relay is off by default
    @PostMapping("/on")
    public ResponseEntity<Map<String, Integer>> turnOnRelay() {
        System.out.println("Relé LIGADO");
        currentState = 1; // Update the state to ON
        return ResponseEntity.ok(Map.of("relay", 1));
    }

    @PostMapping("/off")
    public ResponseEntity<Map<String, Integer>> turnOffRelay() {
        System.out.println("Relé DESLIGADO");
        currentState = 0; // Update the state to OFF
        return ResponseEntity.ok(Map.of("relay", 0));
    }

    @GetMapping("/state")
    public ResponseEntity<Map<String, Integer>> getRelayState()
    {
        return ResponseEntity.ok(Map.of("relay", currentState)); // Assuming relay is off by default
    }
}