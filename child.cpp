#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <fcntl.h>
#include "simple.h"

using namespace std;

int main(){

    char result[256]; int r = 0;
    char num;
    int number = 0;
    int znak; 
    int size = 0;

    // Проверка чтения данных 
    if (read(STDIN_FILENO, &num, sizeof(num)) == -1){
        perror("Readind error. \n");
        exit(-1);
    }
    else{
        // Цикл работает, пока находяться числа или \n 
        while (num != ' '){
            result[r] = num;
            r++;
            size++;

            // Составление одного числа, происходит в рамках одной строки до \n
            if (num != '\n'){ 
                if (num == '-'){
                    znak = -1;
                }
                else{
                    znak = 1;
                }

                number = (number * 10) + (num - '0');
                read(STDIN_FILENO, &num, sizeof(num));
            }
            else{

                // Обработка составленного числа
                number *= znak;

                if (Simple(number)){
                    break;
                }

                number = 0;
                size = 0;
                read(STDIN_FILENO, &num, sizeof(num));
            }
        }
    }
    // Запись составленных чисел в поток вывода (связан с fd[1] pipe1)
    for (int q = 0; q < r - 2; q++){
        write(STDOUT_FILENO, &result[q], sizeof(result[q]));
    }
    exit(0);
}