#include <ruby.h>
#include <SDL.h>

typedef VALUE(*RubyAllocator)(VALUE);
typedef VALUE(*RubyMethod)(ANYARGS);

template<typename T>
struct Info
{
  T* info;

  static void free_info(void *p)
  {
    Info* ptr = (Info*)p;
    delete ptr->info;
    ptr->info = NULL;
  }

  static VALUE alloc_info(VALUE klass)
  {
    VALUE obj;
    Info* ptr;

    obj = Data_Make_Struct(klass, Info, NULL, free_info, ptr);

    return obj;
  }

  static VALUE init_info(VALUE self)
  {
    Info* ptr;

    Data_Get_Struct(self, Info, ptr);
    ptr->info = new T;

    return self;
  }

};

class NativeInfo
{
public:
  NativeInfo()
  {
    SDL_Init(SDL_INIT_EVERYTHING);
  }

  int version()
  {
    return SDL_COMPILEDVERSION;
  }

  ~NativeInfo()
  {
    SDL_Quit();
  }

  static VALUE rb_version(VALUE self)
  {
    Info<NativeInfo>* ptr;

    Data_Get_Struct(self, Info<NativeInfo>, ptr);
    return INT2NUM( ptr->info->version() );
  }
};

class WindowInfo
{
  bool running;
public:
  WindowInfo() : running(false)
  {
  }

  ~WindowInfo()
  {
  }

  void start()
  {
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_CreateWindowAndRenderer(800,
                                600,
                                SDL_WINDOW_RESIZABLE,
                                &window,
                                &renderer);

    running = true;
    SDL_Event event;
    while (running) {
      SDL_PollEvent(&event);
      if (event.type == SDL_QUIT) {
        running = false;
        break;
      }
      SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
      SDL_RenderClear(renderer);
      SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
  }

  static VALUE rb_start(VALUE self)
  {
    Info<WindowInfo>* ptr;

    Data_Get_Struct(self, Info<WindowInfo>, ptr);
    ptr->info->start();
    return self;
  }
};

template<typename TClass>
void bind_class(VALUE klass)
{
  rb_define_alloc_func(klass, (RubyAllocator)&Info<TClass>::alloc_info);
  rb_define_method(klass, "initialize", (RubyMethod)&Info<TClass>::init_info, 0);
}

extern "C"
void Init_native(void)
{
  VALUE mAlphatau;
  VALUE cNative;
  VALUE cWindow;

  mAlphatau = rb_define_module("Alphatau");
  cNative = rb_define_class_under(mAlphatau, "Native", rb_cObject);
  cWindow = rb_define_class_under(cNative, "Window", rb_cObject);

  bind_class<NativeInfo>(cNative);
  rb_define_method(cNative, "version", (RubyMethod)&NativeInfo::rb_version, 0);

  bind_class<WindowInfo>(cWindow);
  rb_define_method(cWindow, "start", (RubyMethod)&WindowInfo::rb_start, 0);
}
