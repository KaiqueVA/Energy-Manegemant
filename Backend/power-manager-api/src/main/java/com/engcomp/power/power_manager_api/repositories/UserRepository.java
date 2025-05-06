package com.engcomp.power.power_manager_api.repositories;
import com.engcomp.power.power_manager_api.domain.user.User;
import org.springframework.data.jpa.repository.JpaRepository;
import java.util.Optional;
import java.util.UUID;

public interface UserRepository extends JpaRepository<User, UUID>{
    Optional<User> findByEmail(String email);
}
