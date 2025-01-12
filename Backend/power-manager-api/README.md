## Configuração do Arquivo `.env`

Este projeto utiliza um arquivo `.env` para armazenar informações sensíveis e específicas do ambiente, como credenciais do banco de dados e chaves de API. O uso do `.env` ajuda a manter essas informações fora do código-fonte, garantindo maior segurança e flexibilidade.

### **Passos para configurar o `.env`**
1. Na raiz do projeto, crie um arquivo chamado `.env`.
2. Copie o conteúdo do arquivo de exemplo `env.example` (se disponível) para o `.env`:
   ```bash
   cp .env.example .env
