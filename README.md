## Microshell

This repo contains a simple UNIX/Linux shell, implemented in C and with no
particular dependencies.

It was a project which dates back when I was a CS undergrad and it was getting
dust on a remote corner of a forgotten directory tree. So I have decided to 
revamp the source code a little bit and adjust some of the rough edges of the 
original project (which was compiled for the first time between 2001 and 2002).

### Characteristics

The shell supports:

* Redirection ('<','>'), append ('>>') and pipes ('|').
* Bunch of builtin commands: cd, printenv, kill and exit.
* Define/update environment variables (just use: VARNAME=somevalue)

### Source code

The shell parser (defined in command.c/gettoken.c) came from Marc J. Rochkind
and I have added the rest on my own.

**The code is provided "as is", without any guarantees regarding stability and
code safety.**

### Use

Just clone the repo with git and then use the make command. An executable
called 'microshell' will then be available.
