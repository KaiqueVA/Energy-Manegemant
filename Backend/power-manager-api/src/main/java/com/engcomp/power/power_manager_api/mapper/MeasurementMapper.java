package com.engcomp.power.power_manager_api.mapper;

import com.engcomp.power.power_manager_api.domain.measurement.Measurement;
import com.engcomp.power.power_manager_api.dto.MeasurementDTO;
import org.mapstruct.Mapper;

import java.util.UUID;

@Mapper(componentModel = "spring")
public interface MeasurementMapper {

    Measurement toEntity(MeasurementDTO dto);
    MeasurementDTO toDTO(Measurement entity);

    default Integer map(UUID value) {
        return value != null ? value.hashCode() : null;
    }
    default UUID map(Integer value) {
        return value != null ? UUID.nameUUIDFromBytes(value.toString().getBytes()) : null;
    }
}
