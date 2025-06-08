/**
    -----------------------------------------------------------

 	easyVGL
 	simple-demo.c    2025/6/2   
 	
 	@link    : https://github.com/shezw/tinygui
 	@author	 : shezw
 	@email	 : hello@shezw.com

    -----------------------------------------------------------
*/

static void ui_thread(){

    static u32 ms = 0;

    if(ms++%2000!=0)
        return;

    static bool b = false;

    if (b)
        getApp()->historyManager->replace(PageCustomHomeMenu,NULL);
    else
        getApp()->historyManager->replace(PageHome,NULL);

    b = b ? false : true;

}

int main(int argc, char *argv[])
{

    // init the lvgl library
    lv_init();

    // init the platform layer
    porting_init( "/dev/fb0", "/dev/input/event0" );

    // init the app
    evg_app_init(argc, argv);

#if PLATFORM_WASM
    emscripten_set_main_loop_arg(evg_porting_loop_wasm, NULL, -1, true);
#else
    evg_porting_loop_ns(5000);
#endif

    return 0;
}