# =========================
# Project metadata
# =========================
N64_ROM_NAME  := shattered_realms_alpha
N64_ROM_TITLE := Shattered Realms (alpha)

# =========================
# Sources / Objects (compile src/*.c -> build/*.o)
# =========================
SRCS := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c,build/%.o,$(SRCS))

# =========================
# ROMFS (packed filesystem)
# =========================
ROMFS_DIR := romfs
MKDFS ?= mkdfs
ROMFS_IMG := build/romfs.dfs
N64_ROMFS := $(ROMFS_IMG)

# Bring in libdragon rules/toolchain (provides CC/CFLAGS and link rules)
include /usr/local/include/n64.mk

# Compile rule: make sure build/ exists, then compile
build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c -o $@ $<

# Pack ROMFS robustly
$(ROMFS_IMG): $(shell find $(ROMFS_DIR) -type f 2>/dev/null)
	mkdir -p $(dir $@)
	$(MKDFS) $@ $(ROMFS_DIR)

# Convenience targets
.PHONY: all clean
all: $(N64_ROM_NAME).z64

clean:
	rm -rf build $(N64_ROM_NAME).elf $(N64_ROM_NAME).z64
