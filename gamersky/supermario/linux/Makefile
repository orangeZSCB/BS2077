mario.o:	bitmap.o input.o main.o game.o sprite.o plane.o mytime.o
	g++ -o lxmario bitmap.o input.o main.o game.o sprite.o plane.o mytime.o -lvgagl -lvga
	@mv lxmario ..

bitmap.o:	bitmap.cpp ../bitmap.h
	g++ -c -o bitmap.o bitmap.cpp

input.o:	input.cpp ../input.h
	g++ -c -o input.o input.cpp

game.o:		../game.cpp ../sprite.h ../plane.h ../sound.h ../bitmap.h ../mytime.h
	g++ -c -o game.o ../game.cpp

sprite.o:	../sprite.cpp ../sprite.h ../plane.h ../input.h ../bitmap.h ../mytime.h
	g++ -c -o sprite.o ../sprite.cpp

plane.o:	../plane.cpp ../plane.h ../bitmap.h
	g++ -c -o plane.o ../plane.cpp

main.o:		main.cpp ../game.h
	g++ -c -o main.o main.cpp

mytime.o:	mytime.cpp ../mytime.h
	g++ -c -o mytime.o mytime.cpp


clean:
	@rm -f *.o
