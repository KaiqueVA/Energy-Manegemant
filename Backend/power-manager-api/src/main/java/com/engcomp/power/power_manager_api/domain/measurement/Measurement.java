package com.engcomp.power.power_manager_api.domain.measurement;

import com.engcomp.power.power_manager_api.domain.user.User;
import jakarta.persistence.*;
import lombok.*;
import org.hibernate.annotations.CreationTimestamp;

import java.time.LocalDateTime;
import java.util.UUID;


@Entity
@Table(name = "measurement")
@Data
@NoArgsConstructor
@AllArgsConstructor
public class Measurement {
    @Id
    @SequenceGenerator(name = "measurement_seq", sequenceName = "measurement_seq", allocationSize = 1)
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "measurement_seq")
    private Integer id;

    private Double v_eficaz;
    private Double i_eficaz;
    private Double p_aparente;
    private Double p_ativa;
    private Double p_reativa;
    private Double fator_potencia;

    @ManyToOne
    @JoinColumn(name = "user_id", nullable = false)
    private User user;

    @CreationTimestamp
    @Column(updatable = false)
    private LocalDateTime createdAt;
}
