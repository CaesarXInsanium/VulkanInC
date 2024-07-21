CC=/usr/bin/gcc
CFLAGS=-std=gnu18 -Wall -Werror
LDFLAGS=-lglfw -lcglm -lvulkan

LVE=lve
APP=src
BIN=bin

lve_SOURCES= $(wildcard $(LVE)/**.c)
vk_SOURCES= $(wildcard $(APP)/**.c)
