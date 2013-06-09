default:
	@echo " [DFSI] bin/misc.ldi"
	@mkdir -p misc
	@darnit-stringtable config misc/config.ldsz 2>/dev/null
	@darnit-fsimage misc ../bin/misc.ldi
	@rm -Rf misc
	
	@echo " [DFSI] bin/maps.ldi"
	@mkdir -p maps
	@cp *.ldmz maps
	@darnit-fsimage maps ../bin/maps.ldi
	@rm -Rf maps
	
	@echo " [DFSI] bin/assets.ldi"
	@mkdir -p assets
	@cp *.png assets
	@darnit-fsimage assets ../bin/assets.ldi
	@rm -Rf assets
clean:
