#include "Automato.h"

estado *criaEstado(const int n) {			// Cria uma struct estado
	estado *novo = new estado;				// Aloca
	novo->n = n;							// Define o número do estado
	novo->final = false;					// Define como não-final
	for(int i = 0; i <= 127; i++)
		novo->transicoes.push_back(NULL);	// Inicializa todas as transições como NULL
	return novo;							// Retorna o estado criado
}

vector<estado*> inicializaEstados (const int nEstados, const int *finais, const int nFinais) {	// Inicializa o automato
	vector<estado*> automato;					// Cria o automato
	int j = 0;									// Para percorrer a lista de estados finais
	for(int i = 0; i < nEstados; i++) {			// Passa por todos os estados
		automato.push_back(criaEstado(i));		// Insere no automato um estado criado a partir do indice i
		if(j < nFinais && i == finais[j]) {		// Se ainda não percorri todos os finais, verifico se esse estadodeve ser final
			automato[i]->final = true;			// Defino como final
			j++;								// Avanço a lista de estados finais
		}
	}
	return automato;							// Retorno o automato criado
}

void populaTransicoes(vector<estado*> automato, const transicao *transicoes, const int nTransicoes) {	// Popular transiçoes
	for(int i = 0; i < nTransicoes; i++) {		// Percorrer toda a lista de transições
			// O estado no índice "estado inicial" do automato tem uma transição no índice "elemento a ser consumido" que aponta para o estado no índice "estado final" do automato
			automato[ transicoes[i].inicial ]->transicoes[ (int)transicoes[i].cons ] = automato[ transicoes[i].final ];
	}
}

bool testarPalavra(const char palavra[16], estado* inicial) {	// Testar se uma palavra é aceita ou não
	estado* aux = inicial;										// Para percorrer o grafo (automato)
	int i = 0;													// Para percorrer a palavra
	while(palavra[i] != '\0') {									// Enquanto não cheguei no fim da palavra
		if( aux->transicoes[ (int)palavra[i] ] != NULL ) {		// Se existe uma transição que consome aquele elemento
			aux = aux->transicoes[ (int)palavra[i] ];			// Transito para o estado final da transição
			i++;												// Avanço na palavra
		} else return false;									// Se não existe essa transição a palavra é rejeitada
	}
	return aux->final;											// Após percorrer a palavra, retorno se o estado atual é final (aceita) ou não (rejeitada)
}

vector<estado*> excluirInuteis(vector<estado*> automato) {		// Excluir estados que não tenham transições
    unsigned int i, j, k;
	vector<estado*> novo;										// Novo automato sem estados inuteis
	vector<int> inuteis;										// Vetor com o "id" de cada estado inutil
	bool flag;													// Sé é inútil (true)
	for(i = 0; i < automato.size(); i++) {						// Percorrer o automato
		flag = false;											// Define como útil
		for(j = 0; j <= 127; j++) {								// Percorre como todos os ponteiros transições
			if(automato[i]->transicoes[j] != NULL)				// Se existe uma transição que leve a outro estado
				break;											// Estado útil
			if(j == 127)										// Se já percorri todas as possíveis transições
				flag = true;									// Estado inútil
		}
		if(!flag)												// Se é útil
			novo.push_back(automato[i]);						// Insere no novo automato
		else													// Se é inútil
            inuteis.push_back(automato[i]->n);					// Adiciona na lista de inúteis
	}
	for(i = 0; i < novo.size(); i++) {							// Percorre todo o automato novo
	    for(j = 0; j <= 127; j++) {								// Percorre todas as possíveis transições
			for(k = 0; k < inuteis.size(); k++) {				// Percorre a lista de estados inúteis
				if(novo[i]->transicoes[j] != NULL && novo[i]->transicoes[j]->n == inuteis[k]) // Se alguma transição leva a um estado inútil
					novo[i]->transicoes[j] = NULL;				// "Exclui" essa transição
			}
		}
    }
	return novo;												// Retorna seu novo automato
}

void imprimeFormalizacao(vector<estado*> automato, vector<char>alfabeto) {	// É só imprimir, cara
	unsigned int i;
	int k = 0;
	cout << "M = {{";
	for(i = 0; i < automato.size()-1; i++) {
		cout << "q" << automato[i]->n << ",";
	}
	cout << "q" << automato[automato.size()-1]->n << "}, {";
	for(i = 0; i < alfabeto.size()-1; i++) {
		cout << alfabeto[i] << ",";
	}
	cout << alfabeto[alfabeto.size()-1] << "}, f, q" << automato[0]->n << ", {";
	for(i = 0; i < automato.size(); i++) {
		if(automato[i]->final) {
			if (k)
				cout << ",";
			cout << "q" << automato[i]->n;
			k++;
		}

	}
	cout << "}}\nf = {\n";
	for(i = 0; i < automato.size(); i++) {
		for(int j = 0; j <= 127; j++)
			if(automato[i]->transicoes[j] != NULL)
				printf("q%d %c q%d\n", automato[i]->n, j, automato[i]->transicoes[j]->n);
	}
	cout << "}\n";
	return;
}
