CC = gcc
TARGET = intro_exe
OBJECTS = 

all : $(TARGET)

$(TARGET) : $(OBJECTS)
  $(CC) -o $@ $^
  
clean : 
  rm *.o intro_exe
