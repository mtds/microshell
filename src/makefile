# Obj files for the shell executable:
objects = main.o builtin.o shell_err.o gettoken.o command.o invoke.o ignoresig.o redirect.o statusprt.o waitfor.o

# GCC compiler options:
ccflags = -c -w

microshell : $(objects) 
	@gcc -s -o microshell $(objects)

main.o :  main.c commdefs.h
	@gcc $(ccflags) main.c

builtin.o: builtin.c commdefs.h
	@gcc $(ccflags) builtin.c

shell_err.o: shell_err.c
	@gcc $(ccflags) shell_err.c

gettoken.o: gettoken.c commdefs.h
	@gcc $(ccflags) gettoken.c

command.o: command.c commdefs.h
	@gcc $(ccflags) command.c

invoke.o: invoke.c commdefs.h
	@gcc $(ccflags) invoke.c

ignoresig.o: ignoresig.c commdefs.h
	@gcc $(ccflags) ignoresig.c

redirect.o: redirect.c commdefs.h
	@gcc $(ccflags) redirect.c

statusprt.o: statusprt.c commdefs.h
	@gcc $(ccflags) statusprt.c

waitfor.o: waitfor.c commdefs.h
	@gcc $(ccflags) waitfor.c

clean: 
	rm -f microshell* $(objects)

debug: $(objects)
	@gcc -g -o microshell_d $(objects)
