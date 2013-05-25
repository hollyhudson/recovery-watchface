/** \file
 * Hello, Pebble!
 *
 * Sample for the NYC Resistor Pebble programming class
 */
#include "pebble_os.h"
#include "pebble_app.h"

//! Generate your own UUID using `uuidgen` and replace it:
#define MY_UUID { \
        0x69, 0x5C, 0xE6, 0xFE, \
        0x5D, 0xC1, 0x43, 0x81, \
        0x85, 0x29, 0x9A, 0x82, \
        0xDB, 0x09, 0xA0, 0x69, \
        }

PBL_APP_INFO(
        MY_UUID,
        "Recovery",
        "holly",
        1, 0,
        INVALID_RESOURCE,
        APP_INFO_WATCH_FACE

);


static Window window;
static TextLayer text_time;
static TextLayer text_day;
static TextLayer text_month;
static char time_str_buffer[32];
static char day_str_buffer[32];
static char month_str_buffer[32];
static GFont myfont;
static Layer symbol_layer;

BmpContainer bg_img;

static void
handle_tick( AppContextRef ctx, PebbleTickEvent *event)
{
	if (clock_is_24h_style()){
		// 24 hour time
        string_format_time(
                time_str_buffer,
                sizeof(time_str_buffer),
                "%H:%M",
                event->tick_time
			        );
	}else{
		// 12 hour time
        string_format_time(
                time_str_buffer,
                sizeof(time_str_buffer),
                "%I:%M",
                event->tick_time
			        );

	}
     text_layer_set_text(&text_time, time_str_buffer);
	
	// Set Day of the month
	string_format_time(
                day_str_buffer,
                sizeof(day_str_buffer),
                "   %e",
                event->tick_time
			        );
	text_layer_set_text(&text_day, day_str_buffer);
	
	// Set Month
	string_format_time(
                month_str_buffer,
                sizeof(month_str_buffer),
                "  %b",
                event->tick_time
			        );
	text_layer_set_text(&text_month, month_str_buffer);
}


static void
handle_init( AppContextRef ctx)
{
	(void)ctx;

	// Fonts will NOT work without this!
	resource_init_current_app(&APP_RESOURCES);
	
	window_init(&window, "Hello, Pebble");
	window_stack_push(&window, true /* Animated */);
		
	// Create a container for the static background image (recovery symbol)
	bmp_init_container(RESOURCE_ID_IMAGE_RECOVERY_140, &bg_img);
	// place image
	bg_img.layer.layer.frame.origin.x = 35;
	bg_img.layer.layer.frame.origin.y = 3;

	layer_add_child(&window.layer, &bg_img.layer.layer);
	// draw the image
	layer_mark_dirty(&bg_img.layer.layer);
	
	// Tell it what font to use
	myfont = fonts_load_custom_font(
		resource_get_handle(RESOURCE_ID_FONT_QARMIC_SANS_24));

	// Add TIME
	// GRect takes x,y,w,h
	text_layer_init(&text_time, GRect(0,135,60,26));
	text_layer_set_font(&text_time, myfont);
	text_layer_set_text(&text_time, "");
	text_layer_set_background_color(&text_time, GColorClear);
	text_layer_set_text_color(&text_time, GColorBlack);
	layer_add_child(&window.layer, &text_time.layer);
	
	// Add DAY OF THE MONTH
	// GRect takes x,y,w,h
	text_layer_init(&text_day, GRect(75,118,73,58));
	text_layer_set_font(&text_day, myfont);
	text_layer_set_text(&text_day, "");
	text_layer_set_background_color(&text_day, GColorClear);
	text_layer_set_text_color(&text_day, GColorBlack);
	layer_add_child(&window.layer, &text_day.layer);
	
	// Change fonts so the month won't be too big'
	myfont = fonts_load_custom_font(
		resource_get_handle(RESOURCE_ID_FONT_QARMIC_SANS_18));
	
	// Add MONTH
	// GRect takes x,y,w,h
	text_layer_init(&text_month, GRect(75,144,73,58));
	text_layer_set_font(&text_month, myfont);
	text_layer_set_text(&text_month, "");
	text_layer_set_background_color(&text_month, GColorClear);
	text_layer_set_text_color(&text_month, GColorBlack);
	layer_add_child(&window.layer, &text_month.layer);
}


static void handle_deinit( AppContextRef ctx)
{
        (void)ctx;
	bmp_deinit_container(&bg_img);
}


void pbl_main( void *params)
{
        PebbleAppHandlers handlers = {
                .init_handler = handle_init,
                .deinit_handler = handle_deinit,
                .tick_info = {
                        .tick_handler = handle_tick,
                        // call tick_handler once per second
                        .tick_units = MINUTE_UNIT,
                },
        };

        app_event_loop(params, &handlers);
}