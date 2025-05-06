package com.engcomp.power.power_manager_api.services;

import com.engcomp.power.power_manager_api.domain.measurement.Measurement;
import com.engcomp.power.power_manager_api.domain.user.User;
import com.engcomp.power.power_manager_api.dto.MeasurementDTO;
import com.engcomp.power.power_manager_api.mapper.MeasurementMapper;
import com.engcomp.power.power_manager_api.repositories.MeasurementRepository;
import com.engcomp.power.power_manager_api.repositories.UserRepository;
import jakarta.persistence.EntityNotFoundException;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.UUID;
import java.util.stream.Collectors;

@Service
public class MeasurementService {

    private final MeasurementRepository repository;
    private final UserRepository userRepository;
    private final MeasurementMapper mapper;

    public MeasurementService(MeasurementRepository repository, UserRepository userRepository, MeasurementMapper mapper) {
        this.repository = repository;
        this.userRepository = userRepository;
        this.mapper = mapper;
    }

    public List<MeasurementDTO> findAll() {
        return repository.findAll()
                .stream()
                .map(mapper::toDTO)
                .collect(Collectors.toList());
    }

    public MeasurementDTO save(MeasurementDTO dto) {
        var user = userRepository.findById(dto.getUser_id())
                .orElseThrow(() -> new EntityNotFoundException("Usuário não encontrado"));

        var entity = mapper.toEntity(dto);
        entity.setUser(user);

        return mapper.toDTO(repository.save(entity));
    }

    public void delete(Integer id) {
        repository.deleteById(id);
    }

    public List<MeasurementDTO> findByuser_id(UUID user_id) {
        return repository.findByuser_id(user_id)
                .stream()
                .map(mapper::toDTO)
                .collect(Collectors.toList());
    }
}
