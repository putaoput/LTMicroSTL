//@Author: Lin Tao
//@Email: putaopu@qq.com

#pragma once
//该头文件负责提供基本数据结构:红黑树。以模板的形式定义

#include <initializer_list>
#include <cassert>

#include "functional.h"
#include "iterator.h"
#include "memory.h"
#include "type_traits.h"

namespace LT 
{
	typedef bool rb_color_type;
	static constexpr rb_color_type red_node = false;
	static constexpr rb_color_type black_node = true;



};
