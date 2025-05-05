package com.engcomp.power.power_manager_api.dto;

import lombok.Data;
import java.util.UUID;

@Data
public class MeasurementDTO {
    private UUID id;
    private Double vEficaz;
    private Double iEficaz;
    private Double pAparente;
    private Double pAtiva;
    private Double pReativa;
    private Double fatorPotencia;
}
