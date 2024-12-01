# Get Next Line

## Description

The `get_next_line` project aims to read a user's input line by line. It is designed to handle different buffer sizes, which can be set during compilation. This functionality is particularly useful for reading from files or standard input in a controlled manner.

## Features

- **Customizable Buffer Size**: The buffer size can be defined at compile time, allowing for flexibility in different use cases.
- **Bonus - Multiple File Handling**: The bonus version of `get_next_line` can handle multiple files simultaneously, making it more versatile for complex applications.

## Usage

To compile the project with a specific buffer size, use the following command:

```sh
gcc -D BUFFER_SIZE=<size> -o get_next_line get_next_line.c
```

Replace `<size>` with the desired buffer size.

## Example

Here is an example of how to use `get_next_line`:

```c
#include "get_next_line.h"

int main(void)
{
    char *line;
    int fd = open("example.txt", O_RDONLY);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

## Bonus

The bonus version supports reading from multiple file descriptors simultaneously. This is useful for applications that need to process multiple input sources concurrently.

## License

This project is licensed under the MIT License.
