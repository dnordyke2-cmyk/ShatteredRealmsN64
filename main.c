#include <libdragon.h>

int main(void) {
    /* 320x240, 32bpp, double buffer — friendlier to some Rice builds */
    display_init(RESOLUTION_320x240, DEPTH_32_BPP, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);
    console_init();
    console_set_render_mode(RENDER_MANUAL);

    int frame = 0;
    while (1) {
        display_context_t disp;
        while (!(disp = display_lock())) { }

        /* Dark gray clear */
        graphics_fill_screen(disp, graphics_make_color(8,8,8,0));

        /* Big moving white box (60px tall, 60px wide) */
        int x = (frame % 320);
        int y0 = 90, y1 = 150;
        int x0 = x, x1 = (x + 60 < 320) ? x + 60 : 319;
        for (int y = y0; y < y1; y++) {
            for (int x2 = x0; x2 <= x1; x2++) {
                graphics_draw_pixel(disp, x2, y, graphics_make_color(255,255,255,0));
            }
        }

        if ((frame & 15) == 0) {
            console_clear();
            printf("Shattered Realms (alpha)\n");
            printf("Frame: %d\n", frame);
            printf("You should see a WHITE BOX sliding left->right.\n");
        }

        console_render();
        display_show(disp);
        frame++;
        wait_ms(16);
    }
    return 0;
}
