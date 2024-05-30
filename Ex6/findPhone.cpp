#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>

// Function to print usage error message and exit
void Erry(const char *prog_name) {
    fprintf(stderr, "Usage: %s \"Name\"\n", prog_name);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    const char *name;

    // Check if the program received the correct number of arguments
    if (argc != 2) {
        // Prompt the user to enter a name if not provided as an argument
        char inputName[100];
        std::cout << "Enter Name: ";
        std::cin.getline(inputName, sizeof(inputName));
        name = inputName;
    } else {
        name = argv[1];
    }

    // Create three pipes for inter-process communication
    int pipefd[2], pipefd2[2], pipefd3[2];
    if (pipe(pipefd) == -1 || pipe(pipefd2) == -1 || pipe(pipefd3) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the first child process to run 'grep'
    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Child process 1: Run 'grep'
        close(pipefd[0]);            // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to write end of pipe
        close(pipefd[1]);            // Close write end after redirecting

        execlp("grep", "grep", name, "phonebook.txt", (char *)NULL);
        perror("execlp grep");
        exit(EXIT_FAILURE);
    }

    close(pipefd[1]); // Close write end of the first pipe in parent

    // Fork the second child process to run 'sed s/ /#/g'
    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Child process 2: Run 'sed s/ /#/g'
        close(pipefd2[0]);             // Close unused read end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to read end of the first pipe
        dup2(pipefd2[1], STDOUT_FILENO); // Redirect stdout to write end of the second pipe
        close(pipefd[0]);              // Close read end of the first pipe after redirecting
        close(pipefd2[1]);             // Close write end of the second pipe after redirecting

        execlp("sed", "sed", "s/ /#/g", (char *)NULL);
        perror("execlp sed");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);  // Close read end of the first pipe in parent
    close(pipefd2[1]); // Close write end of the second pipe in parent

    // Fork the third child process to run 'sed s/,/ /'
    pid_t pid3 = fork();
    if (pid3 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid3 == 0) {
        // Child process 3: Run 'sed s/,/ /'
        close(pipefd3[0]);             // Close unused read end
        dup2(pipefd2[0], STDIN_FILENO); // Redirect stdin to read end of the second pipe
        dup2(pipefd3[1], STDOUT_FILENO); // Redirect stdout to write end of the third pipe
        close(pipefd2[0]);             // Close read end of the second pipe after redirecting
        close(pipefd3[1]);             // Close write end of the third pipe after redirecting

        execlp("sed", "sed", "s/,/ /", (char *)NULL);
        perror("execlp sed");
        exit(EXIT_FAILURE);
    }

    close(pipefd2[0]); // Close read end of the second pipe in parent
    close(pipefd3[1]); // Close write end of the third pipe in parent

    // Fork the fourth child process to run 'awk {print $2}'
    pid_t pid4 = fork();
    if (pid4 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid4 == 0) {
        // Child process 4: Run 'awk {print $2}'
        dup2(pipefd3[0], STDIN_FILENO); // Redirect stdin to read end of the third pipe
        close(pipefd3[0]);              // Close read end of the third pipe after redirecting

        execlp("awk", "awk", "{print $2}", (char *)NULL);
        perror("execlp awk");
        exit(EXIT_FAILURE);
    }

    close(pipefd3[0]); // Close read end of the third pipe in parent

    // Wait for all child processes to finish
    int status;
    while (wait(&status) > 0);

    return 0;
}
