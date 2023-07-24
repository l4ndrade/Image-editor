#include<iostream>
#include<cmath>
using namespace std;

const int MAXH = 500;

// Troca os valores de duas variáveis
void troca(unsigned char &a, unsigned char &b){ 
    unsigned char aux;
    aux = a;
    a = b;
    b = aux;
}

// Nivela um valor inteir o para estar no intervalo [0, 255]
void level(int &valor){ 
    if(valor > 255)
        valor = 255;
    if(valor < 0)
        valor = 0;
    return;
}

// Cria uma matriz cópia outra, mas com uma borda de 0's em volta da matriz original (apenas em imagens em tons de cinza)
void borda_TC(unsigned char imagem[MAXH][MAXH], unsigned char novaimagem[MAXH + 2][MAXH + 2], int h, int w){
    
    h+=2;
    w+=2;

    for(int i = 0 ; i < h ; i++)
        for(int j = 0 ; j < w ; j++){
            if(i == 0 || i == h-1 || j == 0 || j == w-1)
                novaimagem[i][j] = 0;
            else{
                novaimagem[i][j] = imagem[i-1][j-1];
            }
        } 

}

// Cria uma matriz cópia outra, mas com uma borda de 0's em volta da matriz original (apenas em imagens coloridas)
void borda_CL(unsigned char imagem[MAXH][MAXH][3], unsigned char novaimagem[MAXH + 2][MAXH + 2][3], int h, int w){
    
    h+=2;
    w+=2;

    for(int i = 0 ; i < h ; i++)
        for(int j = 0 ; j < w ; j++)
            for(int k = 0 ; k < 3 ; k++){
                if(i == 0 || i == h-1 || j == 0 || j == w-1)
                    novaimagem[i][j][k] = 0;
                else{
                    novaimagem[i][j][k] = imagem[i-1][j-1][k];
                }
        } 

}


// Copia uma matriz bidimensional
void copia_matriz2(unsigned char base[MAXH][MAXH], unsigned char copia[MAXH][MAXH], int h, int w){ 
    
    for(int i = 0 ; i < h ; i++)
        for(int j = 0 ; j < w ; j++)
            copia[i][j] = base[i][j];
}

// Copia uma matriz tridimensional
void copia_matriz3(unsigned char base[MAXH][MAXH][3], unsigned char copia[MAXH][MAXH][3], int h, int w){ 
    
    for(int i = 0 ; i < h ; i++)
        for(int j = 0 ; j < w ; j++)
            for(int k = 0 ; k < 3 ; k++)
                copia[i][j][k] = base[i][j][k];
}

// Diminui uma valor (faotor) de todos os elementos de uma matriz, escurecendo uma imagem (apenas em imagens em tons de cinza)
void escurecer_TC(unsigned char imagem[MAXH][MAXH], int h, int w, int fator){ 

    int valor;

    for(int i = 0 ; i < h ; i++)
        for(int j = 0 ; j < w ; j++){
            valor = (int)imagem[i][j];
			valor -= fator;
			if (valor < 0)
				valor = 0;		
			imagem[i][j] = (unsigned char)valor;
        }

}

// Diminui uma valor (faotor) de todos os elementos de uma matriz, escurecendo uma imagem (apenas em imagens coloridas)
void escurecer_CL(unsigned char imagem[MAXH][MAXH][3], int h, int w, int fator){ 
    int valor;

    for(int i = 0 ; i < h ; i++)
        for(int j = 0 ; j < w ; j++)
            for(int k = 0 ; k < 3 ; k++){
                valor = (int)imagem[i][j][k];
                valor -= fator;
                if (valor < 0)
                    valor = 0;		
                imagem[i][j][k] = (unsigned char)valor;
            }

}

// Aumenta um valor (faotor) de todos os elementos de uma matriz, clareando uma imagem (apenas em imagens em tons de cinza)
void clarear_TC(unsigned char imagem[MAXH][MAXH], int h, int w, int fator){ 

    int valor;

    for(int i = 0 ; i < h ; i++)
        for(int j = 0 ; j < w ; j++){
            valor = (int)imagem[i][j];
			valor += fator;
			if (valor > 255)
				valor = 255;		
			imagem[i][j] = (unsigned char)valor;
        }

}

// Aumenta um valor (faotor) de todos os elementos de uma matriz, clareando uma imagem (apenas em imagens coloridas)
void clarear_CL(unsigned char imagem[MAXH][MAXH][3], int h, int w, int fator){ 

    int valor;

    for(int i = 0 ; i < h ; i++)
        for(int j = 0 ; j < w ; j++)
            for(int k = 0 ; k < 3 ; k++){
                valor = (int)imagem[i][j][k];
                valor += fator;
                if (valor > 255)
                    valor = 255;		
                imagem[i][j][k] = (unsigned char)valor;
            }

}

// Subtrai 255 de cada elemento da matriz e atribui o módulo desse resultado à sua posição original, fazendo o negativo da imagem (apenas em imagens em tons de cinza)
void negativo_TC(unsigned char imagem[MAXH][MAXH], int h, int w){

    int valor;

    for(int i = 0 ; i < h ; i++)
        for(int j = 0 ; j < w ; j++){
            valor = (int)imagem[i][j];
			valor -= 255;
			if (valor < 0)
				valor *= -1;		
			imagem[i][j] = (unsigned char)valor;
        }

}

// Subtrai 255 de cada elemento da matriz e atribui o módulo desse resultado à sua posição original, fazendo o negativo da imagem (apenas em imagens coloridas)
void negativo_CL(unsigned char imagem[MAXH][MAXH][3], int h, int w){

    int valor;

    for(int i = 0 ; i < h ; i++)
        for(int j = 0 ; j < w ; j++)
            for(int k = 0 ; k < 3 ; k++){
                valor = (int)imagem[i][j][k];
			    valor -= 255;
			    if (valor < 0)
				    valor *= -1;		
			    imagem[i][j][k] = (unsigned char)valor;
            }

}

// Inverte a ordem dos elementos em todas as linhas da matriz, invertendo a imagem (apenas em imagens em tons de cinza)
void espelha_TC(unsigned char imagem[MAXH][MAXH], int h, int w){
    
    unsigned char aux;

    for(int i = 0 ; i < h ; i++)
        for(int j = 0 ; j < w/2 ; j++)
            troca(imagem[i][j], imagem[i][w-1-j]);

}

// Inverte a ordem dos elementos em todas as linhas da matriz, invertendo a imagem (apenas em imagens coloridas)
void espelha_CL(unsigned char imagem[MAXH][MAXH][3], int h, int w){
    
    unsigned char aux;

    for(int i = 0 ; i < h ; i++)
        for(int j = 0 ; j < w/2 ; j++){
            for(int k = 0 ; k < 3 ; k++)
                troca(imagem[i][j][k], imagem[i][w-1-j][k]);
        }

}

// Faz a convolução de uma matriz que define um filtro sobre a matriz que degine a imagem (apenas em imagens em tons de cinza)
void conv_TC(unsigned char imagem[MAXH][MAXH], double filtro[3][3], int h, int w){

    int valor, lin, col; // Variáveis auxiliares
    unsigned char imagemborda[MAXH + 2][MAXH + 2]; // Nova imagem (com borda de 0's)
    borda_TC(imagem, imagemborda, h, w); // Cria a borda de 0's

    for(int i = 0 ; i < h ; i++)
        for(int j = 0 ; j < w ; j++){
            lin = i+1;
            col = j+1;
            valor = 0;

            // Para cada elemento da matriz com borda, é feita a somatória das multiplicações entre todos os elementos com 1 de difereça e ele mesmo (em i ou j) e o item de posição equivalente na matriz que define o filtro;
            for(int a = -1; a <= 1 ; a++)
                for(int b = -1 ; b <= 1 ; b++){
                    valor += imagemborda[i + a][j + b] * filtro[a +1][b + 1];
                }
            level(valor);
            imagem[i][j] = (unsigned char)valor; // O resultado já tratado dessa conta é atribuido àquela posição na matriz
        }
}

// Faz a convolução de uma matriz que define um filtro sobre a matriz que degine a imagem (apenas em imagens coloridas)
void conv_CL(unsigned char imagem[MAXH][MAXH][3], double filtro[3][3], int h, int w){

    int valor, lin, col; // Variáveis auxiliares
    unsigned char imagemborda[MAXH + 2][MAXH + 2][3]; // Nova imagem (com borda de 0's)
    borda_CL(imagem, imagemborda, h, w); // Cria a borda de 0's

    for(int i = 0 ; i < h ; i++)
        for(int j = 0 ; j < w ; j++){
            lin = i+1;
            col = j+1;
            for(int k = 0 ; k < 3 ; k++){
                valor = 0;

                // Para cada elemento (e cada cor) da matriz com borda, é feita a somatória das multiplicações entre todos os elementos com 1 de difereça e ele mesmo (em i ou j) e o item de posição equivalente na matriz que define o filtro;
                for(int a = -1; a <= 1 ; a++)
                    for(int b = -1 ; b <= 1 ; b++){
                        valor += imagemborda[i + a][j + b][k] * filtro[a +1][b + 1];
                    }
                level(valor);
                imagem[i][j][k] = (unsigned char)valor; // O resultado já tratado dessa conta é atribuido àquela posição (e cor) na matriz
            }
        }
}

// Aplica o filtro de sobel utilizando convolução de matrizes(apenas em imagens em tons de cinza)
void sobel_TC(unsigned char imagem[MAXH][MAXH], int h, int w, int tipo){

    int somx, somy, lin, col, valor; // Variáveis auxiliares
    unsigned char imagemborda[MAXH + 2][MAXH + 2]; // Nova imagem (com borda de 0's)
    borda_TC(imagem, imagemborda, h, w); // Cria a borda de 0's

    const int sx[3][3] = { {1, 0, -1}, {2, 0, -2}, {1, 0, -1} }; // Matriz que define o filtro de sobel horizontal
    const int sy[3][3] = { {1, 2, 1}, {0, 0, 0}, {-1, -2, -1} }; // Matriz que define o filtro de sobel vertical

    for(int i = 0 ; i < h ; i++)
        for(int j = 0 ; j < w ; j++){
            lin = i+1;
            col = j+1;
            somx = 0;
            somy = 0;

            // É feita a a convolução das duas matrizes que definem o filtro sobre a da imagem e, dependendo do tipo de sobel escolhido, a atribuição desse valor é feito de uma maneira diferente
            for(int a = -1; a <= 1 ; a++)
                for(int b = -1 ; b <= 1 ; b++){
                    somx += imagemborda[lin + a][col + b] * sx[a + 1][b + 1];
                    somy += imagemborda[lin + a][col + b] * sy[a + 1][b + 1];
                }
            
            // Tipo 1 define o filtro de sobel por média aritmética
            if(tipo == 1)
                valor = (somx + somy)/2;
            // Tipo 2 define o filtro de sobel por valor máximo
            else if(tipo == 2)
                valor = max(somx, somy);
            // Tipo 3 define o filtro de sobel por magnitude do gradiente 
            else if(tipo == 3)
                valor = sqrt(somx * somx + somy * somy);

            level(valor);

            imagem[i][j] = (unsigned char)valor; // Após o tratamento definido pelo tipo, e o tratamento do valor resultante, esse resultado é atribuido à imagem naquela mesma posição
        }
}


// Aplica o filtro de sobel utilizando convolução de matrizes(apenas em imagens coloridas)
void sobel_CL(unsigned char imagem[MAXH][MAXH][3], int h, int w, int tipo){

    int somx, somy, lin, col, valor; // Variáveis auxiliares
    unsigned char imagemborda[MAXH + 2][MAXH + 2][3]; // Nova imagem (com borda de 0's)
    borda_CL(imagem, imagemborda, h, w); // Cria a borda de 0's
    const int sx[3][3] = { {1, 0, -1}, {2, 0, -2}, {1, 0, -1} }; // Matriz que define o filtro de sobel horizontal
    const int sy[3][3] = { {1, 2, 1}, {0, 0, 0}, {-1, -2, -1} }; // Matriz que define o filtro de sobel vertical

    for(int i = 0 ; i < h ; i++)
        for(int j = 0 ; j < w ; j++){
            lin = i+1;
            col = j+1;
            for(int k = 0 ; k < 3 ; k++){
                somx = 0;
                somy = 0;
            // É feita a a convolução das duas matrizes que definem o filtro sobre a da imagem e, dependendo do tipo de sobel escolhido, a atribuição desse valor é feito de uma maneira diferente
                for(int a = -1; a <= 1 ; a++)
                    for(int b = -1 ; b <= 1 ; b++){
                        somx += imagemborda[lin + a][col + b][k] * sx[a + 1][b + 1];
                        somy += imagemborda[lin + a][col + b][k] * sy[a + 1][b + 1];
                    }

                // Tipo 1 define o filtro de sobel por média aritmética
                if(tipo == 1)
                    valor = (somx + somy)/2;
                // Tipo 2 define o filtro de sobel por valor máximo
                else if(tipo == 2)
                    valor = max(somx, somy);
                // Tipo 3 define o filtro de sobel por magnitude do gradiente
                else if(tipo == 3)
                    valor = sqrt(somx * somx + somy * somy);

                level(valor);

                imagem[i][j][k] = (unsigned char)valor; // Após o tratamento definido pelo tipo, e o tratamento do valor resultante, esse resultado é atribuido à imagem naquela mesma posição (e cor)
            }
        }
}

// Converte uma imagem colorida do tipo P3 em uma imagem em tons de cinza do tipo P2
void cinza(unsigned char imagem[MAXH][MAXH][3], unsigned char imagem2[MAXH][MAXH], char tipo[4], int h, int w){

    int soma; // Variável auxiliar

    // Faz a média dos 3 valores das cores num determinado pixel e atribui esse valor à nova imagem do tipo P2 na mesma posição
    for(int i = 0 ; i < h ; i++)
        for(int j = 0 ; j < w ; j++){
            
            soma = 0;

            for(int k = 0 ; k < 3 ; k++)
                soma += imagem[i][j][k];

            soma /= 3;
            level(soma);
            imagem2[i][j] = soma;
        }

    // Muda o tipo da imagem de P3 para P2
    tipo[0] = 'P';
    tipo[1] = '2';

}

double distverde(unsigned char r, unsigned char g, unsigned char b){
    double dr = 0 - r, dg = 255 - g, db = 0 - b;
    return sqrt(dr * dr + dg * dg + db * db);
}

// Retira o fundo verde de uma imagem "chromak" e sobrepõe essa imagem sobre outra imagem "imagem" com uma opacidade definida pelo usuário
void chroma(unsigned char imagem[MAXH][MAXH][3], unsigned char chromak[MAXH][MAXH][3], int h, int w, double opacidade){

    int valor;

    for(int i = 0 ; i < h ; i++)
        for(int j = 0 ; j < w ; j++)
            if(distverde(chromak[i][j][0], chromak[i][j][1], chromak[i][j][2]) > 30){ // Se a distancia entre essa cor e verde for maior que 20, ela aparecerá na nova imagem, se não, ela será desconsiderada
                for(int k = 0 ; k < 3 ; k++){
                    valor = (chromak[i][j][k] * (opacidade/100) + imagem[i][j][k] * ((100 - opacidade)/100));
                    level(valor);
                    imagem[i][j][k] = (unsigned char)valor;
                }
            }

}