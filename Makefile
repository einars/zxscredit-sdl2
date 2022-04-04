CC	= gcc
CFLAGS	= -O2 -Wall
#CFLAGS	= -O2 -Wall -DUSE_DEBUG
LIBSDL	= `sdl2-config --libs`

OBJS	=        main.o          \
                 file.o          \
                 graphic.o       \
                 icons.o         \
                 help.o          \
                 stop.o          \
                 save.o          \
                 newfile.o       \
                 cancel.o        \
                 ok.o            \
                 warn.o          \
                 info.o          \
                 draw.o          \
                 cell.o          \
                 curattr.o       \
                 events.o        \
                 write.o         \
                 moving.o        \
                 actions.o       \
                 mouse.o         \
                 flash.o         \
                 efects.o        \
                 tape.o

all: zxscredit


zxscredit: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBSDL)

%.o:  %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o zxscredit
