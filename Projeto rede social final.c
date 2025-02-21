// Grupo: Maycon Rodrigo, João Victor, David Gabriel, Jhonatan Mendes e Guilherme Bonfim
//Projeto - Rede Social

//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#define MAXIMO_USUARIOS 100
#define MAXIMO_POSTAGENS 1000
#define MAXIMO_SEGUIDORES 100

// Ela guarda as informacoes do Usuario
typedef struct {
    int id;
    char nome[50];
    int idade;
    char senha[10];
    char email[50];
    int bloqueado;
    int postagens[MAXIMO_POSTAGENS];
    int num_postagens;
    int seguidores[MAXIMO_SEGUIDORES];
    int num_seguidores;
} Usuario;
// Guarda as informacoes das postagens
typedef struct {
    int id;
    char conteudo[200];
    int likes;
    int usuario_id;
    int excluida;
} Postagem;
// Variaveis globais e Contadores
Usuario usuarios[MAXIMO_USUARIOS];
Postagem postagens[MAXIMO_POSTAGENS];
int num_usuarios = 0;
int num_postagens = 0;
//Senha do Administrador
char admin_senha[9] = "admin123";
//Funcao para Limpar
void limparTela() {
    system("cls");
}
// Garante que a Entrada seja valida
int lerEntradaValida() {
    int valor;
    if (scanf("%d", &valor) != 1) {
        while (getchar() != '\n');
        return -1;
    }
    return valor;
}

// Essa funcao Garante que a senha tenha de 4 a 8 digitos e tem caracteres alfanumericos
int validarSenha(const char *senha) {
    if (strlen(senha) < 4 || strlen(senha) > 8) {
        return 0;
    }
    for (int i = 0; i < 4; i++) {
        if (!isalnum(senha[i])) {
            return 0;
        }
    }
    return 1;
}
// Essa funcao garante que o email tenha '@', '.com' e nao tenha espacos
int validarEmail(const char *email) {
    if (strstr(email, "@") == NULL) {
        printf("O email deve conter '@'.\n");
        return 0;
    }
    if (strstr(email, " ") != NULL) {
        printf("O email n�o deve conter espa�o.\n");
        return 0;
    }
    if (strstr(email, ".com") == NULL) {
        printf("O email deve conter '.com'.\n");
        return 0;
    }
    if (strstr(email == email))
    return 1;
}
//Essa funcao faz o cadastro do usuario
void cadastro_Usuario() {
    Usuario novoUsuario;

    while (getchar() != '\n');

    printf("Nome: ");
    fgets(novoUsuario.nome, sizeof(novoUsuario.nome), stdin);
    novoUsuario.nome[strcspn(novoUsuario.nome, "\n")] = '\0';

    printf("Informe sua idade: ");
    scanf("%d", &novoUsuario.idade);
    getchar();
    //Garante que o usuario tenha idade igual ou maior a 13 anos
    if (novoUsuario.idade < 13) {
        printf("Voce deve ter no mínimo 13 anos de idade para criar uma conta.\n");
        system("pause");
        limparTela();
        return;
    }

    do {
        printf("Insira seu email: ");
        fgets(novoUsuario.email, sizeof(novoUsuario.email), stdin);
        novoUsuario.email[strcspn(novoUsuario.email, "\n")] = '\0';
    } while (!validarEmail(novoUsuario.email));

    char senha[5];
    do {
        printf("Insira sua Senha: ");
        scanf("%s", senha);
        if (!validarSenha(senha)) {
            printf("Senha invalida. Deve ter no minimo 4 caracteres alfanumericos.\n");
        }
    } while (!validarSenha(senha));
    //Aqui garantimos que as senhas sejam iguais
    char confirmacaoSenha[10];
    do {
        printf("Confirme a senha: ");
        scanf("%s", confirmacaoSenha);
        if (strcmp(senha, confirmacaoSenha) != 0) {
            printf("As senhas nao coincidem. Tente novamente.\n");
        }
    } while (strcmp(senha, confirmacaoSenha) != 0);
    strcpy(novoUsuario.senha, senha);

    novoUsuario.id = num_usuarios;
    novoUsuario.bloqueado = 0;
    novoUsuario.num_postagens = 0;
    novoUsuario.num_seguidores = 0;

    usuarios[num_usuarios++] = novoUsuario;
    printf("Usuario cadastrado com sucesso!\n", novoUsuario);
}
// Exiba as postagens feitas pelo usuario
void exibirPostagens(int usuario_id, int is_admin) {
    printf("\nPostagens:\n");
    for (int i = 0; i < num_usuarios; i++) {
        if (usuarios[i].bloqueado){
            continue;
        }
           if (is_admin || i == usuario_id) {
            int contador_postagem = 1;
            for (int j = 0; j < num_postagens; j++) {
                if (postagens[j].usuario_id == i && !postagens[j].excluida) {
                    printf("Usuario %s | Postagem %d | ID %d | Conteudo: %s | Likes: %d\n",
                           usuarios[i].nome, contador_postagem, postagens[j].id, postagens[j].conteudo, postagens[j].likes);
                    contador_postagem++;
                }
            }
        } else {
            int segue = 0;
            for (int j = 0; j < usuarios[usuario_id].num_seguidores; j++) {
                if (usuarios[usuario_id].seguidores[j] == i) {
                    segue = 1;
                    break;
                }
            }
            if (segue) {
                int contador_postagem = 1;
                for (int j = 0; j < num_postagens; j++) {
                    if (postagens[j].usuario_id == i && !postagens[j].excluida) {
                        printf("Usuario %s | Postagem %d | ID %d | Conteudo: %s | Likes: %d\n",
                               usuarios[i].nome, contador_postagem, postagens[j].id, postagens[j].conteudo, postagens[j].likes);
                        contador_postagem++;
                    }
                }
            }
        }
    }
}
void exibirPostagensSeguidores(int usuario_id) {
    printf("\nPostagens dos usuarios que voce segue:\n");
    for (int i = 0; i < num_usuarios; i++) {
        // Verifica se o usuário atual segue o usuário i
        int segue = 0;
        for (int j = 0; j < usuarios[usuario_id].num_seguidores; j++) {
            if (usuarios[usuario_id].seguidores[j] == i) {
                segue = 1;
                break;
            }
        }

        // Se o usuário atual segue o usuário i, exibe as postagens dele
        if (segue) {
            int contador_postagem = 1;
            for (int j = 0; j < num_postagens; j++) {
                if (postagens[j].usuario_id == i && !postagens[j].excluida) {
                    printf("Usuario %s | Postagem %d | ID %d | Conteudo: %s | Likes: %d\n",
                           usuarios[i].nome, contador_postagem, postagens[j].id, postagens[j].conteudo, postagens[j].likes);
                    contador_postagem++;
                }
            }
        }
    }
}
// Essa funcao pertence ao administrador que exclui a postagem de um usuario pelo nome e numero da postagem
void excluirPostagemPorNomeENumero() {
    char nome[50];
    int numero_postagem;

    printf("Digite o nome do usuario: ");
    scanf(" %[^\n]", nome);
    ////fgets(nome, 50, stdin); // Usar " %[^\n]" para ler strings com espacos
    ////getchar();

    int usuario_encontrado = -1;
    for (int i = 0; i < num_usuarios; i++) {
        if (strcmp(usuarios[i].nome, nome) == 0) {
            usuario_encontrado = i;
            break;
        }
    }

    if (usuario_encontrado == -1) {
        printf("Usuario nao encontrado.\n");
        return;
    }

    int contador_postagem = 1;
    printf("\nPostagens do usuario %s:\n", usuarios[usuario_encontrado].nome);
    for (int j = 0; j < num_postagens; j++) {
        if (postagens[j].usuario_id == usuario_encontrado && !postagens[j].excluida) {
            printf("Postagem %d | Conteudo: %s | Likes: %d\n",
                   contador_postagem, postagens[j].conteudo, postagens[j].likes);
            contador_postagem++;
        }
    }

    // Solicitar a exclusao de uma postagem
    printf("Digite o numero da postagem a ser excluida: ");
    scanf("%d", &numero_postagem);
    getchar();  // Para limpar o buffer apos a leitura do inteiro

    // Encontrar e excluir a postagem
    contador_postagem = 1;
    for (int i = 0; i < num_postagens; i++) {
        if (postagens[i].usuario_id == usuario_encontrado && !postagens[i].excluida) {
            if (contador_postagem == numero_postagem) {
                postagens[i].excluida = 1;
                printf("Postagem excluida com sucesso.\n");

                // Verificar se o usuario tem 3 postagens excluidas
                int postagens_excluidas = 0;
                for (int j = 0; j < num_postagens; j++) {
                    if (postagens[j].usuario_id == usuario_encontrado && postagens[j].excluida) {
                        postagens_excluidas++;
                    }
                }
                if (postagens_excluidas >= 3) {
                    usuarios[usuario_encontrado].bloqueado = 1;
                    printf("Usuario %s foi bloqueado por ter 3 postagens excluidas.\n", usuarios[usuario_encontrado].nome);
                }
                return;
            }
            contador_postagem++;
        }
    }

    printf("Postagem nao encontrada.\n");
}
void salvarUsuarios() {
    FILE *arquivo = fopen("usuarios.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de usuarios.\n");
        return;
    }

    // Escreve o cabecalho do arquivo CSV
    fprintf(arquivo, "id,nome,idade,senha,email,bloqueado,num_postagens,num_seguidores\n");

    // Escreve os dados de cada usuario
    for (int i = 0; i < num_usuarios; i++) {
        fprintf(arquivo, "%d,%s,%d,%s,%s,%d,%d,%d\n",
                usuarios[i].id,
                usuarios[i].nome,
                usuarios[i].idade,
                usuarios[i].senha,
                usuarios[i].email,
                usuarios[i].bloqueado,
                usuarios[i].num_postagens,
                usuarios[i].num_seguidores);
    }

    fclose(arquivo);
    printf("Usuarios salvos com sucesso!\n");
}

void salvarPostagens() {
    FILE *arquivo = fopen("postagens.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de postagens.\n");
        return;
    }

    // Escreve o cabecalho do arquivo CSV
    fprintf(arquivo, "id,conteudo,likes,usuario_id,excluida\n");

    // Escreve os dados de cada postagem
    for (int i = 0; i < num_postagens; i++) {
        fprintf(arquivo, "%d,%s,%d,%d,%d\n",
                postagens[i].id,
                postagens[i].conteudo,
                postagens[i].likes,
                postagens[i].usuario_id,
                postagens[i].excluida);
    }

    fclose(arquivo);
    printf("Postagens salvas com�sucesso!\n");
}
// Carregar as informacoes salvas
void carregarUsuarios() {
    FILE *arquivo = fopen("usuarios.csv", "r");
    if (arquivo == NULL) {
        printf("Arquivo de usuarios nao encontrado. Criando novo arquivo.\n");
        return;
    }

    // Ignora o cabecalho do arquivo CSV
    char linha[256];
    fgets(linha, sizeof(linha), arquivo);

    // Le os dados de cada usuario
    while (fgets(linha, sizeof(linha), arquivo)) {
        Usuario novoUsuario;
        sscanf(linha, "%d,%[^,],%d,%[^,],%[^,],%d,%d,%d",
               &novoUsuario.id,
               novoUsuario.nome,
               &novoUsuario.idade,
               novoUsuario.senha,
               novoUsuario.email,
               &novoUsuario.bloqueado,
               &novoUsuario.num_postagens,
               &novoUsuario.num_seguidores);

        usuarios[num_usuarios++] = novoUsuario;
    }

    fclose(arquivo);
    printf("Usuarios carregados com sucesso!\n");
}

void carregarPostagens() {
    FILE *arquivo = fopen("postagens.csv", "r");
    if (arquivo == NULL) {
        printf("Arquivo de postagens nao encontrado. Criando novo arquivo.\n");
        return;
    }

    // Ignora o cabecalho do arquivo CSV
    char linha[256];
    fgets(linha, sizeof(linha), arquivo);

    // Le os dados de cada postagem
    while (fgets(linha, sizeof(linha), arquivo)) {
        Postagem novaPostagem;
        sscanf(linha, "%d,%[^,],%d,%d,%d",
               &novaPostagem.id,
               novaPostagem.conteudo,
               &novaPostagem.likes,
               &novaPostagem.usuario_id,
               &novaPostagem.excluida);

        postagens[num_postagens++] = novaPostagem;
    }

    fclose(arquivo);
    printf("Postagens carregadas com sucesso!\n");
}
//Funcao que acessa as funcionalidades do administrador
void entrarAdmin() {
    char senha[9];
    printf("Senha do administrador: ");
    scanf("%s", senha);
    if (strcmp(senha, admin_senha) != 0) {
        printf("Senha incorreta.\n");
        return;
    }

    int opcao;
    do {
        printf("\nMenu Administrador:\n");
        printf("1. Bloquear/Desbloquear Usuario\n");
        printf("2. Excluir Postagem\n");
        printf("3. Visualizar Todas as Postagens\n");
        printf("4. Visualizar Relatorio de Engajamento\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        //Chama a funcao que garante uma entrada valida
        opcao = lerEntradaValida();
        if (opcao == -1) {
            printf("Opcao invalida.\n");
            continue;
        }
        switch (opcao) {
            case 1: {
                char email[50];
                printf("Email do usuario: ");
                scanf("%s", email);
                int encontrado = 0;
                for (int i = 0; i < num_usuarios; i++) {
                    if (strcmp(usuarios[i].email, email) == 0) {
                        usuarios[i].bloqueado = !usuarios[i].bloqueado;
                        printf("Usuario %s foi %s.\n", usuarios[i].nome, usuarios[i].bloqueado ? "bloqueado" : "desbloqueado");
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("Usuario nao encontrado.\n");
                }
                break;
            }
            case 2: {
                excluirPostagemPorNomeENumero();
                break;
            }
            case 3: {
                exibirPostagens(-1, 1);
                break;
            }
            case 4: {
                printf("\nRelatorio de Engajamento:\n");
                int total_usuarios = num_usuarios;
                int total_postagens = 0;
                int total_likes = 0;

                for (int i = 0; i < num_usuarios; i++) {
                    printf("Usuario: %s\n", usuarios[i].nome);
                    printf("Seguidores: %d\n", usuarios[i].num_seguidores);
                    printf("Postagens: %d\n", usuarios[i].num_postagens);
                    int likes_usuario = 0;
                    for (int j = 0; j < num_postagens; j++) {
                        if (postagens[j].usuario_id == usuarios[i].id && !postagens[j].excluida) {
                            likes_usuario += postagens[j].likes;
                        }
                    }
                    printf("Likes totais: %d\n\n", likes_usuario);
                    total_postagens += usuarios[i].num_postagens;
                    total_likes += likes_usuario;
                }

                printf("Total de usuarios: %d\n", total_usuarios);
                printf("Total de postagens: %d\n", total_postagens);
                printf("Total de likes: %d\n", total_likes);
                break;
            }
            case 5:
                printf("Saindo da conta de administrador.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 5);
}
// Funcao que acessa as funcionalidades do Usuario
void entrarUsuario(int usuario_id) {
    int opcao;
    do {
        printf("\nMenu Usuario:\n");
        printf("1. Criar Postagem\n");
        printf("2. Curtir Postagem\n");
        printf("3. Seguir/Deixar de Seguir Usuario\n");
        printf("4. Visualizar Postagens\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        opcao = lerEntradaValida();
        if (opcao == -1) {
            printf("Opcao invalida.\n");
            continue;
        }
        switch (opcao) {
            case 1: {
                if (usuarios[usuario_id].num_postagens >= MAXIMO_POSTAGENS) {
                    printf("Limite de postagens atingido.\n");
                    break;
                }
                Postagem novaPostagem;
                printf("Conteudo da postagem: ");
                scanf(" %[^\n]", novaPostagem.conteudo);
                novaPostagem.id = num_postagens;
                novaPostagem.usuario_id = usuario_id;
                novaPostagem.likes = 0;
                novaPostagem.excluida = 0;
                postagens[num_postagens++] = novaPostagem;
                usuarios[usuario_id].postagens[usuarios[usuario_id].num_postagens++] = novaPostagem.id;
                printf("Postagem criada com sucesso! ID: %d\n", novaPostagem.id);
                break;
            }
            case 2: {
                // Aqui vai exibir as postagens do usuário que a pessoa segue;
                exibirPostagensSeguidores(usuario_id);

                int id;
                printf("ID da postagem a ser curtida: ");
                scanf("%d", &id);

                int encontrado = 0;
                for (int i = 0; i < num_postagens; i++) {
                    if (postagens[i].id == id && !postagens[i].excluida) {
                        // Verifica se o usuario atual segue o autor das postagens dos usuarios;
                        int segue_autor = 0;
                        for (int j = 0; j < usuarios[usuario_id].num_seguidores; j++) {
                            if (usuarios[usuario_id].seguidores[j] == postagens[i].usuario_id) {
                                segue_autor = 1;
                                break;
                            }
                        }

                        if (segue_autor) {
                            postagens[i].likes++;
                            printf("Postagem curtida com sucesso!\n");
                        } else {
                            printf("Voce so pode curtir postagens de usuarios que voce segue.\n");
                        }
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("Postagem nao encontrada.\n");
                }
                break;
            }
            case 3: {
                char email[50];
                printf("Email do usuario a seguir/deixar de seguir: ");
                scanf("%s", email);
                int encontrado = 0;
                for (int i = 0; i < num_usuarios; i++) {
                    if (strcmp(usuarios[i].email, email) == 0) {
                        if (usuarios[i].bloqueado){
                            printf("Este usuario esta bloqueado e nao pode ser seguido!\n");
                            break;
                        }

                        if (i == usuario_id) {
                            printf("Voce nao pode seguir a si mesmo.\n");
                            break;
                        }
                        int ja_segue = 0;
                        for (int j = 0; j < usuarios[usuario_id].num_seguidores; j++) {
                            if (usuarios[usuario_id].seguidores[j] == i) {
                                for (int k = j; k < usuarios[usuario_id].num_seguidores - 1; k++) {
                                    usuarios[usuario_id].seguidores[k] = usuarios[usuario_id].seguidores[k + 1];
                                }
                                usuarios[usuario_id].num_seguidores--;
                                printf("Voce deixou de seguir %s.\n", usuarios[i].nome);
                                ja_segue = 1;
                                break;
                            }
                        }
                        if (!ja_segue) {
                            usuarios[usuario_id].seguidores[usuarios[usuario_id].num_seguidores++] = i;
                            printf("Voce comecou a seguir %s.\n", usuarios[i].nome);
                        }
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("Usuario nao encontrado.\n");
                }
                break;
            }
            case 4: {
                exibirPostagens(usuario_id, 0);
                break;
            }
            case 5:
                printf("Saindo da conta de usuario.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 5);
}
//Funcao principal
int main() {
    setlocale(LC_ALL, "portuguese");
    carregarUsuarios();
    carregarPostagens();

    int opcao;
    do {
        printf("\nMenu Principal:\n");
        printf("1. Entrar na conta de administrador\n");
        printf("2. Cadastrar novo usuario\n");
        printf("3. Entrar na conta de usuario\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        opcao = lerEntradaValida();
        if (opcao == -1) {
            printf("Opcao invalida.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                entrarAdmin();
                break;
            case 2:
                cadastro_Usuario();
                break;
            case 3: {
                char email[50], senha[5];
                printf("Email: ");
                scanf("%s", email);
                printf("Senha: ");
                scanf("%s", senha);
                int encontrado = 0;
                for (int i = 0; i < num_usuarios; i++) {
                    if (strcmp(usuarios[i].email, email) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
                        if (usuarios[i].bloqueado) {
                            printf("Usuario bloqueado.\n");
                            break;
                        }
                        entrarUsuario(i);
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("Email ou senha incorretos.\n");
                    break;
                }

            }
            case 4:
                printf("Saindo do sistema.\n");
                salvarUsuarios();
                salvarPostagens();
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 4);

    return 0;
}

