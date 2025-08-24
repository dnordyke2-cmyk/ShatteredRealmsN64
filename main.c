#include <libdragon.h>

int main(void) {
    console_init();
    console_set_render_mode(RENDER_MANUAL);
    console_clear();

    printf("Shattered Realms (alpha1)\n");
    printf("Build OK. Rendering every 250ms…\n");

    while (1) {
        console_render();
        wait_ms(250);
    }
    return 0;
}
