skiplist: skiplist.cpp
#		${CC} ${CFLAGS} z_simulation.cpp -o z_simulation
		g++ -g -std=gnu++11 skiplist.cpp -o skiplist

clean:
		rm -f skiplist
