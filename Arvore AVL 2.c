#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    short valor, altura;
    struct No *esquerdo, *direito;
} No;

No* novoNo(short x) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = x;
    novo->altura = 1;
    novo->esquerdo = novo->direito = NULL;
    return novo;
}

short altura(No* no) {
    return no ? no->altura : 0;
}

int balanceamento(No* no) {
    return no ? altura(no->esquerdo) - altura(no->direito) : 0;
}

void atualizarAltura(No* no) {
    if (no)
        no->altura = 1 + (altura(no->esquerdo) > altura(no->direito) ? altura(no->esquerdo) : altura(no->direito));
}

No* rotacaoDireita(No* y) {
    No* x = y->esquerdo;
    No* T2 = x->direito;
    x->direito = y;
    y->esquerdo = T2;
    atualizarAltura(y);
    atualizarAltura(x);
    return x;
}

No* rotacaoEsquerda(No* x) {
    No* y = x->direito;
    No* T2 = y->esquerdo;
    y->esquerdo = x;
    x->direito = T2;
    atualizarAltura(x);
    atualizarAltura(y);
    return y;
}

No* inserir(No* no, short valor) {
    if (!no) return novoNo(valor);
    if (valor < no->valor) no->esquerdo = inserir(no->esquerdo, valor);
    else if (valor > no->valor) no->direito = inserir(no->direito, valor);
    else return no;
    atualizarAltura(no);
    int balance = balanceamento(no);
    if (balance > 1 && valor < no->esquerdo->valor) return rotacaoDireita(no);
    if (balance < -1 && valor > no->direito->valor) return rotacaoEsquerda(no);
    if (balance > 1 && valor > no->esquerdo->valor) {
        no->esquerdo = rotacaoEsquerda(no->esquerdo);
        return rotacaoDireita(no);
    }
    if (balance < -1 && valor < no->direito->valor) {
        no->direito = rotacaoDireita(no->direito);
        return rotacaoEsquerda(no);
    }
    return no;
}

void inorder(No* no) {
    if (!no) return;
    inorder(no->esquerdo);
    printf("%d ", no->valor);
    inorder(no->direito);
}

int main() {
    No* raiz = NULL;
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 40);
    printf("Árvore AVL em ordem:\n");
    inorder(raiz);
    return 0;
}

