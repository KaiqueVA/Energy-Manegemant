package com.engcomp.power.power_manager_api.services;

import com.engcomp.power.power_manager_api.domain.measurement.Measurement;
import com.engcomp.power.power_manager_api.dto.MeasurementDTO;
import com.engcomp.power.power_manager_api.mapper.MeasurementMapper;
import com.engcomp.power.power_manager_api.repositories.MeasurementRepository;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.UUID;
import java.util.stream.Collectors;

@Service
public class MeasurementService {

    private final MeasurementRepository repository;
    private final MeasurementMapper mapper;

    public MeasurementService(MeasurementRepository repository, MeasurementMapper mapper) {
        this.repository = repository;
        this.mapper = mapper;
    }

    public List<MeasurementDTO> findAll() {
        return repository.findAll()
                .stream()
                .map(mapper::toDTO)
                .collect(Collectors.toList());
    }

    public MeasurementDTO save(MeasurementDTO dto) {
        Measurement saved = repository.save(mapper.toEntity(dto));
        return mapper.toDTO(saved);
    }

    public void delete(UUID id) {
        repository.deleteById(id);
    }
}
