.PHONY: clean All

All:
	@echo "----------Building project:[ EnhancedDivideTreasure - Debug ]----------"
	@cd "EnhancedDivideTreasure" && "$(MAKE)" -f  "EnhancedDivideTreasure.mk"
clean:
	@echo "----------Cleaning project:[ EnhancedDivideTreasure - Debug ]----------"
	@cd "EnhancedDivideTreasure" && "$(MAKE)" -f  "EnhancedDivideTreasure.mk" clean
