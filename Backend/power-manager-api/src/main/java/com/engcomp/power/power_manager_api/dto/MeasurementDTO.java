package com.engcomp.power.power_manager_api.dto;

import lombok.Data;
import java.util.UUID;

@Data
public class MeasurementDTO {
    private UUID id;
    private Double v_eficaz;
    private Double i_eficaz;
    private Double p_aparente;
    private Double p_ativa;
    private Double p_reativa;
    private Double fator_potencia;
}
