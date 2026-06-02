#include <stdio.h>

#define MAX_LEITURAS 100

void limparEntrada() {
    int caractere;

    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

int lerInteiro(const char mensagem[]) {
    int valor;
    int resultado;

    printf("%s", mensagem);
    resultado = scanf("%d", &valor);

    while (resultado != 1) {
        limparEntrada();
        printf("Entrada invalida. Digite um numero inteiro: ");
        resultado = scanf("%d", &valor);
    }

    limparEntrada();
    return valor;
}

float lerFloat(const char mensagem[]) {
    float valor;
    int resultado;

    printf("%s", mensagem);
    resultado = scanf("%f", &valor);

    while (resultado != 1) {
        limparEntrada();
        printf("Entrada invalida. Digite um numero: ");
        resultado = scanf("%f", &valor);
    }

    limparEntrada();
    return valor;
}

void exibirMenu() {
    printf("\n========== MONITORAMENTO DE MISSAO ESPACIAL ==========\n");
    printf("1 - Inserir dados da missao\n");
    printf("2 - Visualizar status\n");
    printf("3 - Executar analise\n");
    printf("0 - Encerrar sistema\n");
    printf("Escolha uma opcao: ");
}

void inserirDados(float temperaturas[], float energias[], int comunicacoes[], int *totalLeituras) {
    if (*totalLeituras >= MAX_LEITURAS) {
        printf("\nLimite de leituras atingido.\n");
        return;
    }

    printf("\n--- Cadastro da leitura %d ---\n", *totalLeituras + 1);

    temperaturas[*totalLeituras] = lerFloat("Temperatura da nave em Celsius: ");

    energias[*totalLeituras] = lerFloat("Nivel de energia em porcentagem: ");

    while (energias[*totalLeituras] < 0 || energias[*totalLeituras] > 100) {
        energias[*totalLeituras] = lerFloat("Energia invalida. Digite um valor entre 0 e 100: ");
    }

    comunicacoes[*totalLeituras] = lerInteiro("Status da comunicacao (1 = ativa, 0 = falha): ");

    while (comunicacoes[*totalLeituras] != 0 && comunicacoes[*totalLeituras] != 1) {
        comunicacoes[*totalLeituras] = lerInteiro("Comunicacao invalida. Digite 1 para ativa ou 0 para falha: ");
    }

    (*totalLeituras)++;
    printf("\nDados cadastrados com sucesso.\n");
}

float calcularMediaTemperatura(float temperaturas[], int totalLeituras) {
    float soma = 0;

    for (int i = 0; i < totalLeituras; i++) {
        soma += temperaturas[i];
    }

    return soma / totalLeituras;
}

float calcularMediaEnergia(float energias[], int totalLeituras) {
    float soma = 0;

    for (int i = 0; i < totalLeituras; i++) {
        soma += energias[i];
    }

    return soma / totalLeituras;
}

void analisarLeitura(float temperatura, float energia, int comunicacao) {
    int alerta = 0;

    if (temperatura > 80) {
        printf("Alerta de superaquecimento.\n");
        alerta = 1;
    }

    if (energia < 20) {
        printf("Economia de energia recomendada.\n");
        alerta = 1;
    }

    if (comunicacao == 0) {
        printf("Falha de comunicacao.\n");
        alerta = 1;
    }

    if (alerta == 0) {
        printf("Missao em condicao operacional normal.\n");
    }
}

void visualizarStatus(float temperaturas[], float energias[], int comunicacoes[], int totalLeituras) {
    if (totalLeituras == 0) {
        printf("\nNenhum dado cadastrado.\n");
        return;
    }

    int ultima = totalLeituras - 1;

    printf("\n--- Status atual da missao ---\n");
    printf("Temperatura atual: %.2f C\n", temperaturas[ultima]);
    printf("Energia atual: %.2f%%\n", energias[ultima]);

    if (comunicacoes[ultima] == 1) {
        printf("Comunicacao: ativa\n");
    } else {
        printf("Comunicacao: falha\n");
    }

    printf("Status operacional: ");
    analisarLeitura(temperaturas[ultima], energias[ultima], comunicacoes[ultima]);
}

void executarAnalise(float temperaturas[], float energias[], int comunicacoes[], int totalLeituras) {
    int totalSuperaquecimento = 0;
    int totalEnergiaBaixa = 0;
    int totalFalhaComunicacao = 0;

    if (totalLeituras == 0) {
        printf("\nNenhum dado cadastrado para analise.\n");
        return;
    }

    printf("\n--- Analise das leituras cadastradas ---\n");

    for (int i = 0; i < totalLeituras; i++) {
        printf("\nLeitura %d\n", i + 1);
        printf("Temperatura: %.2f C | Energia: %.2f%% | Comunicacao: %d\n",
               temperaturas[i], energias[i], comunicacoes[i]);

        analisarLeitura(temperaturas[i], energias[i], comunicacoes[i]);

        if (temperaturas[i] > 80) {
            totalSuperaquecimento++;
        }

        if (energias[i] < 20) {
            totalEnergiaBaixa++;
        }

        if (comunicacoes[i] == 0) {
            totalFalhaComunicacao++;
        }
    }

    printf("\n--- Resumo geral ---\n");
    printf("Total de leituras: %d\n", totalLeituras);
    printf("Media de temperatura: %.2f C\n", calcularMediaTemperatura(temperaturas, totalLeituras));
    printf("Media de energia: %.2f%%\n", calcularMediaEnergia(energias, totalLeituras));
    printf("Alertas de superaquecimento: %d\n", totalSuperaquecimento);
    printf("Alertas de energia baixa: %d\n", totalEnergiaBaixa);
    printf("Falhas de comunicacao: %d\n", totalFalhaComunicacao);
}

int main() {
    float temperaturas[MAX_LEITURAS];
    float energias[MAX_LEITURAS];
    int comunicacoes[MAX_LEITURAS];
    int totalLeituras = 0;
    int opcao;

    do {
        exibirMenu();
        opcao = lerInteiro("");

        switch (opcao) {
            case 1:
                inserirDados(temperaturas, energias, comunicacoes, &totalLeituras);
                break;
            case 2:
                visualizarStatus(temperaturas, energias, comunicacoes, totalLeituras);
                break;
            case 3:
                executarAnalise(temperaturas, energias, comunicacoes, totalLeituras);
                break;
            case 0:
                printf("\nSistema encerrado.\n");
                break;
            default:
                printf("\nOpcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}
