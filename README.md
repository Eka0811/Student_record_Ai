# Student Record and Result Management System

A menu-driven C program for student contact details, semester SGPAs, CGPA calculations, sorting, and academic recommendations.

## Build and run

Requires a C99-compatible compiler such as GCC or Clang.

    gcc -std=c99 -Wall -Wextra -pedantic 590033730.c -o student-record
    ./student-record

On Windows, run `student-record.exe` after compiling.

Records are held in memory for one run and reset when the program exits. The program supports up to 100 students.
