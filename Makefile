makefile
command

general makefile name: 
Makefile 

rule format: 
Target:Dependencies 
commands 

(1) Target: usually the object file. 
Or fake target to remove all object files 


(2) Dependencies: the file to determine when to build target 
if timestamp of the file is newer than target, then rebuild target 
if dependency file is target of other rule, then Make will also build this target to generate 
final target 

(3) commands: start with Tab 
a new shell is executed for a new command(start with Tab) 
ex: 
test: test.c 
cd abc; rm *.o 
rm *.o 
first rm will clean *.o in abc/ 
second rm will clean *.o in current directory 

multiple commands in one line: 
seperated by ; 


split one line into multiple lines: 
use \ 


define and use variable in Makefile: 
use $ + ( ) to access variable 
ex: 
targets = test.o 
$(targets): test.c 
gcc -c test.c 

two methods to define variable: 
(1) target = test.o 
the value of variable is determined after scanning all content of Makefile 
(2) target := test.o 
the value of variable is determined at the time of definition 

defualt target: 
Makefile usually contains many rules. Make only build the first target specified in the Makefile 


Rule to install: 
usually install object files into some location 

print message: 
use @echo 
ex: 
@echo "hello" 

not print message for command 
add @ 
ex: 
@gcc -c test.c 


comment: 
use # 

include files: 
use include 
goal: like the content of inclueded files are inserted into makefile 
ex: 
(1) include test.in test2.in 
(2) include *.in 

implicit rule: 
ex: 
OBJS = ftp.o common.o 
HDRS = ftp.h common.h 
CFLAGS = -g -O2 
TARGETS = ftp 
CC = gcc 
# Default Target 
ftp: $(OBJS) $(HDRS) 
$(CC) $(OBJS) -o ftp 

ftp.o and common.o are created from implicit rule 

command: 
(1) make 

(2) build non-default goal: 
ex: 
make ftp 
ftp is target name 