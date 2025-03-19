/*
 * Vinci
 *
 * Copyright (C) 2025 Orastron Srl unipersonale
 *
 * Vinci is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Vinci is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Vinci. If not, see <http://www.gnu.org/licenses/>.
 *
 * File author: Paolo Marrone
 */

#include "vinci.h"

#include <string.h>
#include <stdio.h>

#if defined(_WIN32) || defined(__CYGWIN__)
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP(ms) usleep(ms * 1000)
#endif

vinci *g;
window *w1, *w2;
char active_windows = 0;

static void on_close(window *w) {
	printf("on_close %p \n", (void*)w); fflush(stdout);
	window_free(w);
	active_windows--;
}

static void on_mouse_press (window *w, int32_t x, int32_t y, uint32_t state) {
	printf("on_mouse_press %p %d %d %u \n", (void*)w, x, y, state);
}

static void on_mouse_release (window *w, int32_t x, int32_t y, uint32_t state) {
	printf("on_mouse_release %p %d %d %u \n", (void*)w, x, y, state);
}

static void on_mouse_move (window *w, int32_t x, int32_t y, uint32_t state) {
	printf("on_mouse_move %p %d %d %u \n", (void*)w, x, y, state);
}

static void on_window_resize (window *w, int32_t width, int32_t height) {
	printf("on_window_resize %p %d %d \n", (void*) w, width, height);
}

static void tick(void) {
    vinci_idle(g);
}

int main (void) {

	// Vinci init
	g = vinci_new();
	// TODO: check for errors

	// w1
	struct window_cbs w1cbs;
	memset(&w1cbs, 0, sizeof(window_cbs));
	w1cbs.on_window_close  = on_close;
	w1cbs.on_mouse_press   = on_mouse_press;
	w1cbs.on_mouse_release = on_mouse_release;
	w1cbs.on_mouse_move    = on_mouse_move;
	w1cbs.on_window_resize = on_window_resize;

	w1 = window_new(g, NULL, 300, 500, &w1cbs);
	on_window_resize(w1, window_get_width(w1), window_get_height(w1)); // This is needed for x only
	window_show(w1);

	// w2

	struct window_cbs w2cbs;
	memset(&w2cbs, 0, sizeof(window_cbs));
	w2cbs.on_window_close  = on_close;
	w2cbs.on_mouse_press   = on_mouse_press;
	w2cbs.on_mouse_release = on_mouse_release;
	w2cbs.on_mouse_move    = on_mouse_move;
	w2cbs.on_window_resize = on_window_resize;

	w2 = window_new(g, NULL, 500, 500, &w2cbs);
	on_window_resize(w2, window_get_width(w2), window_get_height(w2));
	window_show(w2);

	// I dare you to find a worse timer :)
	active_windows = 2;
	while (active_windows > 0) {
        tick();
        SLEEP(20);
    }

	vinci_destroy(g);
}