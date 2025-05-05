package com.engcomp.power.power_manager_api.mapper;

import com.engcomp.power.power_manager_api.domain.measurement.Measurement;
import com.engcomp.power.power_manager_api.dto.MeasurementDTO;
import org.mapstruct.Mapper;

@Mapper(componentModel = "spring")
public interface MeasurementMapper {
    Measurement toEntity(MeasurementDTO dto);
    MeasurementDTO toDTO(Measurement entity);
}
