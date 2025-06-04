package com.engcomp.power.power_manager_api.mapper;

import com.engcomp.power.power_manager_api.domain.measurement.Measurement;
import com.engcomp.power.power_manager_api.dto.MeasurementDTO;
import org.mapstruct.Mapper;
import org.mapstruct.Mapping;

import java.util.UUID;

@Mapper(componentModel = "spring")
public interface MeasurementMapper {

    Measurement toEntity(MeasurementDTO dto);
    MeasurementDTO toDTO(Measurement entity);

    default String map(UUID value) {
        return value != null ? value.toString() : null;
    }

    default UUID map(String value) {
        return value != null ? UUID.fromString(value) : null;
    }
}
