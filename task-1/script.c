#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

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
    pivot=*(mas+ (l+r)/2); /*определение опорного значения*/
    while (l<=r) {
        while (*(mas+l)<pivot) l++;
        while (*(mas+r)>pivot) r--;
        if (l<=r) {
            swap((mas+l),(mas+r)); /*перестановка двух элементов*/
            l++;
            r--;
        }
    } /*Рекурсивная сортировка:*/
    
    struct Args arg;
    arg.mas = mas;
    arg.left= first;
    arg.right = r;
    if (first<r) quick_sort(&arg); /*- левого участка, */
    arg.left = l;
    arg.right = last;
    if (l<last) quick_sort(&arg); /*- правого участка.*/
}


int index_of_min(int *mas, int *pointers){
    int m = INT_MAX;
    int p;
    for (int i = 0; i< NUMBER_OF_THREADS; i++){
        if (pointers[i]!= -1 && mas[pointers[i]]<m){
	    m = mas[pointers[i]];
 	    p = i;
        }
    }
    return p;
}



//функция многопоточной сортировки
void sort(int *mas, int len){
    int l = len/NUMBER_OF_THREADS; //минимальная длина отрезка сортировки
    int remaind = len % NUMBER_OF_THREADS;
    struct Args arguments[NUMBER_OF_THREADS];
    pthread_t last_thread;
    pthread_t threads[NUMBER_OF_THREADS];
    int pointers[NUMBER_OF_THREADS];

    //создание потоков и сортировка

    printf("\nРазбиение массива на подмассивы с индексами начального(l) и конечного(r) элементов:\n");
    
    int left= 0;
    for (int i = 0; i < NUMBER_OF_THREADS; i++){
        pthread_t thread;

        arguments[i].left = left;
        if(i<remaind) arguments[i].right = left + l; //добавление остаточных элементов к первым подмассивам
        else arguments[i].right = left + l -1;  //-1, т.к. индексация с нуля
        arguments[i].mas = mas;
        pointers[i]=left;
        
        printf("Поток %d: l = %d; r = %d\n", i+1, arguments[i].left, arguments[i].right);
	    if (pthread_create(&thread, NULL, quick_sort, &arguments[i])!= 0) {
		    printf("Ошибка создания потока\n");
	    }
	    threads[i] = thread;
        left = arguments[i].right+1;
    }

    // ожидание завершения всех потоков
    for (int i = 0; i < NUMBER_OF_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    //исходный массив после сортировки подмассивов и до слияния
    print_mas(mas, len);

    // Слияние подмассивов в общий массив
    int temp[len];
    for (int k=0; k<len; k++){
	int m = index_of_min(mas, pointers);
	temp[k] = mas[pointers[m]];
	pointers[m]++;
        if (pointers[m] > arguments[m].right) pointers[m]=-1;
    }

    //копирование отсортированного временного массива в основной
    for (int i = 0; i< len; i++){
	*(mas+i) = *(temp+i);
    }
}




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
    //scan_mas(mas,len); //с клавиатуры
    random_mas(mas, len, a, b);// случайными числами из диапазона [a,b]
    printf("Исходный массив:\n");
    print_mas(mas, len);

    printf("Максимальное колличество потоков: %d\n", NUMBER_OF_THREADS);

    sort(mas,len);
    printf("\nОтсортированный массив:\n");
    print_mas(mas,len);

    free(mas);
    return 0;
}
