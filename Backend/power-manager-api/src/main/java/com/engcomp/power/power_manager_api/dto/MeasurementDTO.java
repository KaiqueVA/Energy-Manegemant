package com.engcomp.power.power_manager_api.dto;

import lombok.Data;
import lombok.Getter;
import lombok.Setter;

import java.time.LocalDateTime;
import java.util.UUID;

@Getter
@Setter
@Data
public class MeasurementDTO {
    private Integer id;
    private Double v_eficaz;
    private Double i_eficaz;
    private Double p_aparente;
    private Double p_ativa;
    private Double p_reativa;
    private Double fator_potencia;
    private Double energiaKWh;

    private UUID user_id;
    private LocalDateTime createdAt;

    public void setEnergiaKWh(Double energiaKWh) {
        this.energiaKWh = energiaKWh;
    }
}
