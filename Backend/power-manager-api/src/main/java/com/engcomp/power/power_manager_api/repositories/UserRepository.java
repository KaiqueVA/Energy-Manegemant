package com.engcomp.power.power_manager_api.repositories;
import com.engcomp.power.power_manager_api.domain.user.User;
import org.springframework.data.jpa.repository.JpaRepository;

public interface UserRepository extends JpaRepository<User, String>{
}
