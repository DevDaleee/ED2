#include <stdio.h>

int soma_digitos(int num){
    if (num % 10 == num)
        return num;
    return ((num % 10) + soma_digitos(num / 10));
}

int main(){
    int n = 123;
    n = soma_digitos(n);
    printf("%d \n", n);
}
