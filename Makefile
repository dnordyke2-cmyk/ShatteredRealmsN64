# =========================
# Project metadata
# =========================
N64_ROM_NAME  := shattered_realms_alpha
N64_ROM_TITLE := Shattered Realms (alpha)

# =========================
# Objects (use libdragon's default %.o: %.c in SAME DIR)
# =========================
# Keep sources at the REPO ROOT (e.g., main.c) so the default rule applies.
OBJS := main.o

# =========================
# ROMFS (packed filesystem)
# =========================
ROMFS_DIR := romfs
MKDFS ?= mkdfs
ROMFS_IMG := build/romfs.dfs
N64_ROMFS := $(ROMFS_IMG)

$(ROMFS_IMG): $(shell find $(ROMFS_DIR) -type f 2>/dev/null)
	mkdir -p $(dir $@)
	$(MKDFS) $@ $(ROMFS_DIR)

# =========================
# Bring in libdragon rules/toolchain
# =========================
include /usr/local/include/n64.mk

# =========================
# Convenience targets
# =========================
.PHONY: all clean
all: $(N64_ROM_NAME).z64

clean:
	rm -rf build $(N64_ROM_NAME).elf $(N64_ROM_NAME).z64
