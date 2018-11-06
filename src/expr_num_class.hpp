#ifndef src_expr_num_class_hpp
#define src_expr_num_class_hpp

// src/expr_num_class.hpp

#include "misc_includes.hpp"

namespace frost_hdl
{

class ExprNum
{
private:		// variables
	size_t ___size = 0;
	BigNum* ___val = nullptr;

public:		// functions
	inline ExprNum()
	{
	}

	inline ExprNum(size_t s_size, BigNum* s_val)
		: ___size(s_size), ___val(s_val)
	{
	}

	inline ExprNum(const ExprNum& to_copy) = default;
	//inline ExprNum(ExprNum&& to_move) = default;

	inline ExprNum& operator = (const ExprNum& to_copy) = default;
	//inline ExprNum& operator = (ExprNum&& to_move) = default;

	inline bool operator < (const ExprNum& to_cmp) const
	{
		if (size() < to_cmp.size())
		{
			return true;
		}
		else if (size() == to_cmp.size())
		{
			return (val() < to_cmp.val());
		}
		else // if (size() > to_cmp.size())
		{
			return false;
		}
	}

	inline bool is_constant() const
	{
		return (val() != nullptr);
	}

	gen_getter_and_setter_by_val(size);
	gen_getter_and_setter_by_val(val)
};

} // namespace frost_hdl




#endif		// src_expr_num_class_hpp
