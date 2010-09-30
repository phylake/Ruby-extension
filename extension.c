#include "ruby.h"
#include "intern.h"
#include <math.h>

static VALUE m_rotate(VALUE self, VALUE coords, VALUE theta) {
	if( TYPE(coords) == T_ARRAY &&
		RARRAY_LEN(coords) == 2 )
	{
		int x = NUM2INT(rb_ary_entry(coords, 0));
		int y = NUM2INT(rb_ary_entry(coords, 1));
		int angle = NUM2INT(theta);
		
		VALUE t_coords = rb_ary_new();
		VALUE t_y = rb_float_new( x*cos(angle) + y*sin(angle) );
		VALUE t_x = rb_float_new( -x*sin(angle) + y*cos(angle) );
		
		rb_ary_push(t_coords, t_y);
		rb_ary_push(t_coords, t_x);
		
		return t_coords;
	}

	return INT2NUM(-1);
}

void Init_matrices() {
	VALUE matrixMod = rb_define_module("Matrices");
	rb_define_module_function(matrixMod, "rotate", m_rotate, 2);
}