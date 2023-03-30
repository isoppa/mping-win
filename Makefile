#Makefile

CC = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -O3

BINDIR = .
OBJDIR = .

PROGRAM = mping
OBJS = mping.o
DEPS = $(OBJS:.o=.d)

.SUFFIXES: .c .o

$(BINDIR)/$(PROGRAM): $(addprefix $(OBJDIR)/, $(OBJS))
	mkdir -p $(BINDIR)
	$(CC) $(CXXFLAGS) -o $(BINDIR)/$(PROGRAM) $^

$(OBJDIR)/%.o: ./%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CXXFLAGS) -o $@ -c $<

clean:
	$(RM) $(BINDIR)/$(PROGRAM) $(addprefix $(OBJDIR)/, $(OBJS)) $(addprefix $(OBJDIR)/, $(DEPS))

-include $(addprefix $(OBJDIR)/, $(DEPS))


