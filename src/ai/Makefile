# Project: Speedoman
include $(TOPDIR)/config.mk

CFLAGS += -fPIC
SRCFILES=$(wildcard *.c)
OBJFILES=$(SRCFILES:.c=.o)
LIB = ai.code
LDFLAGS += -shared -Wl,-soname,ai.code
.PHONY: all clean

all: $(OBJFILES) $(DEPENDS)
	@echo " [ LD ]	$(LIB)"
	@$(CC) $(OBJFILES) -o $(LIB) $(LDFLAGS)
	@echo " Done."
	@echo

clean:
	@echo " [ RM ]	$(OBJFILES)"
	@echo " [ RM ]	$(LIB)"
	@$(RM) $(OBJFILES)
	@$(RM) $(LIB)
	@echo "Done."
	@echo ""


%.o: %.c %.h
	@echo " [ CC ]	src/ai/$<"
	@$(CC) $(CFLAGS) -c -o $@ $< 

#muon.res:
#	@windres ../res/windows/svgestim.rc -O coff -o svgestim.res
