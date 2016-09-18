#include "pebble.h"

static Window *window;
static TextLayer *nameText_layer;
static TextLayer *LogText_layer;

typedef void(* ClickConfigProvider)(void *context);

enum AngelDataKey {
  
  // sotres initial angle value
  ANGEL_DATA_KEY = 0x0
};

//Reserve global memory to store an AppSync struct and your Dictionary:


// Some methods of the app are commented due to non-availability of mobile app
// static AppSync sync;
// static uint8_t sync_buffer[32];

// static void sync_error_callback(DictionaryResult dict_error, AppMessageResult
//                                app_message_error, void *context){
//   APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Sync error: %d", app_message_error);
// }

// static void sync_tuple_changed_callback(const uint32_t key, const Tuple *new_tuple, const 
//                                        Tuple *old_tuple, void *context){
//   switch(key){
//     case ANGEL_DATA_KEY:
//         text_layer_set_text(nameText_layer, new_tuple->value->cstring);
//     break;
//   }
// }

//This method has been commented out as the mobile-app is still in development-process
// static void setupAppSyncWithInitialData(void){
//   //Open App message with inbox and outbox buffersize
//   const int inbound_size = 64;
//   const int outbound_size = 64;
  
//   app_message_open(inbound_size,outbound_size);
  
//   //Store initial data as key value pairs in Tuplet type;
//   Tuplet initial_values[]={
//     TupletCString(ANGEL_DATA_KEY,"Angel value")
//   };
  
//   //Initialize the synchronization
//   app_sync_init(&sync,sync_buffer,sizeof(sync_buffer),initial_values,ARRAY_LENGTH
//                (initial_values), sync_tuple_changed_callback, sync_error_callback,NULL);
  
// }


static void select_click_handler(ClickRecognizerRef recognizer, void *context){
  text_layer_set_text(nameText_layer, "Angel value sent");//actual angel value goes here
  
  // This is where you send data back to the phone
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  
  Tuplet value = TupletCString(1,"a-ok"); // send ack to phone
  dict_write_tuplet(iter, &value);
  
  app_message_outbox_send();
  text_layer_set_text(LogText_layer,"Ack sent!");
  
// This part has been commented out as the mobile-app is still in development-process
//   Tuplet new_values[]={
//     TupletCString(ANGEL_DATA_KEY, "New angel value"),
//   };
  
//   app_sync_set(&sync, new_values, 2);
  
}

static void click_config_provider(void *context){
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

// Called after an incoming message is received
static void in_received(DictionaryIterator *iterator, void *context){
  
  // Check for fields you expect to receieve from phone
  Tuple *text_tuple = dict_find(iterator, 0); // look for incoming ack;
  
  // Action on the found fields received
  if(text_tuple){
     text_layer_set_text(nameText_layer,text_tuple->value->cstring);
  }
  
  //text_layer_set_text_(LogText_layer, "in_received");
}

// Called after an incoming message is dropped
static void in_dropped(AppMessageResult reason, void *context){
  text_layer_set_text(LogText_layer, "404"); 
}

// Called after an outbound message has been sent and the reply has been received
static void out_sent(DictionaryIterator *iterator, void *context){
  text_layer_set_text(LogText_layer,"success!"); // ack sent by phone app
}

// Called after an outbound message has not been sent successfully
static void out_failed(DictionaryIterator *iterator, AppMessageResult reason, void *context){
  text_layer_set_text(LogText_layer,"No Signa!");
}


static void setupAppMessage(void){
  
  // Registering all the message handlers
  app_message_register_inbox_received(in_received);
  app_message_register_inbox_dropped(in_dropped);
  app_message_register_outbox_sent(out_sent);
  app_message_register_outbox_failed(out_failed);
  
  //1. Open App message with Inbox and outbox buffer size
  const int inbound_size = 64; // size of the data coming out
  const int outbound_size = 64; // size of the data coming in
  app_message_open(inbound_size, outbound_size);
  
}

static void init() {
  
  //Create and display a window
  window = window_create();
  window_stack_push(window, true);
  
  window_set_click_config_provider(window,click_config_provider);
  
  //Get window root layer and its bounds
  Layer* window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  //Create a name text layer
  nameText_layer = text_layer_create((GRect){.origin={0,30}, .size={bounds.size.w,40}});
  text_layer_set_text_alignment(nameText_layer, GTextAlignmentCenter);
  text_layer_set_text(nameText_layer, "Angel: 75.36°"); //Angel heading goes here
  text_layer_set_font(nameText_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_alignment(nameText_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(nameText_layer));
  
  //Create a log text layer
  LogText_layer = text_layer_create((GRect){.origin={0,70}, .size={bounds.size.w, 30}});
  text_layer_set_text_alignment(LogText_layer, GTextAlignmentCenter);
  text_layer_set_text(LogText_layer, "Log: Recording...");
  text_layer_set_font(nameText_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  
  // This method has been commented out as the mobile-app is still in development-process
  //setupAppSyncWithInitialData();
  
  layer_add_child(window_layer, text_layer_get_layer(LogText_layer));
  
  // a method to setup app message API
  setupAppMessage(); 

}

static void deinit() {
  // Destroy Window
  text_layer_destroy(nameText_layer);
  text_layer_destroy(LogText_layer);
  window_destroy(window);
}


int main(void) {
  init();
  app_event_loop();
  deinit();
}
