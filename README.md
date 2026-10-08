# Microshell

A simple UNIX/Linux shell implemented in C, with no dependencies beyond libc.

## History

The project dates back to my CS undergrad days; it was first compiled between
2001 and 2002 and then gathered dust in a remote corner of a forgotten
directory tree. I first tidied up the rough edges, and then — nearly ten
years later — a second round removed known security bugs and modernized the
code: bounded token parsing (no more stack overflow on long input),
corruption-free environment handling, validated builtin arguments, POSIX
signal handling, and hardened compiler flags (tag `0.2`).

## Features

The shell supports:

* Redirection ('<', '>'), append ('>>') and pipes ('|').
* Background commands ('cmd &'), which print the PID of the new process.
* Double-quoted words with backslash escapes.
* Bunch of builtin commands: cd, printenv, kill and exit.
* Define/update environment variables (just use: VARNAME=somevalue).

Words are limited to 20 characters, file names to 45, and a command takes at
most 20 arguments.

## Source

The shell parser (defined in command.c/gettoken.c) came from Marc J. Rochkind
and I have added the rest on my own.

**The code is provided "as is", without any guarantees regarding stability.**
The 2026 round removed the known memory-safety bugs and the build was
verified with warnings enabled plus ASan/UBSan, but this remains an
educational toy shell, not a daily-driver replacement.

## Build

Just clone the repo with git and then use the make command. An executable
called 'microshell' will then be available; it is built with gcc -std=gnu11,
warnings enabled and hardening options (fortify, stack protector).
'make debug' produces a shell executable with debug information called
'microshell_d', and 'make asan' produces an AddressSanitizer/UBSan
instrumented build called 'microshell_asan'.
