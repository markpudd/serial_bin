LINK_TARGET = bitstream_test

OBJS = bitstream.o bitstream_test.o

all: $(LINK_TARGET)

$(LINK_TARGET) : $(OBJS)
	 gcc -o $@ $^

%.o : %.c
	 gcc -o $@ -c $<
     
clean:
	 rm -f $(LINK_TARGET) $(OBJS)
	 
bitstream_test.o : bitstream.o