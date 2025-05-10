#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


#define NUMBER_OF_THREADS 8

struct Args{
    int *mas;
    int left;
    int right;
};


// функция вывода массива на экран
void print_mas(int *mas, int len){  // указатель на массив | >
    
    /*
    // вывод индексов
    for (int i = ; i<=len-1; i++){
        printf("%3d",i);
    }
    printf("\n");
    */
    //вывод значений массива
    for (int i = 0; i<len; i++){
        printf("%3d", *(mas+i));
    }
    printf("\n");
}


// функция ввода массива с клавиатуры
void scan_mas(int *mas, int len){   // указатель на массив | длинна массива
    for (int i = 0; i< len; i++){
        scanf("%d", mas+i);
    }
}


// функция генерации случайного числа в диапазоне [a,b]
int random_ab(int a, int b){    // a | b
    return a+rand()%(b-a+1);
}


// функция заполнения массива случайными числами из диапазона a b
void random_mas(int *mas, int len, int a, int b){  // указатель на массив | длинна массива | a | b
    for (int i = 0; i< len; i++){
        *(mas+i)= random_ab(a,b);
    }
}


// вспомогательная функция 
void swap(int *x, int *y)
{
 int temp; /* temp - вспомогательная переменная */
 temp=*x;
 *x=*y;
 *y=temp;
}


// быстрая сортировка
void* quick_sort(void *args){
    struct Args *arguments = (struct Args *) args;
    int *mas = arguments->mas;
    int first = arguments->left;
    int last = arguments->right;
    int pivot; /*опорное значение*/
    int l,r; /*левый и правый счетчики*/
    l=first; r=last;
    pivot=*(mas+(l+r)/2); /*определение опорного значения*/
    while (l<=r) {
        while (*(mas+l)<pivot) l++;
        while (*(mas+r)>pivot) r--;
        if (l<=r) {
            swap(mas+l,mas+r); /*перестановка двух элементов*/
            l++;
            r--;
        }
    } /*Рекурсивная сортировка:*/
    arguments->left = first;
    arguments->right = r;
    if (first<r) quick_sort(&arguments); /*- левого участка, */
    arguments->left = l;
    arguments->right = last;
    if (l<last) quick_sort(&arguments); /*- правого участка.*/
    return 0;
}


//функция мноопоточной сортировки
void sort(int *mas, int len){
    int l = len/NUMBER_OF_THREADS+1; //длина отрезка сортировки
    struct Args arguments[NUMBER_OF_THREADS];
    for (int i = 0; i*l<len; i++){
        pthread_t thread;
        arguments[i].mas = mas;
        arguments[i].left = l*i;
	if (i*(l+1) >len-1){
	    arguments[i].right = len-1;
	} else {
	    arguments[i].right = l*(i+1)-1;
	}
	printf("Поток %d: l = %d; r = %d\n", i, arguments[i].left, arguments[i].right);
	if (pthread_create(&thread, NULL, quick_sort, &arguments[i])!= 0) {
        printf("Ошибка создания потока\n");
	}
	pthread_detach(thread);
	i++;
    }
    print_mas(mas,len);
    // Слияние подмассивов в общий

}




//количество потоков

int main() {
    int len;
    int *mas;

    //инициализация массива
    scanf("%d", &len);
    //len = 50;
    int a = 0;
    int b = 99;
    mas = malloc(len*sizeof(int));

    //заполнение массива
    scan_mas(mas,len); //с клавиатуры
    //random_mas(mas, len, a, b);// случайными числами из диапазона [a,b]
    printf("Исходный массив:\n");
    print_mas(mas, len);

    sort(mas,len);
    printf("Отсортированный массив:\n");
    print_mas(mas,len);

    free(mas);
    return 0;}
