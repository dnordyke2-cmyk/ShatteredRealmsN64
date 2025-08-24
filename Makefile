# =========================
# Project metadata
# =========================
N64_ROM_NAME  := shattered_realms_alpha
N64_ROM_TITLE := Shattered Realms (alpha)

# =========================
# Objects (sources live at REPO ROOT; e.g., main.c -> main.o)
# =========================
# IMPORTANT: OBJS must be set *before* including n64.mk.
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
# libdragon toolchain rules
# =========================
# Valid in the anacierdem/libdragon container:
include /usr/local/include/n64.mk

# =========================
# Convenience targets
# =========================
.PHONY: all clean
all: $(N64_ROM_NAME).z64

clean:
	rm -rf build $(N64_ROM_NAME).elf $(N64_ROM_NAME).z64
