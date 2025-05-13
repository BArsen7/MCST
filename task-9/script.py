import random
a = 0 # левая граница диапазона случайных чисел
b = 100 # правая граница диапазона случайных чисел (не включительно)
count = 50 # количество чисел  в исходном массиве
mas = [random.randint(a, b) for i in range(count)] # исходный массив


print("Исходный массив: ")
print (mas)

max = []
start, end =0,0
s = mas[0]
max_sum=0
max_len=1
for i in range(1,len(mas)):
    if(mas[i]>mas[i-1]):

        s+=mas[i]
        end = i
    else:
        if (end-start+1> max_len and s>max_sum):
            max = mas[start:end+1]
            max_sum = s
            max_len = end-start+1
        s = mas[i]
        start = i

print("Найденный подмассив: ")
print(max)
print(f"Сумма: {max_sum}; Длина {max_len}")
