package com.engcomp.power.power_manager_api.infra.security;

import com.engcomp.power.power_manager_api.domain.user.User;
import com.engcomp.power.power_manager_api.repositories.UserRepository;
import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Component;
import org.springframework.web.filter.OncePerRequestFilter;

import java.io.IOException;
import java.util.Collections;

@Component
public class SecurityFilter extends OncePerRequestFilter {

    @Autowired
    TokenService tokenService;

    @Autowired
    UserRepository userRepository;

    @Override
    protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response, FilterChain filterChain)
            throws ServletException, IOException {

        try {
            var token = recoverToken(request);

            if (token != null) {
                var login = tokenService.validateToken(token);
                if (login != null) {
                    userRepository.findByEmail(login).ifPresent(user -> {
                        var authorities = Collections.singletonList(new SimpleGrantedAuthority("ROLE_USER"));
                        var authentication = new UsernamePasswordAuthenticationToken(user, null, authorities);
                        SecurityContextHolder.getContext().setAuthentication(authentication);
                    });
                }
            }

        } catch (Exception e) {
            // Não interrompe a requisição se o token for inválido ou gerar erro
            System.out.println("Token inválido ou erro na validação: " + e.getMessage());
        }

        filterChain.doFilter(request, response);
    }



    private String recoverToken(HttpServletRequest request) {
        var authHeader = request.getHeader("Authorization");
        if (authHeader == null || !authHeader.startsWith("Bearer ")) return null;
        return authHeader.replace("Bearer ", "");
    }
}