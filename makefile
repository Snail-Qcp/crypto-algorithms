objects=test_xxtea.o xxtea.o

test_xxtea : $(objects)
	g++ $(objects) -o test_xxtea

$(objects) : %.o : %.cpp
	g++ -std=c++11 -c $< -o $@

.PHONY : clean
clean : 
	-rm -f *.o test_xxtea
