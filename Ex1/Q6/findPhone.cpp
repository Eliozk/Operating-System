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

    // Check if the program received the correct number of arguments name of prog and name
    if (argc != 2) {
        // Prompt the user to enter a name if not provided as an argument
        char inputName[100];
        std::cout << "Enter Name: not running  ";
        std::cin.getline(inputName, sizeof(inputName));
        name = inputName;
    } else {
        name = argv[1];
    }

    // Create three pipes for inter-process communication
    //pipe1- search by name
    //pipe2- change space to #
    //pipe3 - change "," to space
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
        // Child process 1: Run 'grep' to search for the specific name
        close(pipefd[0]);            // Close unused read end of the first pipe
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the write end of the first pipe
        close(pipefd[1]);            // Close the write end of the first pipe after redirecting

        execlp("grep", "grep", name, "phonebook.txt", (char *)NULL);
        perror("execlp grep");       // If execlp fails, print error
        exit(EXIT_FAILURE);
    }

    close(pipefd[1]); // Close the write end of the first pipe in parent

    // Fork the second child process to run 'sed s/ /#/g'
    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Child process 2: Run 'sed s/ /#/g' to replace spaces with '#'
        close(pipefd2[0]);             // Close unused read end of the second pipe
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to the read end of the first pipe
        dup2(pipefd2[1], STDOUT_FILENO); // Redirect stdout to the write end of the second pipe
        close(pipefd[0]);              // Close the read end of the first pipe after redirecting
        close(pipefd2[1]);             // Close the write end of the second pipe after redirecting

        execlp("sed", "sed", "s/ /#/g", (char *)NULL);
        perror("execlp sed");          // If execlp fails, print error
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);  // Close the read end of the first pipe in parent
    close(pipefd2[1]); // Close the write end of the second pipe in parent

    // Fork the third child process to run 'sed s/,/ /'
    pid_t pid3 = fork();
    if (pid3 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid3 == 0) {
        // Child process 3: Run 'sed s/,/ /' to replace commas with spaces
        close(pipefd3[0]);             // Close unused read end of the third pipe
        dup2(pipefd2[0], STDIN_FILENO); // Redirect stdin to the read end of the second pipe
        dup2(pipefd3[1], STDOUT_FILENO); // Redirect stdout to the write end of the third pipe
        close(pipefd2[0]);             // Close the read end of the second pipe after redirecting
        close(pipefd3[1]);             // Close the write end of the third pipe after redirecting

        execlp("sed", "sed", "s/,/ /", (char *)NULL);
        perror("execlp sed");          // If execlp fails, print error
        exit(EXIT_FAILURE);
    }

    close(pipefd2[0]); // Close the read end of the second pipe in parent
    close(pipefd3[1]); // Close the write end of the third pipe in parent

    // Fork the fourth child process to run 'awk {print $2}'
    pid_t pid4 = fork();
    if (pid4 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid4 == 0) {
        // Child process 4: Run 'awk {print $2}' to print the second field
        dup2(pipefd3[0], STDIN_FILENO); // Redirect stdin to the read end of the third pipe
        close(pipefd3[0]);              // Close the read end of the third pipe after redirecting

        execlp("awk", "awk", "{print $2}", (char *)NULL);
        perror("execlp awk");           // If execlp fails, print error
        exit(EXIT_FAILURE);
    }

    close(pipefd3[0]); // Close the read end of the third pipe in parent

    // Wait for all child processes to finish
    int status;
    while (wait(&status) > 0);

    return 0;
}


// 1. תהליך ראשון יוצר את פקודת ה-Grep על מנת לחפש את השם המבוקש בקובץ.
// 2. תהליך שני משתמש ב-Sed כדי לשנות רווחים לתו "#" בשורות שנמצאו על ידי ה-Grep.
// 3. תהליך שלישי משתמש גם ב-Sed כדי להחליף פסיקים ברווחים.
// 4. תהליך רביעי משתמש ב-Awk כדי להציג את השדה השני בכל שורה, שהוא המספר הטלפון.
//
// לסיום, התוכנית מחכה לסיום כל התהליכים הילדים ומציגה את התוצאה הסופית בפלט.