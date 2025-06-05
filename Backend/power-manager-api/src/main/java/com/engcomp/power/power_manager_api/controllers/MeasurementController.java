package com.engcomp.power.power_manager_api.controllers;

import com.engcomp.power.power_manager_api.dto.MeasurementDTO;
import com.engcomp.power.power_manager_api.infra.security.TokenService;
import com.engcomp.power.power_manager_api.services.MeasurementService;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDate;
import java.util.List;
import java.util.Map;
import java.util.UUID;

@RestController
@RequestMapping("/measurements")
public class MeasurementController {

    private final MeasurementService service;
    private final TokenService tokenService;

    public MeasurementController(MeasurementService service, TokenService tokenService) {
        this.service = service;
        this.tokenService = tokenService;
    }

    private UUID getUserIdFromToken(String authHeader) {
        if (authHeader == null || !authHeader.startsWith("Bearer ")) {
            throw new RuntimeException("Token inválido ou ausente");
        }
        String token = authHeader.substring(7);
        UUID userId = tokenService.extractUserId(token);
        if (userId == null) {
            throw new RuntimeException("Token inválido");
        }
        return userId;
    }

    @GetMapping
    public ResponseEntity<List<MeasurementDTO>> getAll() {
        return ResponseEntity.ok(service.findAll());
    }

    @GetMapping("/today")
    public ResponseEntity<List<MeasurementDTO>> getToday() {
        return ResponseEntity.ok(service.getToday());
    }

    @GetMapping("/this-week")
    public ResponseEntity<List<MeasurementDTO>> getThisWeek() {
        return ResponseEntity.ok(service.getThisWeek());
    }

    @GetMapping("/last-7-days")
    public ResponseEntity<List<MeasurementDTO>> getLast7Days() {
        return ResponseEntity.ok(service.getLast7Days());
    }

    @GetMapping("/today/kwh")
    public ResponseEntity<Double> getTodayKwh(@RequestHeader("Authorization") String authHeader) {
        UUID userId = getUserIdFromToken(authHeader);
        Double todayKwh = service.getTodayKwh(userId);
        return ResponseEntity.ok(todayKwh);
    }

    @GetMapping("/last-7-days/kwh")
    public ResponseEntity<List<Map<String, Object>>> getLast7DaysKwh(@RequestHeader("Authorization") String authHeader) {
        UUID userId = getUserIdFromToken(authHeader);
        List<Map<String, Object>> consumption = service.getLast7DaysKwh(userId);
        return ResponseEntity.ok(consumption);
    }

    @GetMapping("/this-week/kwh")
    public ResponseEntity<List<Map<String, Object>>> getThisWeekKwh(@RequestHeader("Authorization") String authHeader) {
        UUID userId = getUserIdFromToken(authHeader);
        List<Map<String, Object>> consumption = service.getThisWeekKwh(userId);
        return ResponseEntity.ok(consumption);
    }



    @PostMapping
    public ResponseEntity<MeasurementDTO> create(@RequestBody MeasurementDTO dto) {
        return ResponseEntity.ok(service.save(dto));
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> delete(@PathVariable Integer id) {
        service.delete(id);
        return ResponseEntity.noContent().build();
    }
}
