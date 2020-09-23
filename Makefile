.PHONY: clean All

All:
	@echo "----------Building project:[ DivideTreasure - Debug ]----------"
	@cd "DivideTreasure" && "$(MAKE)" -f  "DivideTreasure.mk"
clean:
	@echo "----------Cleaning project:[ DivideTreasure - Debug ]----------"
	@cd "DivideTreasure" && "$(MAKE)" -f  "DivideTreasure.mk" clean
