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

    @Query(value = """
        SELECT SUM(p_ativa * 5 / 3600 / 1000) 
        FROM measurement 
        WHERE DATE(created_at) = CURRENT_DATE AND user_id = :userId
    """, nativeQuery = true)
    Double getTodayKwh(@Param("userId") UUID userId);

    @Query("SELECT m FROM Measurement m WHERE m.createdAt >= :startOfWeek")
    List<Measurement> findThisWeek(@Param("startOfWeek") LocalDateTime startOfWeek);

    @Query(value = """
        SELECT DATE(created_at) as dia,
               SUM(p_ativa * 5 / 3600 / 1000) as total_kwh
        FROM measurement
        WHERE created_at >= :startOfWeek AND user_id = :userId
        GROUP BY dia
        ORDER BY dia
    """, nativeQuery = true)
    List<Object[]> getThisWeekKwh(@Param("startOfWeek") LocalDateTime startOfWeek,
                                  @Param("userId") UUID userId);

    @Query("SELECT m FROM Measurement m WHERE m.createdAt >= :sevenDaysAgo")
    List<Measurement> findLast7Days(@Param("sevenDaysAgo") LocalDateTime sevenDaysAgo);

    @Query(value = """
        SELECT DATE(created_at) as dia, 
               SUM(p_ativa * 5 / 3600 /1000) as total_kwh
        FROM measurement
        WHERE created_at >= CURRENT_DATE - INTERVAL '6 days'
          AND user_id = :userId
        GROUP BY dia
        ORDER BY dia
    """, nativeQuery = true)
    List<Object[]> getLast7DaysKwh(@Param("userId") UUID userId);


}
