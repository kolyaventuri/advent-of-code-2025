C_FILES := $(wildcard src/*.c)
LIBS := $(wildcard src/lib/*.c)
OUT_DIR := out


$(shell mkdir -p $(OUT_DIR))

.PHONY: all run
all: run

$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

run: | $(OUT_DIR)
ifeq ($(FILE),)
	@for file in $(C_FILES); do \
		name=$$(basename $$(basename $$file .c)); \
		gcc -o $(OUT_DIR)/$$name $$file $(LIBS); \
	done
else
	gcc -o $(OUT_DIR)/$(basename $(notdir $(FILE))) src/$(FILE).c $(LIBS)
	@echo ==========
	@$(OUT_DIR)/$(basename $(notdir $(FILE)))
endif
