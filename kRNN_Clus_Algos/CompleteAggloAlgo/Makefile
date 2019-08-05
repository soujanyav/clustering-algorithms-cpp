CC = g++ -g

main: main.o error.o Point.o DataSet.o Friendship.o MyKBestFriends.o
	$(CC) -o main main.o error.o Point.o DataSet.o Friendship.o MyKBestFriends.o -lglut -lGLU -lGL -lm

main.o: main.cpp error.h Point.h DataSet.h Friendship.h MyKBestFriends.h header.h
	$(CC) -c main.cpp

error.o: error.cpp error.h
	$(CC) -c error.cpp

Point.o: Point.cpp Point.h error.h header.h
	$(CC) -c Point.cpp

DataSet.o: DataSet.cpp DataSet.h error.h header.h
	$(CC) -c DataSet.cpp

Friendship.o: Friendship.cpp DataSet.h error.h header.h
	$(CC) -c Friendship.cpp

MyKBestFriends.o: MyKBestFriends.cpp Friendship.h DataSet.h error.h header.h
	$(CC) -c MyKBestFriends.cpp

clean:
	rm -f *.o
