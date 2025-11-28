C_FILES := $(wildcard src/*.c)
OUT_DIR := out


$(shell mkdir -p $(OUT_DIR))

.PHONY: all
all: run

run:
ifeq ($(FILE),)
	@for file in $(C_FILES); do \
		name=$$(basename $$(basename $$file .c)); \
		gcc -o $(OUT_DIR)/$$name $$file; \
	done
else
	gcc -o $(OUT_DIR)/$(basename $(notdir $(FILE))) src/$(FILE).c
	@echo ==========
	@$(OUT_DIR)/$$FILE/$(basename $(notdir $(FILE)))
endif
