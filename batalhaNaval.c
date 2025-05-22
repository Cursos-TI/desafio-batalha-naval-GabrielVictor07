#include <stdio.h>
#define TAM 10
#define TAM_HAB 5 
#define NAVIO 3
#define HABILIDADE 5

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;
}

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO FINAL ===\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Posiciona um navio no tabuleiro
void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int dx, int dy) {
    for (int i = 0; i < 3; i++) {
        int l = linha + i * dx;
        int c = coluna + i * dy;
        tabuleiro[l][c] = NAVIO;
    }
}

// Cria matriz de habilidade em formato de cone
void criarCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= (TAM_HAB / 2) - i && j <= (TAM_HAB / 2) + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria matriz de habilidade em formato de cruz
void criarCruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria matriz de habilidade em formato de octaedro (losango)
void criarOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2) <= TAM_HAB / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    int offset = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int linhaTab = origemLinha + (i - offset);
            int colunaTab = origemColuna + (j - offset);

            if (linhaTab >= 0 && linhaTab < TAM && colunaTab >= 0 && colunaTab < TAM) {
                if (habilidade[i][j] == 1 && tabuleiro[linhaTab][colunaTab] != NAVIO)
                    tabuleiro[linhaTab][colunaTab] = HABILIDADE;
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    int cone[TAM_HAB][TAM_HAB], cruz[TAM_HAB][TAM_HAB], octaedro[TAM_HAB][TAM_HAB];

    inicializarTabuleiro(tabuleiro);

    // === Posicionamento dos navios ===
    posicionarNavio(tabuleiro, 1, 1, 0, 1); // Horizontal
    posicionarNavio(tabuleiro, 5, 7, 1, 0); // Vertical
    posicionarNavio(tabuleiro, 3, 3, 1, 1); // Diagonal principal
    posicionarNavio(tabuleiro, 2, 6, 1, -1); // Diagonal secundária

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // === Aplicação das habilidades no tabuleiro ===
    aplicarHabilidade(tabuleiro, cone, 2, 2);       // Cone no centro superior-esquerdo
    aplicarHabilidade(tabuleiro, cruz, 6, 5);       // Cruz mais à direita
    aplicarHabilidade(tabuleiro, octaedro, 4, 4);   // Octaedro no centro

    // === Exibição final ===
    imprimirTabuleiro(tabuleiro);

    return 0;
}
