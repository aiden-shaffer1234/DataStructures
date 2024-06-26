make : proj3_mine.x proj3.o

proj3_mine.x : proj3.o Queue.hpp
	g++ -g proj3.o -o proj3_mine.x

proj3.o : proj3.cpp
	g++ -g -c proj3.cpp

clean:
	rm *.o

backup:
	cp -r *.h *.cpp *.hpp /home/majors/ashaffer/Backup_4530/Hw_3