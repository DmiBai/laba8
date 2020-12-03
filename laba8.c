// Дан текст. Слова в тексте разделены пробелами и знаками препинания.
//Получить n наиболее часто встречающихся слов и число их появлений.

#include <stdio.h>
#include <stdlib.h>

int main() {
	char* str;
	int* l;
	char** words;
	int i, j = 0, n, m = 0, k = 0, d = 0, N=0;


	printf("Line length: ");
	scanf_s("%d\n", &n);
	n++;

	str = (char*)malloc(n * sizeof(char));	// Выделение памяти.

	fgets(str, n, stdin);

	puts(str);

	k = 0;
	for (i = 0; i < n; i++) { // Подсчёт количества пробелов.
		if ((str[i] >= ' ' ) && (str[i] < '/' )){
			m++;
		}
	}
	++m;

	printf("Words number: %d\n", m);

	l = (int*)calloc(m, sizeof(int));

	k = 0;
	for (i = 0; i < m; i++) {  //Подсчёт кол-ва символов в словах.
		while ((str[k] > '/') && (str[k] < '{')) {
			l[i]++;
			k++;
		}
		k++;
	}

	for (i = 0; i < m; i++) {
		printf("%d ", l[i]);
	}

	words = (char**)calloc(m, sizeof(char*));
	for (i = 0; i < m; i++) {
		words[i] = (char*)calloc(l[i], sizeof(char));
	}
	k = 0;
	for (i = 0; i < m; i++) { //Заполнение массива words словами 
		for (j = 0; j < l[i]; j++) {
			if ((str[k] != ' ') && (str[k] != '\0')) {
				words[i][j] = str[k];
			}
			k++;
		}
		k++;
	}
	int* NoR;
	NoR = (int*)malloc(m * sizeof(int));
	for (i = 0; i < m; i++) {
		NoR[i] = 1;
	}
	
	for (i = 0; i < m; i++) {
		for (j = i + 1; j < m; j++) {
			if ((l[i] == l[j]) && (NoR[i] != 0) && (NoR[j] != 0)) {
				d = 0; //Счётчик кол-ва совпавших символов.
				k = 0;
				while ((words[i][k] == words[j][k]) && (d<l[i])) {
						d++;
						k++;
					}
				if (d == l[i]) {
					NoR[j] = 0;
					NoR[i]++;
				}
			}
		}
	}
	

	printf("\n");
	for (i = 0; i < m; i++) {
		printf("%d ", NoR[i]);
	}

	printf("\nEnter n: ");
	scanf_s("%d", &N);
	
	int** arr;
	arr = (int**)malloc(m * sizeof(int*));
	for (i = 0; i < m; i++) {
		arr[i] = (int*)malloc(2 * sizeof(int));
	}

	for (i = 0; i < m; i++) { // Дополнительный массив, необходимый для удобного вывода.
			arr[i][0] = NoR[i];
			arr[i][1] = i;
	}

	for (i = 0; i < m; i++) {
		for (j = 0; j < m - 1; j++) {
			if (arr[j][0] < arr[j + 1][0]) {
				d = arr[j][0];
				arr[j][0] = arr[j + 1][0];
				arr[j + 1][0] = d;

				d = arr[j][1];
				arr[j][1] = arr[j + 1][1];
				arr[j + 1][1] = d;

			}
		}
	}

	for (i = 0; i < N; i++) {
		if (arr[i][0] != 0) {
			printf("\nWord: ");
			for (j = 0; j < l[i]; j++) {
				printf("%c", words[arr[i][1]][j]);
			}
			printf("\nNumber of repetitions: %d\n", arr[i][0]);
		}
	}


	free(l);
	for (i = 0; i < m; i++) {
		free(arr[i]);
	}
	free(NoR);
	free(arr);
	for (i = 0; i < m; i++) {
		free(words[i]);
	}
	free(words);

	return 0;
}
