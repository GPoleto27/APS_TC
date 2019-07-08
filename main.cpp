#include "Automato.h"

int main() {
	register int i, j, k;
	int nEstados, nElementos, nFinais, nTransicoes, nPalavras;
	char palavra[16], c;
	bool eFinal, flag;
	int *finais, *naoFinais;
	vector<char> alfabeto;
	bool *estadosAcessiveis;
	transicao *transicoes;

	// Parte 1

	cin >> nEstados;
	if (nEstados > 10 || nEstados < 1)						// Se o número de estados é inválido retorna erro de código 1
		return 1;

	cin >> nElementos;
	if (nElementos > 10 || nElementos < 0)					// Se o número de elementos é inválido retorna erro de código 2
		return 2;

	for (i = 0; i < nElementos; i++) {						// Insere os elementos do alfabeto
		cin >> c;
		alfabeto.push_back(c);
	}

	cin >> nFinais;
	if (nFinais < 1 || nFinais > nEstados - 1)				// Se o número de estados finais é inválido retorna erro de código 3
		return 3;

	finais = (int*)malloc(nFinais * sizeof(int));			// Aloca o vetor de estados com o número de estados finais
	for (i = 0; i < nFinais; i++) {							// Recebe os estados finais
		cin >> finais[i];
		if (finais[i] < 0 || finais[i] > nEstados - 1)		// Se o elemento inserido é inválido retorna erro de código 4
			return 4;
	}

	cin >> nTransicoes;
	if (nTransicoes > 50 || nTransicoes < nEstados - 1)		// Se o número de transições é inválido retorna erro de código 5
		return 5;

	transicoes = (transicao*)malloc(nTransicoes * sizeof(transicao));
	for (i = 0; i < nTransicoes; i++) {											// Recebe as transições
		cin >> transicoes[i].inicial;
		if (transicoes[i].inicial > nEstados - 1 || transicoes[i].inicial < 0)	// Se o estado inicial da transição é inválido retorna erro de código 6
			return 6;

		cin >> transicoes[i].cons;
		for(j = 0; j < nElementos; j++) {
			if (transicoes[i].cons == alfabeto[j])
				break;
			else if (j == nElementos - 1)	// Se o caracter a ser consumido da transiçãoo não pertencer ao alfabeto retorna erro de código 7
				return 7;
		}

		cin >> transicoes[i].final;
		if (transicoes[i].final > nEstados - 1 || transicoes[i].final < 0)		// Se o estado final da transição é inválido retorna erro de código 8
			return 8;
	}

	cin >> nPalavras;
	if (nPalavras > 10)															// Se o número de palavras é inválido retorna erro de código 9
		return 9;

	vector<estado*> automato = inicializaEstados(nEstados, finais, nFinais);	// Inicializa o automato (grafo)
	populaTransicoes(automato, transicoes, nTransicoes);						// Popula as transições do automato (vector de estado*)

	for (i = 0; i < nPalavras; i++) {
		cin >> palavra;															// Recebe a palavra
		if (testarPalavra(palavra, automato[0]))								// Verifica a palavra
			cout << "Aceita.\n";
		else cout << "Rejeita.\n";
	}
	
	// Parte 2
	// Verifica se a função programa é total
	estado* aux;
	vector<char> auxAlfa = alfabeto;		// Alfabeto auxiliar (para verificar se todos os elementos possuem no mínimo uma transição)
	for (j = 0; j < nEstados; j++) {						// Passar pelos estados		
		aux = automato[i];									// Auxiliar para caminhar pelos estados
		for(i = 0; i < auxAlfa.size(); i++) {				// Todo o alfabeto a ser verificado
			if(aux->transicoes[ auxAlfa[i] ] != NULL) {		// Se existe uma transição para aquele elemento
				auxAlfa.erase(auxAlfa.begin()+(i--));		// Remove o elemento, pois já foi encontrada uma transição para ele
			}
		}
		if(!auxAlfa.size())									// Se todo o alfabeto já foi encontrado
			break;											// Não precisa verificar os outros estados
		else if(j == nEstados-1) {							// Se foi passado por todos os estados
			cout << "Esse AFD nao pode ser minimizado por não ser total\n";
			return 10;										// Retorna código de erro 10
		}
	}

	// Verifica se tem estados inacessíveis
	estadosAcessiveis = (bool*)calloc(nEstados, sizeof(bool));	// Aloca o vetor que representa se o estado é acessível (inicializa false)
	for(i = 0; i < nTransicoes; i++) {							// Passa por todas as transições
		estadosAcessiveis[ transicoes[i].final ] = true;		// Define como acessível o estado final da transição
	}
	for (i = 1; i < nEstados; i++) {							// Passa por todos os estados
		if(!estadosAcessiveis[i]) {								// Se algum estado não está marcado
			cout << "Esse AFD nao pode ser minimizado pois o estado q" << i << " não é acessível\n";
			return 11;											// Retorna erro de código 11
		}
	}

	naoFinais = (int*)malloc( (nEstados - nFinais) * sizeof(int) );	// Gera vetor de estados não-finais
	j = 0;
	for(i = 0; i < nEstados; i++) {								// Passa por todos os estados
		if(!automato[i]->final)									// Se aquele estado não é final
			naoFinais[j++] = automato[i]->n;					// Adiciona em naoFinais e incremeta o contador
	}

	bool equivalencia[nEstados][nEstados];						// Inicializa o vetor de equivalências
	memset(equivalencia, (int)false, nEstados*nEstados*sizeof(bool));	// Inicializa todos como falso

	// Vodka e magia eslava
	for ( i = 0; i < nFinais; i++ ) {							// Passa por todas as combinações de estados finais
		for( j = i + 1; j < nFinais; j++) {
			flag = false;										// Flag representa se um par de estados é distinguivel
			for( k = 0; k < nElementos; k++) {					// Passa por todos os elementos do alfabeto
																// Se encontrar alguma transição distinguivel
				if( automato[ finais[i] ]->transicoes[ (int)alfabeto[k] ] == NULL || automato[ finais[j] ]->transicoes[ (int)alfabeto[k] ] == NULL ||
					!( (automato[ finais[i] ]->transicoes[ (int)alfabeto[k] ]->final &&  automato[ finais[j] ]->transicoes[ (int)alfabeto[k] ]->final) || (!automato[ finais[i] ]->transicoes[ (int)alfabeto[k] ]->final &&  !automato[ finais[j] ]->transicoes[ (int)alfabeto[k] ]->final) ) ) {
					flag = true;								// Então o par é distinguivel
					break;										// Avança, não compara com outros elementos
				}
			}
			equivalencia[ finais[i] ][ finais[j] ] = !flag;		// Define o vetor de equivalencia dos estados i e j como a negação de distinguivel
		}
	}

	for ( i = 0; i < nEstados - nFinais; i++) {					// Passa por todas as combinações de estados não-finais
		for ( j = i + 1; j < nEstados - nFinais; j++) {
			flag = false;										// Flag representa se um par de estados é distinguivel
			for( k = 0; k < nElementos; k++) {					// Passa por todos os elementos do alfabeto
																// Se encontrar alguma transição distinguivel
				if(	automato[ naoFinais[i] ]->transicoes[ (int)alfabeto[k] ] == NULL || automato[ naoFinais[j] ]->transicoes[ (int)alfabeto[k] ] == NULL ||
					!( (automato[ naoFinais[i] ]->transicoes[ (int)alfabeto[k] ]->final &&  automato[ naoFinais[j] ]->transicoes[ (int)alfabeto[k] ]->final) || (!automato[ naoFinais[i] ]->transicoes[ (int)alfabeto[k] ]->final &&  !automato[ naoFinais[j] ]->transicoes[ (int)alfabeto[k] ]->final) ) ) {
					flag = true;								// Então o par é distinguivel
					break;										// Avança, não compara com outros elementos
				}
			}
			equivalencia[ naoFinais[i] ][ naoFinais[j] ] = !flag;	// Define o vetor de equivalencia dos estados i e j como a negação de distinguivel
		}
	}

	cout << "Estados equivalentes:\n";
	for(i = 0; i < nEstados; i++) {
		for(j = 0; j < nEstados; j++) {
			if(equivalencia[i][j]) {
				cout << i << " e " << j << "\n";				// Imprime os estados equivalentes
				if (i < j) {									// Se i < j
					for(k = 0; k < nTransicoes; k++) {			// Altera as ocorrências de j na lista de transições por i
						if (transicoes[k].inicial == j)
							transicoes[k].inicial = i;
						if (transicoes[k].final	== j)
							transicoes[k].final = i;
					}
					for(k = 0; k < nFinais; k++) {				// Altera as ocorrências de j na lista de estados finais por i
						if(finais[k] == j)
							finais[k] = i;
					}
				}
				else {											// Se j < i
					for(k = 0; k < nTransicoes; k++) {			// Altera as ocorrências de i na lista de transições por j
						if (transicoes[k].inicial == i)
							transicoes[k].inicial = j;
						if (transicoes[k].final	== i)
							transicoes[k].final = j;
					}
					for(k = 0; k < nFinais; k++) {				// Altera as ocorrências de i na lista de estados finais por j
						if(finais[k] == i)
							finais[k] = j;
					}
				}
			}
		}
	}

	vector<estado*> minimizado = inicializaEstados(nEstados, finais, nFinais);	// Inicializa o automato minimizado com o mesmo número de estados, porém com a nova lista de finais 
	populaTransicoes(minimizado, transicoes, nTransicoes);						// Popula as transições com a nova lista de transições
	minimizado = excluirInuteis(minimizado); 									// Exclui estados sem transições (o que inclui um estado de cada par de estados equivalentes já que um deles são vai ter transições)
	imprimeFormalizacao(minimizado, alfabeto);									// Imprime a formalização do automato minimizado

return 0;
}
