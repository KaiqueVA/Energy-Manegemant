package com.engcomp.power.power_manager_api.repositories;

import com.engcomp.power.power_manager_api.domain.measurement.Measurement;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;
import java.util.UUID;

public interface MeasurementRepository extends JpaRepository<Measurement, Integer> {
    List<Measurement> findByuser_id(UUID user_id);
}
