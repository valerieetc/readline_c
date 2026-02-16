#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int contains_n(char* buf);
int my_strlen(char* str);
char* my_strcpy(char* dest, char* src);
char* my_strcat(char* dest, char* src);

char* buffer = NULL;
int READLINE_READ_SIZE = 1234;

char* my_readline(int fd) {
    //check buffer. if buffer is empty, we read to the buffer
    if (buffer == NULL) {
        buffer = malloc((READLINE_READ_SIZE + 1) * sizeof(char));
        int bytes_read = read(fd, buffer, READLINE_READ_SIZE);

        if (bytes_read == 0 || bytes_read < 0) {
            return NULL;
        }   

        buffer[bytes_read] = '\0';    
    }

    //check if buffer contains '\n'
    int pos_n = contains_n(buffer);
    
    //if buffer doesn't contain '\n', look for the next segment containing '\n'
    int end_file = 0;
    while (pos_n == -1) {
        char* temp2 = malloc((READLINE_READ_SIZE + 1) * sizeof(char));
        int bytes = read(fd, temp2, READLINE_READ_SIZE);

        if (bytes == 0) {
            end_file = 1;
            free(temp2);
            break;
        }

        temp2[bytes] = '\0';
        char* temp1 = malloc((my_strlen(buffer) + 1) * sizeof(char));
        my_strcpy(temp1, buffer);
        free(buffer);
        buffer = malloc((my_strlen(temp1) + my_strlen(temp2) + 1) * sizeof(char));
        my_strcpy(buffer, temp1);
        my_strcat(buffer, temp2);
        free(temp1);
        free(temp2);
        pos_n = contains_n(buffer);
    }

    if (end_file == 1) {
        pos_n = my_strlen(buffer);
    }

    char* result = NULL;
    result = malloc((pos_n + 1) * sizeof(char));
    for (int i = 0; i < pos_n; i++) {
        result[i] = buffer[i];
    }
    result[pos_n] = '\0';

    //case when we return the last line ending in '\n'
    if ((my_strlen(result) + 1) == my_strlen(buffer)) {
        free(buffer);
        buffer = NULL;
        return result;
    }

    //case when we have reached end of file and return the last line not ending in '\n'
    if (end_file == 1) {
        free(buffer);
        buffer = NULL;
        return result;
    }

    //case when it's not the last line
    int pos_o = 0;
    for (int i = 0, j = pos_n + 1; j < my_strlen(buffer); i++, j++) {
        buffer[i] = buffer[j];
        pos_o = i + 1;
    }
    buffer[pos_o] = '\0';

    return result;
}

void init_my_readline() {
    free(buffer);
    buffer = NULL;
}

int contains_n(char* buf) {
    for (int i = 0; i < my_strlen(buf); i++) {
        if (buf[i] == '\n') {
            return i;
        }
    }
    return -1;
}

int my_strlen(char* str) {
    int i = 0;
    while(str[i] != '\0') {
        i++;
    }
    return i;
}

char* my_strcpy(char* dest, char* src) {
    int pos_o = 0;
    for (int i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
        pos_o = i + 1;
    }
    dest[pos_o] = '\0';
    return dest;
}

char* my_strcat(char* dest, char* src) {
    int len = my_strlen(dest);
    int pos_o = 0;
    for (int i = len, j = 0; src[j] != '\0'; i++, j++) {
        dest[i] = src[j];
        pos_o = i + 1;
    }
    dest[pos_o] = '\0';
    return dest;
}