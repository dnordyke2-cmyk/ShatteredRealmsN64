#include <libdragon.h>

/* Simple moving bar to prove frames are being presented. */
int main(void) {
    /* Video: 320x240, 16-bit, double buffer */
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);
    console_init();

    uint32_t t0 = TIMER_MICROS_NOW();
    int frame = 0;

    while (1) {
        display_context_t disp;
        while (!(disp = display_lock())) { }

        /* Clear screen to dark gray so the white bar pops. */
        graphics_fill_screen(disp, graphics_make_color(8,8,8,0));

        /* Draw a moving white bar across the screen. */
        int x = (frame % 320);
        for (int y = 60; y < 180; y++) {
            for (int w = 0; w < 20; w++) {
                if (x+w < 320) graphics_draw_pixel(disp, x+w, y, graphics_make_color(255,255,255,0));
            }
        }

        /* Simple FPS text using the console overlay. */
        if ((frame & 15) == 0) { /* update text every 16 frames */
            uint32_t dt_us = TIMER_MICROS_SINCE(t0);
            float fps = (dt_us > 0) ? (frame * 1000000.0f / dt_us) : 0.0f;
            console_clear();
            printf("Shattered Realms (alpha)\n");
            printf("Frame: %d   FPS: %.1f\n", frame, fps);
            printf("If you see a white bar moving left->right, video is good.\n");
        }

        console_render();
        display_show(disp);
        frame++;
        /* No wait_ms: let VI timing drive pacing through display_lock/display_show */
    }
    return 0;
}
