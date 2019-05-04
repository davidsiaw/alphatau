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

  int haha(int a)
  {
    return a + 5;
  }

  ~NativeInfo()
  {
    SDL_Quit();
  }

  static VALUE rb_haha(VALUE self, VALUE a)
  {
    Info<NativeInfo>* ptr;

    Data_Get_Struct(self, Info<NativeInfo>, ptr);
    return INT2NUM( ptr->info->haha(NUM2INT(a)) );
  }
};

class WindowInfo
{
  SDL_Window* window;
  SDL_Renderer* renderer;
public:
  WindowInfo()
  {
    SDL_CreateWindowAndRenderer(800,
                                600,
                                SDL_WINDOW_RESIZABLE,
                                &window,
                                &renderer);
  }

  ~WindowInfo()
  {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
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
  rb_define_method(cNative, "haha", (RubyMethod)&NativeInfo::rb_haha, 1);

  bind_class<WindowInfo>(cWindow);

}
