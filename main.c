#include <libdragon.h>
#include <string.h>

/* ---------- Try to include the DFS/ROMFS header under any known name ---------- */
#if defined(__has_include)
  #if __has_include(<filesystem.h>)
    #include <filesystem.h>
    #define SR_HAS_DFS 1
  #elif __has_include(<dfs.h>)
    #include <dfs.h>
    #define SR_HAS_DFS 1
  #elif __has_include(<dragonfs.h>)
    /* Some older libdragon builds use dragonfs.h */
    #include <dragonfs.h>
    #define SR_HAS_DFS 1
  #endif
#endif

/* ---------- If none of the headers are available, declare the minimal API ---------- */
#ifndef SR_HAS_DFS
  /* In libdragon, dfs_open returns an integer handle. */
  typedef int file_t;
  extern file_t dfs_open(const char *path);
  extern int    dfs_size(file_t f);
  extern int    dfs_read(void *ptr, int size, int count, file_t f);
  extern void   dfs_close(file_t f);
  extern void   dfs_init(int location);
  #ifndef DFS_DEFAULT_LOCATION
    /* Safe fallback: default ROMFS mount (0 works with stock builds) */
    #define DFS_DEFAULT_LOCATION 0
  #endif
#endif

/* Read a small text file from ROMFS into a buffer. */
static void read_text_file(const char *path, char *out, size_t outsz) {
    out[0] = 0;
    file_t f = dfs_open(path);
    if (!f) {
        strncpy(out, "(missing)", outsz - 1);
        out[outsz - 1] = 0;
        return;
    }
    int sz = dfs_size(f);
    if (sz < 0) {
        strncpy(out, "(error)", outsz - 1);
        out[outsz - 1] = 0;
        dfs_close(f);
        return;
    }
    if ((size_t)sz >= outsz) sz = (int)outsz - 1;
    dfs_read(out, 1, sz, f);
    out[sz] = 0;
    dfs_close(f);
}

int main(void) {
    /* Video: 320x240, 16-bit, double buffer */
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);
    console_init();

    /* Mount ROMFS (packed from /romfs in your repo) */
    dfs_init(DFS_DEFAULT_LOCATION);

    /* Read romfs/version.txt to prove assets are included */
    char version[64];
    read_text_file("/version.txt", version, sizeof(version));

    while (1) {
        display_context_t disp;
        while (!(disp = display_lock())) { }

        graphics_fill_screen(disp, 0x0000);
        printf("Shattered Realms (alpha)\n");
        printf("ROMFS version: %s\n", version);
        printf("Rendering... (reset in emulator to quit)\n");

        console_render();
        display_show(disp);
        wait_ms(16); /* ~60 FPS */
    }
    return 0;
}
