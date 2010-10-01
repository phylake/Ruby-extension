#include "ruby.h"
#include "intern.h"
#include <math.h>

static VALUE m_transform(VALUE self, VALUE matrix, VALUE coords) {
	if( TYPE(matrix) == T_ARRAY &&//argument is array
		RARRAY_LEN(matrix) == 2 &&//at least 2 columns
		TYPE(rb_ary_entry(matrix, 0)) == T_ARRAY &&//first element is array
		TYPE(rb_ary_entry(matrix, 1)) == T_ARRAY &&//second element is array
		RARRAY_LEN(rb_ary_entry(matrix, 0)) == 2 &&//elements are proper size
		RARRAY_LEN(rb_ary_entry(matrix, 1)) == 2 )//have a 2x2 matrix
	{
		VALUE c0 = rb_ary_entry(matrix, 0);
		VALUE c1 = rb_ary_entry(matrix, 0);
		int c0r0 = NUM2INT(rb_ary_entry(c0, 0));
		int c0r1 = NUM2INT(rb_ary_entry(c0, 1));
		int c1r0 = NUM2INT(rb_ary_entry(c1, 0));
		int c1r1 = NUM2INT(rb_ary_entry(c1, 1));
		int x = NUM2INT(rb_ary_entry(coords, 0));
		int y = NUM2INT(rb_ary_entry(coords, 1));
		
		VALUE t_coords = rb_ary_new();
		VALUE t_x = rb_float_new( x*c0r0 + y*c1r0 );
		VALUE t_y = rb_float_new( x*c0r1 + y*c1r1 );
		rb_ary_push(t_coords, t_x);
		rb_ary_push(t_coords, t_y);
		return t_coords;
	}

	return INT2NUM(-1);
}

static VALUE m_rotate(VALUE self, VALUE coords, VALUE theta_val) {
	if( TYPE(coords) == T_ARRAY && RARRAY_LEN(coords) == 2 )
	{
		int x = NUM2INT(rb_ary_entry(coords, 0));
		int y = NUM2INT(rb_ary_entry(coords, 1));
		int theta = NUM2INT(theta_val);
		
		VALUE t_coords = rb_ary_new();
		VALUE t_x = rb_float_new( x*cos(theta) + y*sin(theta) );
		VALUE t_y = rb_float_new( -x*sin(theta) + y*cos(theta) );
		
		rb_ary_push(t_coords, t_x);
		rb_ary_push(t_coords, t_y);
		
		return t_coords;
	}

	return INT2NUM(-1);
}

void Init_matrices() {
	VALUE matrixMod = rb_define_module("Matrices");
	rb_define_module_function(matrixMod, "rotate", m_rotate, 2);
	rb_define_module_function(matrixMod, "transform", m_transform, 3);
}