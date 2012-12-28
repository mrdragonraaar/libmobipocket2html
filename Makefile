CC = gcc
CCFLAGS = -Wall -ansi
INCDIR = include/
INCLUDES = -I$(INCDIR)
SRCDIR = src/
SRC = mobipocket2html.c mobipocket2html_a.c mobipocket2html_img.c base64.c
OBJ = $(SRC:.c=.o)
LIBS = -lmobipocket
LIB = libmobipocket2html.a
INSTALLDIR = /usr/local/
INSTALLDIRINC = $(INSTALLDIR)include/mobipocket2html/
INSTALLDIRLIB = $(INSTALLDIR)lib/

all: $(SRC) $(LIB)

$(SRC):
	$(CC) $(INCLUDES) $(CCFLAGS) -c $(SRCDIR)$@ $(LIBS)

$(LIB):
	ar rcs $(LIB) $(OBJ)
	ranlib $(LIB)

install:
	mkdir -p $(INSTALLDIRINC)
	cp $(INCDIR)*.h $(INSTALLDIRINC)
	cp $(LIB) $(INSTALLDIRLIB)

clean:
	rm -f $(OBJ) $(LIB)
