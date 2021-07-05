#include <bits/stdc++.h>
using namespace std;

struct MinHeapNode {
	// O elemento a ser armazenado
	int element;

	// índice do arquivo a partir da qual
    // o elemento é levado
	int i;
};

void swap(MinHeapNode* x, MinHeapNode* y);

// Uma aula para Min Heap
class MinHeap {
	// ponteiro para matriz de elementos no amontoa
	MinHeapNode* harr;

	// tamanho da pilha mínima
	int amontoa_tamnho;

public:
	// Construtor: cria um min
	// amontoa de determinado tamanho
	MinHeap(MinHeapNode a[], int tamnho);

	// para amontoaificar uma subárvore com
	// root em determinado índice
	void MinHeapify(int);

	// para obter o índice do filho esquerdo
	// do nó no índice i
	int left(int i) { return (2 * i + 1); }

	// para obter o índice do filho certo
	// do nó no índice i
	int right(int i) { return (2 * i + 2); }

	// para obter a raiz
	MinHeapNode getMin() { return harr[0]; }

	// para substituir a raiz por um novo nó
	// xe amontoaify () nova raiz
	void replaceMin(MinHeapNode x)
	{
		harr[0] = x;
		MinHeapify(0);
	}
};

// Construtor: Monta a amontoa de
// um determinado array a [] de determinado tamanho
MinHeap::MinHeap(MinHeapNode a[], int tamnho)
{
	amontoa_tamnho = tamnho;
	harr = a; // endereço do arquivo
	int i = (amontoa_tamnho - 1) / 2;
	while (i >= 0) {
		MinHeapify(i);
		i--;
	}
}

// Um método recursivo para amontoaificar
// uma subárvore com raiz
// em determinado índice. Este método
// assume que as
// subárvores já estão empilhadas
void MinHeap::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < amontoa_tamnho && harr[l].element < harr[i].element)
		smallest = l;
	if (r < amontoa_tamnho && harr[r].element < harr[smallest].element)
		smallest = r;
	if (smallest != i) {
		swap(&harr[i], &harr[smallest]);
		MinHeapify(smallest);
	}
}

// Uma função de utilidade para trocar dois elementos
void swap(MinHeapNode* x, MinHeapNode* y)
{
	MinHeapNode temp = *x;
	*x = *y;
	*y = temp;
}

// Mescla dois subarrays de arr [].
// O primeiro subarray é arr [l..m]
// O segundo subarray é arr [m + 1..r]
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* criar matrizes temporárias */
	int L[n1], R[n2];

	/* Copia dados para matrizes temporárias L [] e R [] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Mesclar as matrizes temporárias de volta em arr [l..r] */
	// Índice inicial do primeiro subarray
	i = 0;

	// Índice inicial do segundo subarray
	j = 0;

	// Índice inicial de submatriz mesclada
	k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j])
			arr[k++] = L[i++];
		else
			arr[k++] = R[j++];
	}

	/* Copy the remaining elements of L[],
		if there are any */
	while (i < n1)
		arr[k++] = L[i++];

	/* Copie os elementos restantes de R [],
		se houver algum*/
	while (j < n2)
		arr[k++] = R[j++];
}

/* l é para o índice esquerdo er é o índice direito do
submatriz de arr a ser classificado */
void mergeSort(int arr[], int l, int r)
{
	if (l < r) {
		// O mesmo que (l + r) / 2, mas evita estouro para
		// grande l e h
		int m = l + (r - l) / 2;

		// Classificar primeira e segunda metades
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

FILE* openFile(char* fileName, char* mode)
{
	FILE* fp = fopen(fileName, mode);
	if (fp == NULL) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	return fp;
}

// Mescla k arquivos classificados. Nomes de arquivos são assumidos
// sendo 1, 2, 3, ... k
void mergeFiles(char* output_file, int n, int k)
{
	FILE* in[k];
	for (int i = 0; i < k; i++) {
		char fileName[2];

		// converter i para string
		snprintf(fileName, sizeof(fileName),
				"%d", i);

		// Abre os arquivos de saída no modo de leitura.
		in[i] = openFile(fileName, "r");
	}

	// ARQUIVO DE SAÍDA FINAL EM ECREVER
	FILE* out = openFile(output_file, "w");

	// Cria uma pilha mínima com pilha k
	// nós. Cada nó de amontoa
	// tem o primeiro elemento do zero
	// arquivo de saída
	MinHeapNode* harr = new MinHeapNode[k];
	int i;
	for (i = 0; i < k; i++) {
		// quebra se nenhum arquivo de saída estiver vazio e
		// o índice i não será de arquivos de entrada
		if (fscanf(in[i], "%d ", &harr[i].element) != 1)
			break;

		//Índice do arquivo de saída (output) de rascunho
		harr[i].i = i;
	}
	// Cria o amontoa
	// e já organiza com recursividade (parecido com o mergeSort)
	MinHeap hp(harr, i);

	int count = 0;

	// Agora, um por um pegue o
	// elemento mínimo de min
	// empilhar e substituí-lo por
	// próximo elemento.
	// executa até que toda a entrada seja preenchida
	// arquivos alcançam EOF
	while (count != i) {
		// Obtenha o elemento mínimo
		// e armazená-lo no arquivo de saída
		MinHeapNode root = hp.getMin();
		fprintf(out, "%d ", root.element);

		// Encontre o próximo elemento que
		// substituirá o atual
		// elemento da pilha. O próximo elemento
		// pertence ao mesmo
		// arquivo de entrada como o elemento min atual.
		if (fscanf(in[root.i], "%d ",&root.element) != 1) {
			root.element = INT_MAX;
			count++;
		}
		
		// Substitui o elememto pelo próximo
		// elememto do arquivo de entrada
		hp.replaceMin(root);
	}

	// feche os arquivos de entrada e saída
	for (int i = 0; i < k; i++)
		fclose(in[i]);

	fclose(out);
}

// Usando um algoritmo de classificação por mesclagem,
// cria as execuções iniciais
// e dividi-los igualmente entre
// os arquivos de saída
void createInitialRuns(
	char* input_file, int run_tamnho,
	int num_ways)
{
	// Para arquivo de entrada grande
	FILE* in = openFile(input_file, "r");

	// arquivos de trabalho de saída
	FILE* out[num_ways];
	char fileName[2];
	for (int i = 0; i < num_ways; i++) {
		// converter i para string
		snprintf(fileName, sizeof(fileName),
				"%d", i);

		// Cria os arquivos de saída no modo de gravação.
		out[i] = openFile(fileName, "w");
	}

	// alocar um array dinâmico grande o suficiente
	// para acomodar execuções de tamanho run_tamnho
	int* arr = (int*)malloc(
		run_tamnho * sizeof(int));

	bool more_input = true;
	int next_output_file = 0;

	int i;
	//Lê cada uma das divisões de arquivos feitas e ordena, uma por uma
	while (more_input) {
		// escreve elementos run_tamnho
		// para chegar a partir do arquivo de entrada
		for (i = 0; i < run_tamnho; i++) {
			if (fscanf(in, "%d ", &arr[i]) != 1) {
				more_input = false;
				break;
			}
		}

		// ordenar array usando merge sort
		mergeSort(arr, 0, i - 1);//poderia ser qualquer outro

		// escreve os registros para o
		// arquivo de saída de rascunho apropriado
		// sem assumir que o loop
		// corre para run_tamnho
		// desde a duração da última corrida
		// pode ser menor que run_tamnho
		for (int j = 0; j < i; j++)
			fprintf(out[next_output_file],
					"%d ", arr[j]);

		next_output_file++;
	}

	// feche os arquivos de entrada e saída
	for (int i = 0; i < num_ways; i++)
		fclose(out[i]);

	fclose(in);
}

// Para classificar os dados armazenados no disco
void externalSort(
	char* input_file, char* output_file,
	int num_ways, int run_tamnho)
{
	// lê o arquivo de entrada,
	// cria as execuções iniciais,
	// e atribuir os arquivos temporários 
	// aos arquivos de saída de rascunho
	createInitialRuns(input_file,
					run_tamnho, num_ways);

	// Mesclar os arquivos temporários usando
	// a fusão K-way
	mergeFiles(output_file, run_tamnho, num_ways);
}

// Programa de driver para testar acima
int main(){
	// Nº de partições do arquivo de entrada.
	int num_ways = 10;

	// O tamanho de cada partição
	int run_tamnho = 100;

	char input_file[] = "input.txt";
	char output_file[] = "output.txt";

	FILE* in = openFile(input_file, "w");

	srand(time(NULL));

	// gerar input.txt
	for (int i = 0; i < num_ways * run_tamnho; i++)
		fprintf(in, "%d ", rand());

	fclose(in);

	externalSort(input_file, output_file, num_ways,run_tamnho);

	return 0;
}



/**************** DICA *************************
 * 
 * 		for (i = 0; i < run_tamnho; i++) {
			if (fscanf(in, "%d\n", &arr[i]) != 1) {
				more_input = false;
				break;
			}
		}
 * 
 * 
 * 
 */