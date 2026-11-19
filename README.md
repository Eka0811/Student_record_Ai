# Student Record and Result Management System

A menu-driven C program for student contact details, semester SGPAs, CGPA calculations, sorting, and academic recommendations.

## Build and run

Requires a C99-compatible compiler such as GCC or Clang.

    gcc -std=c99 -Wall -Wextra -pedantic 590033730.c -o student-record
    ./student-record

On Windows, run `student-record.exe` after compiling.

Records are held in memory for one run and reset when the program exits. The program supports up to 100 students.

## Academic advisor

The advisor uses four CGPA bands: 9.0 and above, 7.5 to below 9.0, 6.0 to below 7.5, and below 6.0. It runs locally with C if/else logic and does not connect to an AI service. CGPA is the arithmetic mean of the available (non-zero) semester SGPAs.

See `AI_USAGE_LOG.md` for the prompts and how the suggestions were adapted. Example recommendation outputs are in `tests/sample_output.txt`.
