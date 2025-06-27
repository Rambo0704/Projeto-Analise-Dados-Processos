# 📊 Projeto: Análise de Dados de Processos da Justiça Eleitoral do Distrito Federal

## 🔍 Visão Geral

Este projeto realiza uma análise de dados de processos judiciais da Justiça Eleitoral do Distrito Federal. Utilizando programação em C, ele processa, filtra e gera insights a partir de um dataset de processos (formato CSV), destacando padrões e resultados relevantes.

## 🚀 Funcionalidades

* **Leitura e importação** de arquivos CSV com dados dos processos.
* **Filtragem e classificação** por critérios como ano, situação, comarca, etc.
* **Cálculo de estatísticas**: médias, contagens, taxa de indeferimento, etc.
* **Exportação dos resultados** de análise em novos arquivos ou relatórios.

## 🛠️ Tecnologias Utilizadas

* Linguagem **C** (ferramenta principal: `main.c`, `functions.c/h`)
* Manipulação de arquivos CSV
* Algoritmos de ordenação, busca e agregação
* Estruturas de dados como arrays e structs

---

## 🧹 Estrutura do Repositório

```
/
├── .vscode/                  ← Configurações do editor
├── main.c                    ← Ponto de entrada da aplicação
├── functions.c               ← Implementações das funções de análise/processamento
├── functions.h               ← Assinaturas das funções
└── processo_043_202409032338.csv  
                             ← Exemplo de dataset usado nos testes
```

---

## ⚙️ Instalação e Execução

### Pré-requisitos

* Compilador **GCC** (ou equivalente compatível com C99 ou superior)
* Sistema operacional compatível (Linux, macOS, Windows com MinGW/Cygwin)

### Instruções

1. Clone o repositório:

   ```bash
   git clone https://github.com/rambo0704/Projeto-Analise-Dados-Processos.git
   cd Projeto-Analise-Dados-Processos
   ```

2. Compile o código:

   ```bash
   gcc main.c functions.c -o analise_processos
   ```

3. Execute o programa:

   ```bash
   ./analise_processos caminho/para/seu_arquivo.csv
   ```

   > Substitua `caminho/para/seu_arquivo.csv` pelo dataset a ser analisado.

4. Os resultados serão apresentados no terminal ou salvos em arquivos, conforme implementado.

---

## 📈 Exemplos de Uso

Supondo o dataset `processos.csv`:

```bash
./analise_processos ./dados/processos.csv
```

Saída esperada:

```
Total de processos: 5000
Processos finalizados: 3200
Taxa de indeferimento: 45.3%
Comarca com mais processos: Brasília (1230)
...
```

---

## 🧪 Como Testar

* Utilize arquivos CSV de exemplo com formatos semelhantes.
* Ajuste `main.c` ou `functions.c` para novos critérios, coleções ou métricas.
* Adicione funções de teste unitário conforme necessário para funções críticas.



*Obrigado por conferir o projeto! Ficarei feliz em receber seu feedback e colaborações.*
