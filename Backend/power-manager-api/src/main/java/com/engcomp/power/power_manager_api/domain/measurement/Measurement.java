package com.engcomp.power.power_manager_api.domain.measurement;

import jakarta.persistence.*;
import lombok.*;

import java.util.UUID;

@Entity
@Table(name = "measurements")
@Data
@NoArgsConstructor
@AllArgsConstructor
public class Measurement {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private UUID id;

    private Double vEficaz;
    private Double iEficaz;
    private Double pAparente;
    private Double pAtiva;
    private Double pReativa;
    private Double fatorPotencia;
}
