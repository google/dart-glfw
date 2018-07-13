CXX=clang++
CXXFLAGS = -Wall -Werror

ifneq ($(strip $(GLFW_INCLUDE)),)
CXXFLAGS += -I$(GLFW_INCLUDE)
endif

ifneq ($(strip $(DART_INCLUDE)),)
CXXFLAGS += -I$(DART_INCLUDE)
endif

CXXFLAGS += -fPIC -DDART_SHARED_LIB -std=c++11


LDFLAGS = -shared -Wl,-soname=libglfw_extension.so

ifneq ($(strip $(GLFW_LIB)),)
LDFLAGS += -L$(GLFW_LIB)
endif

LDFLAGS += -lglfw


all: glfw_extension

OBJS = src/glfw_extension.o src/instantiate_glfw_classes.o src/manual_bindings.o src/util.o src/generated/function_list.o src/generated/glfw_bindings.o

glfw_extension: $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o libglfw_extension.so

src/glfw_extension.o: src/glfw_extension.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/instantiate_glfw_classes.o: src/instantiate_glfw_classes.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/manual_bindings.o: src/manual_bindings.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/util.o: src/util.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/generated/function_list.o: src/generated/function_list.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/generated/glfw_bindings.o: src/generated/glfw_bindings.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm src/*.o src/generated/*.o libglfw_extension.so
