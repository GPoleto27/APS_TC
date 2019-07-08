#ifndef AUTOMATO_H_INCLUDED
#define AUTOMATO_H_INCLUDED

#include <bits/stdc++.h>
using namespace std;

typedef struct t {	// Estrutura para representar as transi��es
	int inicial;	// Estado inicial
	char cons;		// Elemento a ser consumido
	int final;		// Estado final
} transicao;

typedef struct e {
	int n;			// Número do estado
	bool final;		// Se é final ou não
	vector<struct e*> transicoes;	// Transições (elemento representado no índice (0~127, ASCII))
} estado;

estado *criaEstado(const int);
vector<estado*> inicializaEstados (const int, const int*, const int);
void populaTransicoes(vector<estado*>, const transicao*, const int);
bool testarPalavra(const char[16], estado*);
vector<estado*> excluirInuteis(vector<estado*>);
void imprimeFormalizacao(vector<estado*>, vector<char>);

#endif // AUTOMATO_H_INCLUDED
