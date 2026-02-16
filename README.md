# Welcome to My Readline
***

## Task
The task was to make a program that returns a line from an input stream.

## Description
The program contains the function char* my_readline(int fd) that receives a file descriptor as a parameter.
It reads an amount of bytes set by a global variable called READLINE_READ_SIZE from an input stream using the function read(). 
It finds the first line (delimited by '\n') and returns it without the '\n' character. It stores the rest of the bytes read in 
a global variable called buffer. If upon the next call the buffer contains something, it returns the next line from the buffer 
without calling read(). It also detects the end of file and returns the last line even if it does not end with '\n'. When there 
are no lines left to return, it returns NULL. The program contains the function init_my_readline() that frees the memory 
allocated for the buffer, as well as helper functions: contains_n(), my_strlen(), my_strcpy() and my_strcat().

## Installation
You need to have a GCC compiler to be able to run this program.

## Usage
You need to add main() to use this program. You can reset READLINE_READ_SIZE to your desired value.
Alternatively my_readline.c can be compiled with a separate main.c file.
Before reading from a new file, call init_my_readline() to make sure that the buffer has been freed.

After compiling you can run the program the following way:
```
./my_readline
```

Here is an example of main():

```c
int main(int ac, char **av)
{
  char *str = NULL;

  int fd = open("./file.txt", O_RDONLY);
  while ((str = my_readline(fd)) != NULL)
  {
      printf("%s\n", str);
      free(str);
  }
  close(fd);
  return 0;
}
```
