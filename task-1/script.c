#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>



/*
static void *thread_function() {
    for (int i = 1; i <= 10; i++) {
        printf("Thread: %d\n", i);
        sleep(1); 
    }
    return NULL;
}

void create_thread(){
    pthread_t thread;
    if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
        printf("Ошибка создания потока\n");
    }
    pthread_detach(thread);
}

*/


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


void swap(int *x, int *y)
{
 int temp; /* temp - вспомогательная переменная */
 temp=*x;
 *x=*y;
 *y=temp;
}


void quick_sort(int *mas, int first, int last){
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
    if (first<r) quick_sort(mas,first,r); /*- левого участка, */
    if (l<last) quick_sort(mas,l,last); /*- правого участка.*/

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

    quick_sort(mas,0, len-1);
    printf("Отсортированный массив:\n");
    print_mas(mas,len);


    free(mas);

    /*
    create_thread();
    sleep(1);
    create_thread();

    sleep(20);
    printf("program stop\n");
    */
    return 0;}
