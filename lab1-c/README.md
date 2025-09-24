# Lab 1: Programming in C

* [Pre-Lab preparation](#preparation)
* [Part 1: Hello world](#part1)
* [Part 2: Variables](#part2)
* [Part 3: Bitwise operators](#part3)
* [Challenges](#challenges)
* [References](#references)

### Learning objectives

* Understand the basic structure of C code
* Use C code control structures: loops, conditions
* Understand the binary operators

<a name="preparation"></a>

## Pre-Lab preparation

1. Complete the following table by entering the number of bits and the numeric range for the selected data types defined in C.

   | **Data type** | **Number of bits** | **Range** | **Description** |
   | :-: | :-: | :-: | :-- |
   | `uint8_t`  | 8 | 0, 1, ..., 255 | Unsigned 8-bit integer |
   | `int8_t`   |  |  |  |
   | `uint16_t` |  |  |  |
   | `int16_t`  |  |  |  |
   | `float`    |  | -3.4e+38, ..., 3.4e+38 | Single-precision floating-point |
   | `void`     | -- | -- | Depending on the context, it means *no type*, *no value* or *no parameters* |

<a name="part1"></a>

## Part 1: Hello world

1. Use the [online C editor/compiler](https://www.onlinegdb.com/online_c_compiler) to test your first C code.

   ```c
   #include <stdio.h>

   int main()
   {
       printf("Hello, world!");
       return 0;
   }
   ```

2. Use the `printf` function to test the following escape sequences:

   * **Newline** (`\n`): Moves the cursor to the beginning of the next line.

   * **Carriage Return** (`\r`): Moves the cursor to the beginning of the current line, allowing you to overwrite text on the same line.

      > Note that, on Windows, the end of a line is typically represented by `\r\n` (carriage return + newline). This combination moves the cursor to the beginning of the line (`\r`) and then to the next line (`\n`). On Linux/macOS, only `\n` is used to represent a new line.

   * **Tab** (`\t`): Inserts a horizontal tab, typically advancing the cursor to the next tab stop (commonly set at 4 or 8 spaces).

   * **Backspace** (`\b`): Moves the cursor one position to the left, useful for deleting characters.

<a name="part2"></a>

## Part 2: Variables

1. Use the standard C integer library `stdint.h`, declare local variables and test basic arithmetic operations.

   ```c
   #include <stdio.h>   // Standard C input/output library for `printf`
   #include <stdint.h>  // Standard C integer library for `int8_t, uint8_t`

   int main(void)       // Main function with no input parameters
   {                    // Beginning of function body
       uint8_t a = 10;  // Declaration of local variable

                        // Print formatted strings to the Terminal
                        // Integer `a` will be printed instead of `%d`
       printf("Value = %d\n", a);

       a = a + 100;
       printf("%d\n", a);


       // DO SOME OTHER PROCESSING


       return 0;         // Return value of main function
   }                     // End of function body
   ```

2. Write a program that calculates the factorial of a given number `n`. The factorial is the product of all positive integers from 1 to `n`. Note that you can use **if** statements and **while** or **for** loops.

   For example:
      * factorial of 5 should return 120 because 5! = 5 * 4 * 3 * 2 * 1 = 120.
      * factorial of 0 should return 1, as the factorial of 0 is defined to be 1.
      * factorials of negative values are not defined.

   >
   > Condition syntax:
   > ```c
   > if (condition) {
   >     // Code to execute if condition is true
   > } else {
   >     // Code to execute if condition is false (optional)
   > }
   > ```
   >
   > General syntax of a while loop:
   > ```c
   > while (condition) {
   >     // Code to be executed repeatedly
   > }
   > ```
   >
   > For loop syntax and example:
   > ```c
   > for (initialization; condition; increment/decrement) {
   >     // Code to be executed in each iteration
   > }
   >
   > for (uint8_t i = 0; i < 5; i++) {
   >     printf("*");
   > }
   > ```

3. In C, you can represent and test 8-bit integers in different numeral systems: hexadecimal, decimal, and binary.

   * Decimal: Use the standard number format (base 10).
   * Hexadecimal: Prefix the number with `0x`.
   * Binary: Prefix the number with `0b`.

      ```c
      #include <stdio.h>
      #include <stdint.h>

      int main(void)
      {
          uint8_t hex_value = 0x1f;  // Hexadecimal value
          uint8_t dec_value = 31;    // Decimal value
          uint8_t bin_value = 0b00011111;  // Binary value

          printf("Decimal: %d\n", dec_value);
          printf("Hexadecimal: 0x%x\n", hex_value);
          printf("Convert binary to decimal: %d\n", bin_value);

          return 0;
      }
      ```

   Try declaring several variables in different number formats and display their values ​​using `printf` and the correct **format specifiers**.

   > | **Specifier** | **Description** | **Example** |
   > | :-- | -- | -- |
   > | `%d` or `%i`  | Prints a signed decimal integer (base 10).              | `printf("%d", 42);`          |
   > | `%u`          | Prints an unsigned decimal integer (base 10).           | `printf("%u", 42);`          |
   > | `%x` or `%X`  | Prints an unsigned hexadecimal integer (lower/uppercase)| `printf("%x", 255);`         |
   > | `%f`          | Prints a floating-point number (decimal notation).      | `printf("%f", 3.14);`        |
   > | `%c`          | Prints a single character.                              | `printf("%c", 'A');`         |
   > | `%p`          | Prints a pointer (memory address).                      | `printf("%p", &variable);`   |
   > | `%lf`         | Prints a double-precision floating-point number.        | `printf("%lf", 3.14159);`    |
   > | `%ld` or `%li`| Prints a long signed integer.                           | `printf("%ld", 123456L);`    |
   > | `%%`          | Prints a literal percent symbol (`%`).                  | `printf("%%");`              |
   > 
   > **Notes:**
   > * Floating-point precision: You can control the precision of floating-point numbers, e.g., `%.2f` prints two decimal places.
   > * Hexadecimal with the minimum width of the output: `%04x` ensures that the output has at least 3 characters; if shorter, leading zeros are added to make it exactly four characters long.

<a name="part3"></a>

## Part 3: Bitwise operators

In C, binary (bitwise) operators allow you to directly manipulate individual bits in a variable. These operators are very useful for tasks like setting, clearing, toggling, or checking specific bits, especially useful in embedded systems programming, hardware control, or low-level optimizations.

   **Common bitwise operators in C:**
   * OR (`|`): Used to **set** specific bits.
      ```c
      variable |= (1 << bit_position);
      ```
   * AND (`&`): Used to **clear** specific bits (with combination of `~`).
      ```c
      variable &= ~(1 << bit_position);
      ```
   * XOR (`^`): Used to **toggle** (flip) specific bits.
      ```c
      variable ^= (1 << bit_position);
      ```
   * NOT (`~`): Inverts all the bits of a variable.
   * Left Shift (`<<`): Shifts bits to the left, effectively multiplying by powers of 2.
   * Right Shift (`>>`): Shifts bits to the right, effectively dividing by powers of 2.

   | **b** | **a** |**b OR a** | **b AND a** | **b XOR a** | **NOT b** |
   | :-: | :-: | :-: | :-: | :-: | :-: |
   | 0 | 0 | 0 | 0 | 0 | 1 |
   | 0 | 1 | 1 | 0 | 1 | 1 |
   | 1 | 0 | 1 | 0 | 1 | 0 |
   | 1 | 1 | 1 | 1 | 0 | 0 |

   ![binary operations](images/binary_operations.png)

1. Write a C program that demonstrates the use of bitwise operators (`&`, `|`, `^`, `~`, `<<`, `>>`) on 8-bit integer values.

<a name="challenges"></a>

## Challenges

1. Implement a program to generate Fibonacci numbers. The Fibonacci sequence is a classic series where each number is the sum of the two preceding ones (starting with 0 and 1): 0, 1, 1, 2, 3, 5, 8, ...

2. Write a C program that simulates a simple progress bar using ASCII characters and `printf`. The progress bar should fill up in one line from 0% to 100% using the `#` character and update in real-time.

   Example output:
      ```shell
      [............................................] 0%
      [##########..................................] 20%
      [###################.........................] 40%
      [#############################...............] 60%
      [######################################......] 80%
      [############################################] 100%
      ```

   Hints:
      * Use the loop counter to control how many `#` and `.` characters are printed.
      * Use `fflush(stdout);` after `printf` to ensure the output is displayed immediately.
      * Use the `usleep(100000);` function from the `unistd.h` library to add a delay between updates for a visual effect.
      * You can use ANSI escape codes to highlight progress values.

   ```c
   #include <stdio.h>
   #include <unistd.h>  // For usleep function (POSIX)
   /* Note: POSIX (Portable Operating System Interface) is an IEEE standard 
      that ensures compatibility across different operating systems.*/

   int main(void)
   {
       uint8_t total = 50;  // Total width of the progress bar

       ...

           // Print the progress bar percentage
           printf("] %d%%\r", (i * 100) / total);
           fflush(stdout);  // Ensure the output is flushed immediately
           usleep(100000);  // Delay for 100 milliseconds to create a visual effect

       printf("\n");
       return 0;
   }
   ```

3. Write a program that determines whether a given number is prime and generates all prime numbers up to 1000. Note that prime numbers are natural numbers greater than 1, having only two distinct positive divisors: 1 and the number itself (e.g., 2, 3, 5, 7, 11, 13, 17, ...).

4. Use escape sequence `\x1b` to control text formatting, colors, and other terminal features, such as changing text color with [ANSI escape codes](https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797).

   > Format: `\x1b[<style>m` or `\x1b[<style>;<style>m`
   >
   > Common ANSI Escape Codes:
   >   * Bold: `\x1b[1m`
   >   * Red: `\x1b[31m`
   >   * Green: `\x1b[32m`
   >   * Reset (normal): `\x1b[0m`
   >
   > ```c
   > // Examples
   > printf("This is \x1b[32;1mGREEN BOLD\x1b[0m text.\n");
   > printf("This is \x1b[31mRED\x1b[0m text.\n");
   > ```

<a name="references"></a>

## References

1. [OnlineGDB online compiler and debugger for c/c++](https://www.onlinegdb.com/online_c_compiler)

2. Parewa Labs Pvt. Ltd. [C User-defined functions](https://www.programiz.com/c-programming/c-user-defined-functions)

3. [Programiz C Online Compiler](https://www.programiz.com/c-programming/online-compiler/)
