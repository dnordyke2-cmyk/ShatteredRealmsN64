#include <libdragon.h>
#include <string.h>

/* Simple helper: read a small file from ROMFS into a buffer. */
static void read_text_file(const char *path, char *out, size_t outsz) {
    out[0] = 0;
    file_t f = dfs_open(path);
    if (!f) {
        strncpy(out, "(missing)", outsz-1);
        out[outsz-1] = 0;
        return;
    }
    int sz = dfs_size(f);
    if (sz < 0) {
        strncpy(out, "(error)", outsz-1);
        out[outsz-1] = 0;
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
    dfs_init( DFS_DEFAULT_LOCATION );

    /* Read romfs/version.txt to prove assets are included */
    char version[64];
    read_text_file("/version.txt", version, sizeof(version));

    while (1) {
        display_context_t disp;
        while (!(disp = display_lock())) { }

        /* Clear screen and draw console text each frame */
        graphics_fill_screen(disp, 0x0000);
        printf("Shattered Realms (alpha)\n");
        printf("ROMFS version: %s\n", version);
        printf("Rendering... (press reset in emulator to quit)\n");

        console_render();
        display_show(disp);
        wait_ms(16); /* ~60 FPS */
    }
    return 0;
}
