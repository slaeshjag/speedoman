# Project: Speedoman
include $(TOPDIR)/config.mk

SRCFILES=$(wildcard *.c)
OBJFILES=$(SRCFILES:.c=.o)
BIN = ../bin/speedoman
.PHONY: all clean

all: $(OBJFILES) $(DEPENDS)
	@echo " [ LD ]	$(BIN)"
	@$(CC) $(OBJFILES) -o $(BIN) $(LDFLAGS)
	@echo " [ CD ] src/ai"
	+@make -C ai/
	@echo " Done."
	@echo

clean:
	@echo " [ RM ]	$(OBJFILES)"
	@echo " [ RM ]	$(BIN)"
	@$(RM) $(OBJFILES)
	@$(RM) $(BIN)
	@echo " [ CD ] src/ai"
	+@make -C ai/ clean
	@echo "Done."
	@echo ""


%.o: %.c %.h
	@echo " [ CC ]	src/$<"
	@$(CC) $(CFLAGS) -c -o $@ $< 

#muon.res:
#	@windres ../res/windows/svgestim.rc -O coff -o svgestim.res
