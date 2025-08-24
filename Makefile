# =========================
# Project metadata
# =========================
N64_ROM_NAME  := shattered_realms_alpha1
N64_ROM_TITLE := Shattered Realms (alpha1)

# =========================
# Sources / Objects
# =========================
SRCS := main.c
OBJS := $(SRCS:%.c=build/%.o)

# Compile rule: main.c -> build/main.o  (uses CC/CFLAGS from n64.mk at run time)
build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c -o $@ $<

# =========================
# ROMFS (packed filesystem)
# =========================
ROMFS_DIR := romfs
MKDFS ?= mkdfs
ROMFS_IMG := build/romfs.dfs
N64_ROMFS := $(ROMFS_IMG)

# Pack ROMFS robustly
$(ROMFS_IMG): $(shell find $(ROMFS_DIR) -type f 2>/dev/null)
	mkdir -p $(dir $@)
	$(MKDFS) $@ $(ROMFS_DIR)

# =========================
# Bring in libdragon rules/toolchain
# =========================
include /usr/local/include/n64.mk

# >>> CRUCIAL: ensure the ELF depends on our OBJS so compile runs first
$(N64_ROM_NAME).elf: $(OBJS)

# =========================
# Convenience targets
# =========================
.PHONY: all clean
all: $(N64_ROM_NAME).z64

clean:
	rm -rf build $(N64_ROM_NAME).elf $(N64_ROM_NAME).z64
