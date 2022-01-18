#######################
# Makefile
#######################

# link parameter
CC := g++
AR := ar

#PATH
ifeq (,$(PRO_DIR))
  PRO_DIR =$(shell pwd)
endif
SRC_PATH = $(PRO_DIR)/src
CLICKHOUSE_PATH = $(PRO_DIR)/../clickhouse

#FLAGS
LIBS = -pthread -lpthread 
LIBS += -static -lclickhouse-cpp-lib-static -labsl-lib -lcityhash-lib -llz4-lib
LIBS += -L$(CLICKHOUSE_PATH)/libs
CFLAGS := -g -Wall -std=c++17 -O3
CFLAGS += -I $(CLICKHOUSE_PATH)/include/
CFLAGS += -I $(CLICKHOUSE_PATH)/include/contrib
CFLAGS += -I $(SRC_PATH)
TARGET = out

# all object files.
.PHONY:all
all: $(TARGET)

out:$(SRC_PATH)/main.o 
	$(CC) $(CFLAGS) -o out $(SRC_PATH)/main.o $(LIBS)
	
$(SRC_PATH)/main.o:$(SRC_PATH)/main.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY:clean
clean:
	rm -f $(SRC_PATH)/*.o
	rm -f out