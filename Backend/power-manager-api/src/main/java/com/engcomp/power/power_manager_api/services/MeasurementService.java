package com.engcomp.power.power_manager_api.services;

import com.engcomp.power.power_manager_api.domain.measurement.Measurement;
import com.engcomp.power.power_manager_api.domain.user.User;
import com.engcomp.power.power_manager_api.dto.MeasurementDTO;
import com.engcomp.power.power_manager_api.mapper.MeasurementMapper;
import com.engcomp.power.power_manager_api.repositories.MeasurementRepository;
import com.engcomp.power.power_manager_api.repositories.UserRepository;
import jakarta.persistence.EntityNotFoundException;
import org.springframework.stereotype.Service;

import java.time.DayOfWeek;
import java.time.LocalDate;
import java.time.LocalDateTime;
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
        System.out.println(dto);
        var user = userRepository.findById(dto.getUser_id())
                .orElseThrow(() -> new EntityNotFoundException("Usuário não encontrado"));

        var entity = mapper.toEntity(dto);
        entity.setUser(user);

        return mapper.toDTO(repository.save(entity));
    }

    public void delete(Integer id) {
        repository.deleteById(id);
    }

//    public List<MeasurementDTO> findByUserId(UUID userId) {
//        return repository.findByUserId(userId)
//                .stream()
//                .map(mapper::toDTO)
//                .map(this::addEnergyConsumption)
//                .collect(Collectors.toList());
//    }

    public List<MeasurementDTO> getToday() {
        return repository.findToday()
                .stream()
                .map(mapper::toDTO)
                .map(this::addEnergyConsumption)
                .toList();
    }

    public List<MeasurementDTO> getThisWeek() {
        LocalDateTime startOfWeek = LocalDate.now()
                .with(DayOfWeek.MONDAY)
                .atStartOfDay();
        return repository.findThisWeek(startOfWeek)
                .stream()
                .map(mapper::toDTO)
                .map(this::addEnergyConsumption)
                .toList();
    }

    public List<MeasurementDTO> getLast7Days() {
        LocalDateTime sevenDaysAgo = LocalDateTime.now().minusDays(7);
        return repository.findLast7Days(sevenDaysAgo)
                .stream()
                .map(mapper::toDTO)
                .map(this::addEnergyConsumption)
                .toList();
    }

    private MeasurementDTO addEnergyConsumption(MeasurementDTO dto) {
        if (dto.getP_ativa() == null) {
            dto.setEnergiaKWh(null);
            return dto;
        }
        double potenciaKW = dto.getP_ativa() / 1000.0;  // W para kW
        double intervaloHoras = 5.0 / 3600.0;           // 5 segundos em horas
        double energiaKWh = potenciaKW * intervaloHoras;
        dto.setEnergiaKWh(energiaKWh);
        return dto;
    }
}