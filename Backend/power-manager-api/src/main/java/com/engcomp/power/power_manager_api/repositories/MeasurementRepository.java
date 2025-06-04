package com.engcomp.power.power_manager_api.repositories;

import com.engcomp.power.power_manager_api.domain.measurement.Measurement;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import java.time.LocalDateTime;
import java.util.List;
import java.util.UUID;

public interface MeasurementRepository extends JpaRepository<Measurement, Integer> {
    List<Measurement> findByuser_id(UUID user_id);

    @Query("SELECT m FROM Measurement m WHERE FUNCTION('DATE', m.createdAt) = CURRENT_DATE")
    List<Measurement> findToday();

    @Query("SELECT m FROM Measurement m WHERE m.createdAt >= :startOfWeek")
    List<Measurement> findThisWeek(@Param("startOfWeek") LocalDateTime startOfWeek);

    @Query("SELECT m FROM Measurement m WHERE m.createdAt >= :sevenDaysAgo")
    List<Measurement> findLast7Days(@Param("sevenDaysAgo") LocalDateTime sevenDaysAgo);
}
