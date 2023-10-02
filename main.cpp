#include <unistd.h>
#include <fstream>
#include <fcntl.h>
#include <string>

using namespace std;


int main(){

// Чтение, запись  имени тестового файла 
    write(STDOUT_FILENO, "Enter the file name: \n", 22);
    
    string name ="/home/alexandra/Рабочий стол/ос 3 сем/OS_LW1/tests/";
    char part[256];
    int q = 0;

    if (read(STDIN_FILENO, &part, sizeof(char)) == -1){
        perror("Reading error. \n");
        exit(-1);
    }
    else{
        while (part[q] != '\n'){
            name += part[q];
            q++;
        }
    }

//  Открытие тестового файла 
    const char* full_name = name.c_str();
    int file = open(full_name,O_RDONLY);

    if (file == -1){
        perror("File error. \n");
        exit(-1);
    }

// Создание pipe
    int fd[2];
    int pipe1 = pipe(fd);

    if (pipe1 == -1){
        perror("Pipe1 error. \n");
        exit(-1);
    }

// Создание дочернего потока
    pid_t pid = fork();

    if (pid == -1){
        perror("Pid errror. \n");
        exit(-1);
    }

// Работа с дочерним потоком
    if (pid == 0){ 
        close(fd[0]);

        if (dup2(file,STDIN_FILENO) == -1){
                perror("Dup2 error. \n");
                exit(-1);
            }
        else{
            dup2(file,STDIN_FILENO);
        }
        const char* child = "/home/alexandra/Рабочий стол/ос 3 сем/OS_LW1/build/child";
        execlp(child, child, NULL);

        close(file);
        close(fd[1]);
        exit(0);
    }
    
// Работа с родительским потоком 
    if (pid > 0){
        close(fd[1]);

        char result;
        while ((read(fd[0], &result, sizeof(result)) > 0)){
            write(STDOUT_FILENO, &result, sizeof(result));
        } 

        close(fd[0]);
        exit(0);
    }
    exit(0);
}