OBJS = main.o hashtable.o student.o skiplist.o
SOURCE = main.cpp hashtable.cpp student.cpp skiplist.cpp
HEADER = main.h hashtable.h student.h skiplist.h
OUT = stucs
CC = g++
FLAGS  = -c -g

$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $@

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

hashtable.o: hashtable.cpp
	$(CC) $(FLAGS) hashtable.cpp	

student.o: student.cpp
	$(CC) $(FLAGS) student.cpp

skiplist.o: skiplist.cpp
	$(CC) $(FLAGS) skiplist.cpp

clean: 
	rm -f $(OBJS) $(OUT)

count:
	wc $(SOURCE) $(HEADER)
