package com.engcomp.power.power_manager_api.controllers;

import com.engcomp.power.power_manager_api.dto.MeasurementDTO;
import com.engcomp.power.power_manager_api.services.MeasurementService;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.UUID;

@RestController
@RequestMapping("/measurements")
public class MeasurementController {

    private final MeasurementService service;

    public MeasurementController(MeasurementService service) {
        this.service = service;
    }

    @GetMapping
    public ResponseEntity<List<MeasurementDTO>> getAll() {
        return ResponseEntity.ok(service.findAll());
    }

    @PostMapping
    public ResponseEntity<MeasurementDTO> create(@RequestBody MeasurementDTO dto) {
        return ResponseEntity.ok(service.save(dto));
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> delete(@PathVariable UUID id) {
        service.delete(id);
        return ResponseEntity.noContent().build();
    }
}
