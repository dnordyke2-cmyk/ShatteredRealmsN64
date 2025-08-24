#include <libdragon.h>

int main(void) {
    /* 320x240, 16bpp, double buffer */
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);
    console_init();

    int frame = 0;

    while (1) {
        display_context_t disp;
        while (!(disp = display_lock())) { }

        /* Dark gray clear */
        graphics_fill_screen(disp, graphics_make_color(8,8,8,0));

        /* Draw a 20px white bar moving left->right to prove frames present */
        int x = (frame % 320);
        for (int y = 60; y < 180; y++) {
            for (int w = 0; w < 20; w++) {
                if (x + w < 320)
                    graphics_draw_pixel(disp, x + w, y, graphics_make_color(255,255,255,0));
            }
        }

        /* Simple text overlay */
        if ((frame & 15) == 0) {       /* update text every 16 frames */
            console_clear();
            printf("Shattered Realms (alpha)\n");
            printf("Frame: %d\n", frame);
            printf("You should see a white bar moving.\n");
        }

        console_render();
        display_show(disp);
        frame++;

        /* Keep pacing gentle; VI timing also gates us via display_lock/display_show */
        wait_ms(16);
    }

    return 0;
}
