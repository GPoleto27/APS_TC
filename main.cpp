#include <bits/stdc++.h>
using namespace std;

typedef struct t {
	int inicial;
	char cons;
	int final;
} transicao;

bool testarPalavra(const char palavra[16], const transicao *transicoes, const int nTransicoes, const int *finais, const int nFinais) {
	int estado = 0;
	int i = 0, j;
	while (palavra[i] != '\0') {
		for (j = 0; j < nTransicoes; j++) {
			if (transicoes[j].inicial == estado) {
				if(transicoes[j].cons == palavra[i]) {
					estado = transicoes[j].final;
					break;
				}
			}
			if (j == nTransicoes - 1)
				return false;
		}
		i++;
	}
	for (i = 0; i < nFinais; i++) {
		if (estado == finais[i])
			return true;
	}
	return false;
}

int main() {
	register int i, j;
	int nEstados, nElementos, nFinais, nTransicoes, nPalavras;
	char *alfabeto;
	int *finais;
	transicao *transicoes;
	char palavra[16];

	cin >> nEstados;
	if (nEstados > 10 || nEstados < 1)
		return 1;

	cin >> nElementos;
	if (nElementos > 10 || nElementos < 0)
		return 2;

	alfabeto = (char*)malloc(nElementos * sizeof(char));
	for (i = 0; i < nElementos; i++) {
		cin >> alfabeto[i];
	}

	cin >> nFinais;
	if (nFinais < 1 || nFinais > nElementos - 1)
		return 3;

	finais = (int*)malloc(nFinais * sizeof(int));
	for (i = 0; i < nFinais; i++) {
		cin >> finais[i];
		if (finais[i] < 0 || finais[i] > nEstados - 1)
			return 4;
	}

	cin >> nTransicoes;
	if (nTransicoes > 50 || nTransicoes < nEstados - 1)
		return 5;

	transicoes = (transicao*) malloc(nTransicoes * sizeof(transicao));
	for (i = 0; i < nTransicoes; i++) {
		cin >> transicoes[i].inicial;
		if (transicoes[i].inicial > nEstados - 1 || transicoes[i].inicial < 0)
			return 5;

		cin >> transicoes[i].cons;
		for(j = 0; j < nElementos; j++) {
			if (transicoes[i].cons == alfabeto[j])
				break;
			else if (j == nElementos - 1)
				return 6;
		}

		cin >> transicoes[i].final;
		if (transicoes[i].final > nEstados - 1 || transicoes[i].final < 0)
			return 7;
	}

	cin >> nPalavras;
	if (nPalavras > 10)
		return 8;

	for (i = 0; i < nPalavras; i++) {
		cin >> palavra;
		if (testarPalavra(palavra, transicoes, nTransicoes, finais, nFinais))
			cout << "Aceita.\n";
		else cout << "Rejeita.\n";
	}

return 0;
}
