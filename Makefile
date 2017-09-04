run: bin/main.o bin/utils.o bin/kalman.o
	g++ -std=c++1y bin/main.o bin/utils.o bin/kalman.o `pkg-config opencv --cflags --libs` -o run

bin/main.o: src/main.cpp include/main.h
	g++ -c -std=c++1y src/main.cpp -o bin/main.o

bin/utils.o: src/utils.cpp include/utils.h
	g++ -c -std=c++1y src/utils.cpp -o bin/utils.o

bin/kalman.o: src/kalman.cpp include/kalman.h
	g++ -c -std=c++1y src/kalman.cpp -o bin/kalman.o

clean:
	rm bin/*.o run