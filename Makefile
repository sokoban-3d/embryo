c_flags=-std=gnu11
cpp_flags=-std=gnu++0x
cc_flags=-MMD -g

ld_flags=-lm -lstdc++ -lbsd -lGL -lGLee -lglfw -lassimp 

# TODO: Find a better way to do this.
lib_src_c=$(wildcard **/*.c)
lib_src_cpp=$(wildcard **/*.cpp)
lib_src=$(lib_src_c) $(lib_src_cpp)

toplevel_src_c=$(wildcard *.c)
toplevel_src_cpp=$(wildcard *.cpp)
toplevel_src=$(toplevel_src_c) $(toplevel_src_cpp)

lib_obj_c=$(addprefix build/obj/, $(lib_src_c:.c=.c.o))
lib_obj_cpp=$(addprefix build/obj/, $(lib_src_cpp:.cpp=.cpp.o))
lib_obj=$(lib_obj_c) $(lib_obj_cpp)

toplevel_obj_c=$(addprefix build/obj/, $(toplevel_src_c:.c=.c.o))
toplevel_obj_cpp=$(addprefix build/obj/, $(toplevel_src_cpp:.cpp=.cpp.o))
toplevel_obj=$(toplevel_obj_c) $(toplevel_obj_cpp)

obj=$(lib_obj) $(toplevel_obj)

all: ref model_conv

clean:
	rm -rf build/*

.PHONY: ref model_conv

ref: build/ref

model_conv: build/model_conv

build/obj/%.c.o: %.c
	mkdir -p $(dir $@)
	cc $(cc_flags) $(c_flags) -c -o $@ $<

build/obj/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	cc $(cc_flags) $(cpp_flags) -c -o $@ $<

-include $(obj:.o=.d)

build/ref: build/obj/ref.c.o $(lib_obj)
	cc $(ld_flags) -o $@ $^

build/model_conv: build/obj/model_conv.cpp.o $(lib_obj)
	cc $(ld_flags) -o $@ $^
