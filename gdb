gdb 
command 


ex: 
gdb test.o 
-> (gdb) run 
-> (gdb) bt 


ex:
gdb test.o 
-> (gdb) run arg1 arg2
-> (gdb) bt 

compile:
gcc with -g to add debug info into program


watch global variable value:
ex:
(gdb) watch a
Hardware watchpoint 1: a
(gdb) run
Starting program: /private/var/root/test2.o 
Reading symbols for shared libraries +. done
Hardware watchpoint 1: a

Old value = 0
New value = 3
main () at test2.c:12
12		a = 5;
(gdb) c
Continuing.
Hardware watchpoint 1: a

Old value = 3
New value = 5
main () at test2.c:13
13		return 0;


