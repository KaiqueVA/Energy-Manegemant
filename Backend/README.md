# ⚡ Energy Management - Backend

<p align="center">
    <img loading="lazy" src="http://img.shields.io/static/v1?label=STATUS&message=Developing&color=346eeb&style=for-the-badge"/>
</p>

Este repositório contém a aplicação *backend* do sistema de gerenciamento de energia, desenvolvida em *Java com Spring Boot*. Ele é responsável por toda a lógica de negócio, autenticação, manipulação de dados e comunicação com o banco de dados.

---

## 🚀 Funcionalidades

- ✅ Cadastro e autenticação de usuários
- ✅ Associação de medições de energia aos usuários
- ✅ Segurança com JWT e Spring Security
- ✅ API RESTful com endpoints organizados por domínio
- ✅ Integração com banco de dados relacional

---

## 🛠 Tecnologias utilizadas

- *Java 21*
- *Spring Boot*
- *Spring Security*
- *Spring Data JPA*
- *JWT (JSON Web Tokens)*
- *Banco de dados* (ex: PostgreSQL)
- *Lombok*
- *MapStruct*

---

## 📁 Estrutura de pastas

```bash
power-manager-api/
├── controllers # Controladores REST
├── domain # Entidades e modelos de domínio
├── dto # Data Transfer Objects
├── repositories # Interfaces de acesso ao banco
├── services # Regras de negócio
├── mapper # Mapeamento entre entidades e DTOs
├── infra/security # Segurança e autenticação
└── PowerManagerApiApplication.java
```
---

## 🔒 Segurança

O projeto utiliza *JWT* para autenticação e *Spring Security* para proteger os endpoints.

---

## 📦 Como rodar o projeto

1. Clone o repositório:

```bash
git clone https://github.com/nathaliaatamanchuk/Energy-Management-Backend.git
cd Energy-Management-Backend
```

2. Configure o application.properties com as credenciais do banco.

3. Rode a aplicação.

## 👥 Authors

| [<img loading="lazy" src="https://avatars.githubusercontent.com/u/123494342?v=4" width=115><br><sub>Kaique Vecchia</sub>](https://github.com/KaiqueVA) | [<img loading="lazy" src="https://avatars.githubusercontent.com/u/92125155?v=4" width=115><br><sub>Nathalia Atamanchuk</sub>](https://github.com/nathaliaatamanchuk) |
| :---: | :---: |
