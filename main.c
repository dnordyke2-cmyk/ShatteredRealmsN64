#include <libdragon.h>

int main(void) {
    /* Init video (320x240, 16bpp, double buffer) and console. */
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);
    console_init();

    while (1) {
        display_context_t disp;
        while (!(disp = display_lock())) { }

        /* Black clear + console text */
        graphics_fill_screen(disp, 0x0000);
        printf("Shattered Realms (alpha)\n");
        printf("Build OK. Rendering at ~60 FPS\n");
        printf("(ROMFS intentionally disabled for this test)\n");

        console_render();
        display_show(disp);
        wait_ms(16); /* ~60 FPS */
    }
    return 0;
}
