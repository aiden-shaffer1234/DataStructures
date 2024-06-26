make : matrix_driver.x test_vector.x

test_vector.x : test_vector.o
	g++ -g test_vector.o -o test_vector.x

test_vector.o : test_vector.cpp
	g++ -g -c test_vector.cpp

matrix_driver.x : matrix_driver.o
	g++ -g matrix_driver.o -o matrix_driver.x

matrix_driver.o : matrix_driver.cpp
	g++ -g -c matrix_driver.cpp

clean:
	rm *.o

backup:
	cp -r *.h *.cpp *.hpp /home/majors/ashaffer/Backup_4530/Hw_2

	

