package com.engcomp.power.power_manager_api.domain.measurement;

import jakarta.persistence.*;
import lombok.*;

import java.util.UUID;

@Entity
@Table(name = "measurement")
@Data
@NoArgsConstructor
@AllArgsConstructor
public class Measurement {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private UUID id;

    private Double v_eficaz;
    private Double i_eficaz;
    private Double p_aparente;
    private Double p_ativa;
    private Double p_reativa;
    private Double fator_potencia;
}
