#include <bits/stdc++.h>

using namespace std;

int main()
{
    int nEstados, nElementos, nFinais, nTransicoes, nPalavras, i, j;
    char *alfabeto, *finais, *transicoes;
    string *palavras;

    cin >> nEstados >> nElementos;
    alfabeto = (char*) malloc( nElementos * sizeof (char) );
    for (i = 0; i < nElementos; i++) {
        cin >> alfabeto[i];
    }

    cin >> nFinais;
    finais = (char*) malloc( nFinais * sizeof (char) );
    for (i = 0; i < nFinais; i++) {
        cin >> finais[i];
    }

    cin >> nTransicoes;
    finais = (char*) malloc( 3 * nFinais * sizeof (char) );
    for (i = 0; i < nTransicoes; i++) {
        for (j = 0; j < 3; j++){
            cin >> transicoes[i][j];
        }
    }

    cin >> nPalavras;
    palavras = (string*) malloc( nPalavras * sizeof (string) );
    for (i = 0; i < nPalavras; i++) {
        cin >> palavras[i];
    }

    return 0;
}
