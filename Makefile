## PRoject: Speedoman

include config.mk
MAKEFLAGS	+=	--no-print-directory
TOPDIR		=	$(shell pwd)
export TOPDIR

default:
	@mkdir -p bin/
	@echo " [ CD ] src/"
	+@make -C src/
	@echo " [ CD ] res/"
	+@make -C res/
	@echo
	@echo "*** Build complete ***"

clean:
	@echo " [ CD ] src/"
	+@make -C src/ clean
	@echo " [ CD ] res/"
	+@make -C res/ clean
	@$(RM) bin/
