default:
	mkdir -p misc
	darnit-stringtable config misc/config.ldsz
	darnit-fsimage misc ../bin/misc.ldi
	rm -Rf misc
	
	mkdir -p maps
	cp *.ldmz maps
	darnit-fsimage maps ../bin/maps.ldi
	rm -Rf maps
	
	mkdir -p assets
	cp *.png assets
	darnit-fsimage assets ../bin/assets.ldi
	rm -Rf assets
