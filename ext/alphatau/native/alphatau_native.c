#include <ruby.h>
#include <SDL.h>

typedef struct _native_info
{
  size_t size;
  void *ptr;
} NativeInfo;

static void free_native_info(void *p)
{
  NativeInfo *ptr = p;

  if (ptr->size > 0)
  {
    free(ptr->ptr);
  }

  if (SDL_WasInit(SDL_INIT_EVERYTHING))
  {
    SDL_Quit();
  }
}

static VALUE alloc_native_info(VALUE klass)
{
  VALUE obj;
  NativeInfo *ptr;

  obj = Data_Make_Struct(klass, NativeInfo, NULL, free_native_info, ptr);

  ptr->size = 0;
  ptr->ptr  = NULL;

  return obj;
}

static VALUE init_native_info(VALUE self)
{
  NativeInfo *ptr;

  Data_Get_Struct(self, NativeInfo, ptr);

  SDL_Init(SDL_INIT_EVERYTHING);

  return self;
}

void Init_native(void)
{
  VALUE mAlphatau;
  VALUE cNative;

  mAlphatau = rb_define_module("Alphatau");
  cNative = rb_define_class_under(mAlphatau, "Native", rb_cObject);

  rb_define_alloc_func(cNative, alloc_native_info);
  rb_define_method(cNative, "initialize", init_native_info, 0);
}
