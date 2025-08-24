# =========================
# Project metadata
# =========================
N64_ROM_NAME  := shattered_realms_alpha
N64_ROM_TITLE := Shattered Realms (alpha)

# =========================
# Sources
# =========================
SRCS := src/main.c

# =========================
# ROMFS (packed filesystem)
# =========================
ROMFS_DIR := romfs
MKDFS ?= mkdfs
ROMFS_IMG := build/romfs.dfs

$(ROMFS_IMG): $(shell find $(ROMFS_DIR) -type f 2>/dev/null)
	mkdir -p $(dir $@)
	$(MKDFS) $@ $(ROMFS_DIR)

# Include this filesystem in the ROM
N64_ROMFS := $(ROMFS_IMG)

# =========================
# libdragon toolchain rules
# =========================
# Path valid inside anacierdem/libdragon container
include /usr/local/include/n64.mk

# =========================
# Convenience targets
# =========================
.PHONY: all clean
all: $(N64_ROM_NAME).z64

clean:
	rm -rf build $(N64_ROM_NAME).elf $(N64_ROM_NAME).z64
