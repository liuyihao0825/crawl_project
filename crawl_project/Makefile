LIB_PATH = $(HOME)/liuyihao/scmph/lib2-64/
ULLIB_PATH = $(LIB_PATH)/ullib
HTTPLIB_PATH = $(LIB_PATH)/http

INCLUDE_DIR = -I$(ULLIB_PATH)/include -I$(HTTPLIB_PATH)/include
LIB_DIR = -L$(ULLIB_PATH)/lib/ -L$(HTTPLIB_PATH)/lib/ -lnewhttp -lullib -lpthread

CC = g++ -g

all:demo out

demo:Main.o Receive.o Dispatch.o Crawl.o Epoll.o
	$(CC) -o demo Main.o Receive.o Dispatch.o Crawl.o Epoll.o $(INCLUDE_DIR) $(LIB_DIR)

Main.o:Main.cpp Receive.h
	$(CC) -c Main.cpp $(INCLUDE_DIR)

Receive.o:Receive.cpp Receive.h Dispatch.h Crawl.h Epoll.h
	$(CC) -c Receive.cpp $(INCLUDE_DIR)

Dispatch.o:Dispatch.cpp Dispatch.h
	$(CC) -c Dispatch.cpp $(INCLUDE_DIR)

Crawl.o:Crawl.cpp Crawl.h Dispatch.h Epoll.h
	$(CC) -c Crawl.cpp $(INCLUDE_DIR)

Epoll.o:Epoll.cpp Epoll.h
	$(CC) -c Epoll.cpp $(INCLUDE_DIR)

out:
	cp -f demo output/bin/

clean:
	rm -rf *.o out.html demo output/bin/demo output/data/*.html output/log/crawllog*
