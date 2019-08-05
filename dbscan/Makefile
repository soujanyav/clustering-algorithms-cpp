CC = g++ -g

main: main.o error.o Point.o DataSet.o Dbscan.o
	$(CC) -o main main.o error.o Point.o DataSet.o Dbscan.o -lm

main.o: main.cpp error.h Point.h DataSet.h Dbscan.h header.h
	$(CC) -c main.cpp

error.o: error.cpp error.h
	$(CC) -c error.cpp

Point.o: Point.cpp Point.h error.h header.h
	$(CC) -c Point.cpp

DataSet.o: DataSet.cpp DataSet.h error.h header.h
	$(CC) -c DataSet.cpp

Dbscan.o: Dbscan.cpp Dbscan.h error.h header.h
	$(CC) -c Dbscan.cpp

clean:
	rm -f *.o
