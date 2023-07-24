//Trabalho prático 3 - INF110
//Aluno: Leonardo de Andrade Porto 
//Matrícula: 112681

#include<iostream>
#include <fstream>
#include <cstring>
#include"tratamentos.cpp"

using namespace std;

int main(){

    unsigned char imagem_TC[500][500], imagem_CL[500][500][3]; // Matrizes para armazenar as imagens (CL - colorido, TC - tons de cinza);
    int w, h;                                                  // Inteiros para, respectivamente, largura e altura da imagem
    char tipo[4];                                              // Cadeia d caracteres para o tipo da imagem;
    string nome, path;                                         // Strings o nome e o caminho da imagem
    ifstream filein;                                           // Arquivo para a imagem original
    ofstream fileout;                                          // Arquivo para a imagem alterada
    
    //*Leitura da imagem e abertura do arquivo-----------------------

    cout << "Digite o nome do arquivo PNM: ";
    cin >> nome;
    path = "images/" + nome;

    filein.open(path,ios::in);
    if (!filein) {
		cout << "Nao consegui abrir arquivo " << path << endl;
		return 0;
	}
    cout << endl;

    //---------------------------------------------------------------

    //*Leitura do cabeçalho------------------------------------------

    char comentario[200], c; // Variáveis auxiliares
    int valor;               // Variável auxiliar

    // Leitura de tipo
    filein >> tipo;
    filein.get();

    // Tratamento de tipo
    if (strcmp(tipo,"P1")==0) {
		cout << "Imagem preto e branco" << endl;
		cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
		filein.close();
		return 0;
	}
	else if (strcmp(tipo,"P2")==0) {
		cout << "Imagem em tons de cinza" << endl;
    }
	else if (strcmp(tipo,"P3")==0) {
		cout << "Imagem colorida" << endl;
	}
	else if (strcmp(tipo,"P4")==0 || strcmp(tipo,"P5")==0 || strcmp(tipo,"P6")==0) {
		cout << "Imagem no formato RAW\n";
		cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
		filein.close();
		return 0;
	}

    // Descarte de comentarios (linhas começadas em '#')
    while((c = filein.get()) == '#')
		filein.getline(comentario,200);
    filein.putback(c);

    // Leitura do tamanho da imagem
    filein >> w >> h;
    cout << "Tamanho: " << w << " * " << h << endl << endl;

    // Tratamento do tamanho da imagem
    if (w > MAXH) {
		cout << "Desculpe, ainda nao trabalho com imagens com mais de " << MAXH << " pixels de largura." << endl;
		filein.close();
		return 0;
	}
	if (h > MAXH) {
		cout << "Desculpe, ainda nao trabalho com imagens com mais de " << MAXH << " pixels de altura." << endl;
		filein.close();
		return 0;
	}
    
    // Leitura do valor do maior pixel (assumiremos como 255)
    filein >> valor;

    //---------------------------------------------------------------

    //*Leitura dos pixels da imagem----------------------------------

    // Se a imagem for em tons de cinza
    if (strcmp(tipo,"P2")==0){
        for(int i = 0 ; i < h ; i++)
            for(int j = 0 ; j < w ; j++){
                filein >> valor;
                imagem_TC[i][j] = (unsigned char)valor;
            }
    }
    // Se a imagem for colorida
    else{

        for(int i = 0 ; i < h ; i++)
            for(int j = 0 ; j < w ; j++)
                for(int k = 0 ; k < 3 ; k++){
                    filein >> valor;
                    imagem_CL[i][j][k] = (unsigned char)valor;
                }

    }

    filein.close();

    //---------------------------------------------------------------

    //*Menu para tipos de tratamento---------------------------------

    int opt;
    do{

        cout << "Selecione o tipo de tratamento de imagem:"<<endl;
        cout << "1 - Escurecer" << endl;    
        cout << "2 - Clarear" << endl;    
        cout << "3 - Negativo" << endl;    
        cout << "4 - Espelhar" << endl;    
        cout << "5 - Filtro de Sobel" << endl;
        cout << "6 - Filtro de desfoque gaussiano" << endl;
        cout << "7 - Filtro de realce" << endl;
        cout << "8 - Filtro de Laplace" << endl;
        cout << "9 - Converter imagem em tons de cinza (apenas para imagens coloridas)" << endl;
        cout << "10 - Chroma key" << endl;
        cout << '-';
        cin >> opt;

        if(opt < 1 || opt > 10) // Caso a opção escolhida não seja uma opção válida
            cout << "Opção inválida, digite outro valor" << endl;
    
    }while(opt < 1 || opt > 10);

    //---------------------------------------------------------------

    //*Tratamento da imagem------------------------------------------

    if(opt == 1){ // Escurecimento
        
        int fator;

        cout << "Qual é o fator de escurecimento? ";
        cin >> fator;
        level(fator);

        // Para imagens em tons de cinza
        if(strcmp(tipo,"P2")==0)
            escurecer_TC(imagem_TC, h, w, fator);
        // Para imagens coloridas
        else
            escurecer_CL(imagem_CL, h, w, fator);

    }else if(opt == 2){ // Clareamento;

        int fator;

        cout << "Qual é o fator de clareamento? ";
        cin >> fator;
        level(fator);

        // Para imagens em tons de cinza
        if(strcmp(tipo,"P2")==0)
            clarear_TC(imagem_TC, h, w, fator);
        // Para imagens coloridas
        else
            clarear_CL(imagem_CL, h, w, fator);

    }else if(opt == 3){ // Negativo

        // Para imagens em tons de cinza
        if(strcmp(tipo,"P2")==0)
            negativo_TC(imagem_TC, h, w);   
        // Para imagens coloridas
        else
            negativo_CL(imagem_CL, h, w);

    }else if(opt == 4){ // Espelhar
        
        // Para imagens em tons de cinza
        if(strcmp(tipo,"P2")==0)
            espelha_TC(imagem_TC, h, w);
        // Para imagens coloridas
        else
            espelha_CL(imagem_CL, h, w);

    }else if(opt == 5){ // Filtro de Sobel
        
        int sobel;
        
        // Menu para escolha do tipo de filtro de
        do{

        cout << "Selecione o tipo de sobel que você quer aplicar:"<<endl;
        cout << "1 - Média aritmética" << endl;    
        cout << "2 - Valor máximo" << endl;    
        cout << "3 - Magnitude do gradiente" << endl;  
        cout << '-';  
        cin >> sobel;
        if(sobel < 1 || sobel > 3) // Caso o tipo de sobel escolhido não seja um tipo de sobel válido
            cout << "Tipo inválido, digite outro valor" << endl;
        
        }while(sobel < 1 || sobel > 3);

        // Para imagens em tons de cinza
        if(strcmp(tipo,"P2")==0)
            sobel_TC(imagem_TC, h, w, sobel);
        // Para imagens coloridas
        else
            sobel_CL(imagem_CL, h, w, sobel);
        

    }else if(opt == 6){ // Desfoque gaussiano

        double filtro[3][3] = {{1.0/16, 2.0/16, 1.0/16}, {2.0/16, 4.0/16, 2.0/16}, {1.0/16, 2.0/16, 1.0/16}}; // Matriz 3x3 que define o filtro
        
        // Para imagens em tons de cinza
        if(strcmp(tipo,"P2")==0)
            conv_TC(imagem_TC, filtro, h, w);
        // Para imagens coloridas
        else
            conv_CL(imagem_CL, filtro, h, w);

    }else if(opt == 7){ // Realce

        double filtro[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}; // Matriz 3x3 que define o filtro
        
        // Para imagens em tons de cinza
        if(strcmp(tipo,"P2")==0)
            conv_TC(imagem_TC, filtro, h, w);
        // Para imagens coloridas
        else
            conv_CL(imagem_CL, filtro, h, w);

    }else if(opt == 8){ // Filtro de Laplace

        double filtro[3][3] = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}; // Matriz 3x3 que define o filtro
        
        // Para imagens em tons de cinza
        if(strcmp(tipo,"P2")==0)
            conv_TC(imagem_TC, filtro, h, w);
        // Para imagens coloridas
        else
            conv_CL(imagem_CL, filtro, h, w);

    }else if(opt == 9){ // Converter em tons de cinza
        
        // Para imagens em tons de cinza
        if(strcmp(tipo,"P2")==0){
            cout << "Essa imagem já está em tons de cinza.";
            return 0;
        // Para imagens coloridas
        }else
            cinza(imagem_CL, imagem_TC, tipo, h, w);
    }else{ // Chroma key

        ifstream chromain; 

        if (!(strcmp(tipo,"P3")==0)){ // Tratamento do tipo de imagem de fundo
		    cout << "Não aceitamos imagens que não sejam coloridas para esse tipo de tratamento" << endl;
            return 0;
	    }

        while (true){ // Tratamento e leitura da imagem de chroma key

            cout << "Digite o nome do arquivo que terá o fundo retirado: ";
            cin >> nome;
            path = "chromas/" + nome;

            chromain.open(path,ios::in);
            if (!chromain) {
                cout << "Nao consegui abrir arquivo " << path << endl;
                return 0;
            }

            chromain >> tipo;
            chromain.get();

            if (!(strcmp(tipo,"P3")==0)){
                cout << "Não aceitamos imagens que não sejam coloridas para esse tipo de tratamento" << endl;
                return 0;
            }

            // Descarte de comentarios (linhas começadas em '#')
            while((c = chromain.get()) == '#')
                chromain.getline(comentario,200);
            chromain.putback(c);

            int a, l;

            chromain >> l >> a;
            if (l != w || a != h){
                cout << "A imagem escolhida deve ter dimensões iguais às da imagem de plano de fundo, digite novamente" << endl;
                continue;
            }
            break;

        }

        chromain >> valor;

        unsigned char chromak[500][500][3];

        for(int i = 0 ; i < h ; i++)
            for(int j = 0 ; j < w ; j++)
                for(int k = 0 ; k < 3 ; k++){
                    chromain >> valor;
                    chromak[i][j][k] = (unsigned char)valor;
                }

        chromain.close();

        double opacidade;
        cout << "Digite a porcentagem de opacidade da imagem sobre o plano de fundo (0-100): ";
        cin >> opacidade;
        opacidade = opacidade>100?100:opacidade;
        opacidade = opacidade<0?0:opacidade;

        chroma(imagem_CL, chromak, h, w, opacidade);

    }

    //---------------------------------------------------------------

    //*Gravação da imagem--------------------------------------------

    path = ""; // Caminho para salvar a imagem
    cout << "Digite o nome do novo arquivo: ";
    cin >> nome; // Nome do novo arquivo
    path = "resultados/" + nome;

	fileout.open(path,ios::out);
	if (!fileout) {
		cout << "Nao consegui criar " << nome << endl;
		return 0;
	}

	fileout << tipo << endl;
	fileout << "# TP3-INF110, by AGS\n";
    fileout << "# TP3-INF110, trabalho feito por Leonardo Porto 112681 \n";
	fileout << w << " " << h;
	fileout << " " << 255 << endl;

    if (strcmp(tipo,"P2")==0){ //Para imagens escuras

        for(int i = 0 ; i < h ; i++)
            for(int j = 0 ; j < w ; j++)
                fileout << (int)imagem_TC[i][j] << endl;

    }else{ //Para imagens coloridas

        for(int i = 0 ; i < h ; i++)
            for(int j = 0 ; j < w ; j++)
                for(int k = 0 ; k < 3 ; k++)
                    fileout << (int)imagem_CL[i][j][k] << endl;

    }

	fileout.close();

    //---------------------------------------------------------------

    return 0;
}

// norma do vetor