#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// Function to display an error message and exit the program
void Erry(const char *prog_name) {
    fprintf(stderr, "Usage: %s\n", prog_name);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 1) { // Only the program name should be provided
        Erry(argv[0]);
    }

    char name[100];
    char last_name[100];
    char phone_number[100];

    // Prompt the user for the name
    printf("Enter Name: ");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        fprintf(stderr, "Error reading Name\n");
        exit(EXIT_FAILURE);
    }
    // Remove the newline character from the input
    name[strcspn(name, "\n")] = '\0';

    // Prompt the user for the last name
    printf("Enter Last Name: ");
    if (fgets(last_name, sizeof(last_name), stdin) == NULL) {
        fprintf(stderr, "Error reading Last Name\n");
        exit(EXIT_FAILURE);
    }
    // Remove the newline character from the input
    last_name[strcspn(last_name, "\n")] = '\0';

    // Prompt the user for the phone number
    printf("Enter Phone Number: ");
    if (fgets(phone_number, sizeof(phone_number), stdin) == NULL) {
        fprintf(stderr, "Error reading Phone Number\n");
        exit(EXIT_FAILURE);
    }
    // Remove the newline character from the input
    phone_number[strcspn(phone_number, "\n")] = '\0';

    // Combine the inputs into a single string
    char entry[512];
    snprintf(entry, sizeof(entry), "%s %s,%s\n", name, last_name, phone_number);

    // Create a pipe
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        // Close the write end of the pipe
        close(pipe_fd[1]);

        // Redirect the read end of the pipe to stdin
        if (dup2(pipe_fd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        // Close the original read end of the pipe
        close(pipe_fd[0]);

        // Execute the cat command to append the input to the phonebook.txt file
        execlp("sh", "sh", "-c", "cat >> phonebook.txt", NULL);

        // If exec fails
        perror("execlp");
        exit(EXIT_FAILURE);
    } else { // Parent process
        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Write the entry to the write end of the pipe
        if (write(pipe_fd[1], entry, strlen(entry)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        // Close the write end of the pipe
        close(pipe_fd[1]);

        // Wait for the child process to finish
        wait(NULL);

        printf("Entry added successfully.\n");
    }

    return 0;
}
