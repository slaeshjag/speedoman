default:
	@echo "*** Building resource package ***"
	@mkdir -p data
	@echo " [DFSI] misc.ldi"
	@mkdir -p misc
	@darnit-stringtable config misc/config.ldsz 2>/dev/null
	@darnit-stringtable ai misc/ai_lookup.ldsz 2>/dev/null
	@darnit-stringtable lang misc/lang.ldsz 2>/dev/null
	@cp ../src/ai/ai.code misc/
	@darnit-fsimage misc data/misc.ldi
	@rm -Rf misc
	
	@echo " [DFSI] bin/maps.ldi"
	@mkdir -p maps
	@cp *.ldmz maps
	@darnit-fsimage maps data/maps.ldi
	@rm -Rf maps
	
	@echo " [DFSI] bin/assets.ldi"
	@mkdir -p assets
	@cp *.png assets
	@cp *.spr assets
	@cp *.lst assets
	@cp *.dmg assets
	@cp *.ttf assets
	@darnit-fsimage assets data/assets.ldi
	@rm -Rf assets
	
	@darnit-fsimage data data.ldi
	@rm -Rf data
	@cat data.ldi >> ../bin/speedoman
	@rm data.ldi
clean:
