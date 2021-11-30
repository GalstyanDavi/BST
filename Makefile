# the compiler: gcc for C program, define as g++ for C++
  CC = g++
 
 
  # The build target 
  TARGET = main
 
  all: $(TARGET)

 $(TARGET):$(TARGET).cpp
		$(CC)  -o $(TARGET) $(TARGET).cpp
clean:
		$(RM) $(TARGET)
