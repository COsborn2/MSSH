FLAGS= -g -c -m32

EXE = mssh
MAIN = ./cscd340Lab6.c

ALIAS = ./alias/alias.o
HISTORY = ./history/history.o
LINKEDLIST = ./linkedlist/linkedList.o ./linkedlist/listUtils.o
PIPES = ./pipes/pipes.o
PROCESS = ./process/process.o
MAKEARGS = ./tokenize/makeArgs.o
UTILS= ./utils/myUtils.o ./utils/fileUtil.o

${EXE}:	${UTILS} ${ALIAS} ${HISTORY} ${LINKEDLIST} ${PIPES} ${PROCESS} ${MAKEARGS} ${MAIN}
	gcc -o ${EXE} ${MAIN} ${UTILS} ${ALIAS} ${HISTORY} ${LINKEDLIST} ${PIPES} ${PROCESS} ${MAKEARGS}


#=======================================================================================================================

alias.o:	./alias/alias.c ./alias/alias.h
	gcc  ${FLAGS} ./alias/alias.c

history.o:	./history/history.h ./history/history.c
	gcc ${FLAGS} ./history/history.c

#=======================================================================================================================

pipes.o:	./pipes/pipes.h ./pipes/pipes.c
	gcc  ${FLAGS} ./pipes/pipes.c

#=======================================================================================================================

process.o:	./process/process.h ./process/process.c
	gcc  ${FLAGS} ./process/process.c

#=======================================================================================================================

tokenize.o:	./tokenize/makeArgs.h ./tokenize/makeArgs.c ./utils/myUtils.h
	gcc  ${FLAGS} ./tokenize/makeArgs.c

#=======================================================================================================================

listUtils.o:	./linkedlist/listUtils.c listUtils.h
	gcc  ${FLAGS} ./linkedlist/listUtils.c

linkedList.o:	./linkedlist/linkedList.h ./linkedlist/linkedList.c ./linkedlist/requiredIncludes.h
	gcc ${FLAGS} ./linkedlist/linkedList.c

#=======================================================================================================================

myUtils.o:	./utils/myUtils.h ./utils/myUtils.c
	gcc ${FLAGS} ./utils/myUtils.c

fileUtil.o:	./utils/fileUtil.h ./utils/fileUtil.c
	gcc ${FLAGS} ./utils/fileUtil.c

#=======================================================================================================================

clean:
	rm linkedlist/*.o
	rm utils/*.o
	rm alias/*.o
	rm history/*.o
	rm tokenize/*.o
	rm pipes/*.o
	rm process/*.o
	rm ${EXE}