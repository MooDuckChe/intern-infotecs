CC = gcc
CFLAGS = -std=c++17 -lstdc++

# Цель по умолчанию
all: folder infotecs

folder: 
	mkdir -p ./Journals
# Цель для создания исполняемого файла
infotecs: dll.so main.o functions.o
	$(CC) -o infotecs main.o functions.o dll.so -Wl,-rpath,. $(CFLAGS) 

# Цель для создания динамической библиотеки
dll.so: dllmain.o
	$(CC) $(CFLAGS) -fPIC -shared -o dll.so dllmain.o

# Цель для создания объектного файла dllmain.o
dllmain.o: ./src/source/dllmain.cpp ./src/include/dllmain.h
	$(CC) $(CFLAGS) -fPIC -c -o dllmain.o ./src/source/dllmain.cpp

# Цель для создания объектного файла main.o
main.o: ./src/source/main.cpp ./src/include/include.h
	$(CC) $(CFLAGS) -fPIC -c -o main.o ./src/source/main.cpp

# Цель для создания объектного файла functions.o
functions.o: ./src/source/functions.cpp ./src/include/functions.h
	$(CC) $(CFLAGS) -fPIC -c -o functions.o ./src/source/functions.cpp

# Цель для очистки
all_clean:
	rm -f dllmain.o main.o functions.o dll.so infotecs
clean:
	rm -f dllmain.o main.o functions.o
