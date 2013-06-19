# Async I/O

This is a small minimalist library that wraps the standard C I/O functions for non-blocking I/O, providing a high-performance alternative. This was done as an experiment to see if JS programming style can be brought to C programming. Well, the answer is yes!

## Building

Just execute:

    build.sh

The library will be built as `lib\libasyncio.a`.

## Example

Try the `example.c` file. To compile execute:

    gcc -o example example.c -pthread lib/libasyncio.a
    ./example

## Make it better

Sure! Just fork and send a pull request.
