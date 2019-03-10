#include "compiler_class.hpp"
#include "general_allocator_class.hpp"

#include <sstream>



#define ANY_JUST_ACCEPT_BASIC(arg) \
	arg->accept(this)

#define ANY_ACCEPT_IF_BASIC(arg) \
	if (arg) \
	{ \
		ANY_JUST_ACCEPT_BASIC(arg); \
	}

#define TOK_TO_DUPPED_STR(arg) \
	dup_str(arg->toString())

#define ANY_PUSH_TOK_IF(arg) \
	if (arg) \
	{ \
		_stacks.push_str(TOK_TO_DUPPED_STR(arg)); \
	}



namespace frost_hdl
{

typedef Compiler::VisitorRetType VisitorRetType;

Compiler::Compiler(Parser& parser)
{
	_program_ctx = parser.program();
}

int Compiler::run()
{
	// Temporary initialization of "Pass::FrostListModules".
	set_pass(Pass::FrostListModules);


	while (pass() < Pass::Done)
	{
		visitProgram(_program_ctx);
		set_pass(static_cast<Pass>(static_cast<PassUint>(pass())
			+ static_cast<PassUint>(1)));
	}

	return 0;
}


// Basically just "module" and "package" declarations.  There are no other
// things at global scope.
VisitorRetType Compiler::visitProgram(Parser::ProgramContext *ctx)
{

	if (in_frost_package_pass())
	{
		//for (auto subprogram : ctx->declPackage())
		//{
		//	ANY_JUST_ACCEPT_BASIC(subprogram);
		//}
	}
	else if (in_frost_module_pass())
	{
		for (auto subprogram : ctx->declModule())
		{
			ANY_JUST_ACCEPT_BASIC(subprogram);
		}
	}

	return nullptr;
}




// Variable declaration stuff
VisitorRetType Compiler::visitLhsTypeName
	(Parser::LhsTypeNameContext *ctx)
{
	return nullptr;
}


VisitorRetType Compiler::visitDeclNoLhsTypeVar
	(Parser::DeclNoLhsTypeVarContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitDeclVarList
	(Parser::DeclVarListContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitDeclPortVarList
	(Parser::DeclPortVarListContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitDeclPortInputVarList
	(Parser::DeclPortInputVarListContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitDeclPortOutputVarList
	(Parser::DeclPortOutputVarListContext *ctx)
{
	return nullptr;
}
VisitorRetType Compiler::visitDeclPortInoutVarList
	(Parser::DeclPortInoutVarListContext *ctx)
{
	return nullptr;
}


// "module" stuff
VisitorRetType Compiler::visitDeclModule(Parser::DeclModuleContext *ctx)
{
	if (pass() == Pass::FrostListModules)
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		auto ident_name = _stacks.pop_str();

		if (_frost_program.frost_module_table.contains(ident_name))
		{
			_err(ctx, sconcat("Duplicate module called \"", *ident_name,
				"\""));
		}

		_frost_program.curr_frost_module = save_frost_module(FrostModule
			(ident_name));

		// Process ports of this module
		for (auto port_list : ctx->declPortInputVarList())
		{
			ANY_JUST_ACCEPT_BASIC(port_list);
		}
		for (auto port_list : ctx->declPortOutputVarList())
		{
			ANY_JUST_ACCEPT_BASIC(port_list);
		}
		for (auto port_list : ctx->declPortInoutVarList())
		{
			ANY_JUST_ACCEPT_BASIC(port_list);
		}

		_frost_program.frost_module_table.insert_or_assign
			(_frost_program.curr_frost_module);
	}
	else if (pass() == Pass::FrostExpandModules)
	{
		//ANY_JUST_ACCEPT_BASIC(ctx->identName());
		//auto ident_name = _stacks.pop_str();
	}
	else
	{
		_err(ctx, "Compiler::visitDeclModule():  Eek!");
	}


	return nullptr;
}

VisitorRetType Compiler::visitModuleInsides
	(Parser::ModuleInsidesContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitModuleStmtAssign
	(Parser::ModuleStmtAssignContext *ctx)
{
	return nullptr;
}

// Expression parsing
VisitorRetType Compiler::visitExpr
	(Parser::ExprContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitExprLogical
	(Parser::ExprLogicalContext *ctx)
{
	return nullptr;
}
VisitorRetType Compiler::visitExprCompare
	(Parser::ExprCompareContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitExprAddSub
	(Parser::ExprAddSubContext *ctx)
{
	return nullptr;
}
VisitorRetType Compiler::visitExprMulDivModEtc
	(Parser::ExprMulDivModEtcContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitExprUnary
	(Parser::ExprUnaryContext *ctx)
{
	return nullptr;
}


VisitorRetType Compiler::visitExprBitInvert
	(Parser::ExprBitInvertContext *ctx)
{
	return nullptr;
}
VisitorRetType Compiler::visitExprNegate
	(Parser::ExprNegateContext *ctx)
{
	return nullptr;
}
VisitorRetType Compiler::visitExprLogNot
	(Parser::ExprLogNotContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitNumExpr
	(Parser::NumExprContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitRawNumExpr
	(Parser::RawNumExprContext *ctx)
{
	ANY_PUSH_TOK_IF(ctx->TokDecNum())
	else ANY_PUSH_TOK_IF(ctx->TokHexNum())
	else ANY_PUSH_TOK_IF(ctx->TokBinNum())
	else
	{
		//err
	}

	return nullptr;
}
VisitorRetType Compiler::visitSizedNumExpr
	(Parser::SizedNumExprContext *ctx)
{
	ANY_JUST_ACCEPT_BASIC(ctx->rawNumExpr());
	return nullptr;
}

VisitorRetType Compiler::visitIdentExpr
	(Parser::IdentExprContext *ctx)
{
	return nullptr;
}


VisitorRetType Compiler::visitIdentName
	(Parser::IdentNameContext *ctx)
{
	_stacks.push_str(TOK_TO_DUPPED_STR(ctx->TokIdent()));

	return nullptr;
}

// For now, only support sliced identifiers.
VisitorRetType Compiler::visitIdentSliced
	(Parser::IdentSlicedContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitIdentConcatExpr
	(Parser::IdentConcatExprContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitListIdentExpr
	(Parser::ListIdentExprContext *ctx)
{
	return nullptr;
}



VisitorRetType Compiler::visitSlice
	(Parser::SliceContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitInnerSliceOne
	(Parser::InnerSliceOneContext *ctx)
{
	return nullptr;
}

VisitorRetType Compiler::visitInnerSliceTwo
	(Parser::InnerSliceTwoContext *ctx)
{
	return nullptr;
}


} // namespace frost_hdl
