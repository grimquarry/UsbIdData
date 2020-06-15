OBJS = *.cpp
CXX = g++ -std=c++17
CPPFLAGS = -WALL 

app: $(OBJS)
	$(CXX) -o run $(OBJS) $(LDLIBS)

clean:
	$(RM) run
