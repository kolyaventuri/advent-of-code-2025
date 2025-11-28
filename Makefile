C_FILES := $(wildcard src/*.c)
LIBS := $(wildcard src/lib/*.c)
FLAGS := -O0
OUT_DIR := out
REPORT_DIR := report


$(shell mkdir -p $(OUT_DIR))

.PHONY: all run report
all: run

$(OUT_DIR)/:
	@mkdir -p $(OUT_DIR)

$(REPORT_DIR)/.dirstamp:
	@mkdir -p $(REPORT_DIR)

run: | $(OUT_DIR)/
ifeq ($(FILE),)
	@for file in $(C_FILES); do \
		name=$$(basename $$(basename $$file .c)); \
		echo Building $$name...;\
		clang $(FLAGS) -o $(OUT_DIR)/$$name $$file $(LIBS); \
	done
else
	OUT_FILE=$(basename $(notdir $(FILE)))
	clang $(FLAGS) -o $(OUT_DIR)/$$FILE src/$(FILE).c $(LIBS)
	@echo ==========
	@$(OUT_DIR)/$(basename $(notdir $(FILE)))
endif

report: | $(OUT_DIR)/ $(REPORT_DIR)/.dirstamp
ifeq ($(FILE),)
	$(error FILE is required to run in report mode. Usage: make report FILE=day0)
else
	@echo "Running report for $(FILE)..."
	@OUT_FILE=$$(basename $(notdir $(FILE))); \
	clang $(FLAGS) -o $(OUT_DIR)/$$OUT_FILE src/$(FILE).c $(LIBS); \
	REPORT_FILE=$(REPORT_DIR)/$$OUT_FILE.md; \
	printf '# Report for %s\n\n' "$$OUT_FILE" > "$$REPORT_FILE"; \
	{ ./prettytime.sh ./out/$$FILE; } >> "$$REPORT_FILE" 2>&1; \
	printf '\n\n' >> "$$REPORT_FILE"; \
	printf '`leaks --atExit --list -- ./out/%s`\n```\n' "$$OUT_FILE" >> "$$REPORT_FILE"; \
	{ leaks -q --atExit --list -- ./out/$$OUT_FILE; } | sed -n '/^leaks Report Version:/,$$p' >>  "$$REPORT_FILE" 2>&1 || true; \
	printf '```\n' >> "$$REPORT_FILE"
endif
