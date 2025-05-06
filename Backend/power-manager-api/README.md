# Configuração do Ambiente de Desenvolvimento

Para executar este projeto no seu ambiente local, você precisará configurar algumas variáveis de ambiente em sua IDE ou em seu sistema operacional

---

## Variáveis de Ambiente Necessárias

Antes de iniciar o projeto, configure as seguintes variáveis de ambiente:

| Nome da Variável | Descrição                                  | Exemplo                               |
|-------------------|-------------------------------------------|---------------------------------------|
| `DB_URL`          | URL de conexão com o banco de dados       | `jdbc:postgresql://localhost:5432/db` |
| `DB_USERNAME`     | Nome de usuário do banco de dados         | `admin`                               |
| `DB_PASSWORD`     | Senha do banco de dados                  | `senha_secreta`                       |
| `API_SECURITY_TOKEN_SECRET`| Segredo utilizado para assinar e validar tokens JWT na aplicação| `senha_secreta`|

