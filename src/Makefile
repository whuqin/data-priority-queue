GCC=g++

VERSION=-DVERSION="\"data-pq 1.0.0.0

VERSION64_SIGN=64bit\""
VERSION32_SIGN=\""

ifeq ($(MAC),64)
	VERSION+=$(VERSION64_SIGN)
	USERFLAGS=-fPIC
else
	VERSION+=$(VERSION32_SIGN)
endif

CPPFLAGS = -g -finline-functions -W -Wall -Winline -pipe -D_DEBUG $(VERSION)
#CPPFLAGS = -g -finline-functions -W -Wall -Winline -pipe -O2 $(VERSION)

all : output

.PHONY: clean
clean:
	rm -f *.o 
	rm -rf output

output : libdata-pq.a
	mkdir -p output output/lib output/include output/bin
	cp libdata-pq.a output/lib
	cp *.h output/include
	mkdir -p ../output ../output/lib ../output/include
	cp libdata-pq.a ../output/lib
	cp *.h ../output/include

libdata-pq.a :  pri_queue.o fifo_queue.o data_backup.o
	ar rcv libdata-pq.a pri_queue.o fifo_queue.o data_backup.o
	ranlib libdata-pq.a

#cat_to_stderr : cat_to_stderr.o

%.o	: %.cpp
	$(GCC) $(CPPFLAGS) -c $< -o $@ 
