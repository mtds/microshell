# Obj files for the shell executable:
objects = main.o builtin.o shell_err.o gettoken.o command.o invoke.o ignoresig.o redirect.o statusprt.o waitfor.o closefds.o

# GCC compiler options:
cc = gcc
ccflags = -c -std=gnu11 -O2 -Wall -Wextra -D_FORTIFY_SOURCE=2 -fstack-protector-strong

microshell : $(objects)
	@$(cc) -o microshell $(objects)

main.o :  main.c commdefs.h
	@$(cc) $(ccflags) main.c

builtin.o: builtin.c commdefs.h
	@$(cc) $(ccflags) builtin.c

shell_err.o: shell_err.c commdefs.h
	@$(cc) $(ccflags) shell_err.c

gettoken.o: gettoken.c commdefs.h
	@$(cc) $(ccflags) gettoken.c

command.o: command.c commdefs.h
	@$(cc) $(ccflags) command.c

invoke.o: invoke.c commdefs.h
	@$(cc) $(ccflags) invoke.c

ignoresig.o: ignoresig.c commdefs.h
	@$(cc) $(ccflags) ignoresig.c

redirect.o: redirect.c commdefs.h
	@$(cc) $(ccflags) redirect.c

statusprt.o: statusprt.c commdefs.h
	@$(cc) $(ccflags) statusprt.c

waitfor.o: waitfor.c commdefs.h
	@$(cc) $(ccflags) waitfor.c

closefds.o: closefds.c commdefs.h
	@$(cc) $(ccflags) closefds.c

clean:
	rm -f microshell microshell_d microshell_asan $(objects)

debug: $(objects)
	@$(cc) -g -o microshell_d $(objects)

asan: commdefs.h
	@$(cc) -std=gnu11 -g -fsanitize=address,undefined -fno-omit-frame-pointer -o microshell_asan *.c
