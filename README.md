# Gerenciador de Projetos e Membros

## 📌 Visão Geral
Este programa em C implementa um sistema de gerenciamento de projetos e membros, utilizando listas encadeadas para armazenar e manipular os dados carregados de arquivos externos. O sistema permite associar membros a projetos e consultar essas relações utilizando o menu interativo.

## 🚀 Funcionalidades Principais
- 📂 **Carregamento de Dados**: Importação de projetos, membros e relações a partir de arquivos.
- 🔍 **Consultas**: Permite buscar todos os projetos de um membro e todos os membros de um projeto.
- 🖥 **Interface de Usuário**: Menu interativo via terminal.

## 🛠 Estruturas de Dados
- **`t_projeto`**: Representa um projeto com ID e descrição.
- **`t_membro`**: Representa um membro com ID e nome.
- **`t_relacao`**: Representa a associação entre membros e projetos.

## 🔧 Principais Funções

### 📂 **Carregamento de Dados**
- `Lista load_projetos(char *fileName)`: Carrega projetos de um arquivo e os adiciona à lista.
- `Lista load_membros(char *fileName)`: Carrega membros de um arquivo e os adiciona à lista.
- `Lista load_relacoes(char *fileName)`: Carrega as relações entre projetos e membros.

### 🔍 **Consultas**
- `Lista membros_projeto(char *id_proj, Lista lst_relacoes, Lista lst_membros)`: Retorna os membros de um projeto.
- `Lista projetos_membro(char *id_mem, Lista lst_relacoes, Lista lst_projetos)`: Retorna os projetos de um membro.

## 📜 Dependências
- `tadlista.h`: Biblioteca para manipulação das listas encadeadas.
- Arquivos de dados: `bdmembros.txt`, `bdprojetos.txt`, `bdrelacoes.txt`.

## 🚀 Como Executar
1. Compile o programa:
   ```bash
   gcc resposta.c -o resposta.exe
   ./resposta.exe
