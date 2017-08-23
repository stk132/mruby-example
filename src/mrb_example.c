/*
** mrb_example.c - Example class
**
** Copyright (c) Takuya Shimabukuro 2017
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mrb_example.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  char *str;
  int len;
} mrb_example_data;

static const struct mrb_data_type mrb_example_data_type = {
  "mrb_example_data", mrb_free,
};

static mrb_value mrb_example_init(mrb_state *mrb, mrb_value self)
{
  mrb_example_data *data;
  char *str;
  int len;

  data = (mrb_example_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_example_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "s", &str, &len);
  data = (mrb_example_data *)mrb_malloc(mrb, sizeof(mrb_example_data));
  data->str = str;
  data->len = len;
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_example_hello(mrb_state *mrb, mrb_value self)
{
  mrb_example_data *data = DATA_PTR(self);

  return mrb_str_new(mrb, data->str, data->len);
}

static mrb_value mrb_example_hi(mrb_state *mrb, mrb_value self)
{
  return mrb_str_new_cstr(mrb, "hi!!");
}

void mrb_mruby_example_gem_init(mrb_state *mrb)
{
  struct RClass *example;
  example = mrb_define_class(mrb, "Example", mrb->object_class);
  mrb_define_method(mrb, example, "initialize", mrb_example_init, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, example, "hello", mrb_example_hello, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, example, "hi", mrb_example_hi, MRB_ARGS_NONE());
  DONE;
}

void mrb_mruby_example_gem_final(mrb_state *mrb)
{
}

