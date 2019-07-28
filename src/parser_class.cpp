#include "parser_class.hpp"

namespace frost_hdl
{
using namespace ast;

Parser::Parser(vector<string>&& s_filename_vec)
	: ParserBase<Lexer>(std::move(s_filename_vec))
{
	_ast_root.reset(new NodeProgram(SrcCodeChunk()));
}
Parser::~Parser()
{
}

#define fp(func) &Parser::_parse_##func
#define named_fp(func) #func, fp(func)
#define rseqp(func) _req_seq_parse(_unit_parse(named_fp(func), false))
#define oseqp(func) _opt_seq_parse(_unit_parse(named_fp(func), false))
#define make_msp MapSeqParse map_seq_parse
#define msp(func) map_seq_parse[#func]
#define set_msp_r(func) msp(func) = rseqp(func)
#define set_msp_o(func) msp(func) = oseqp(func)

#define check_parse_named(seq, some_req_seq_parse) \
	const auto seq = some_req_seq_parse; \
	if (actual_just_test()) \
	{ \
		return _check_for_just_test(seq); \
	}

#define check_parse_anon(some_req_seq_parse) \
	if (actual_just_test()) \
	{ \
		return _check_for_just_test(some_req_seq_parse); \
	}

#define simple_seq_parse_named(seq, some_req_seq_parse) \
	check_parse_named(seq, some_req_seq_parse) \
	/* const auto first_invalid = seq.first_invalid(); */ \
	/* if (!std::holds_alternative<bool>(first_invalid.one_inst)) */ \
	/* { */ \
	/* 	_unexpected(*first_invalid.parse_ret); */ \
	/* } */ \
	seq.exec(); \

#define simple_seq_parse_anon(some_req_seq_parse) \
	check_parse_anon(some_req_seq_parse) \
	/* const auto first_invalid = some_req_seq_parse.first_invalid(); */ \
	/* if (!std::holds_alternative<bool>(first_invalid.one_inst)) */ \
	/* { */ \
	/* 	_unexpected(*first_invalid.parse_ret); */ \
	/* } */ \
	some_req_seq_parse.exec(); \

#define simple_seq_parse_if_jp_anon(some_req_seq_parse) \
	check_parse_anon(some_req_seq_parse) \
	if (just_parse()) \
	{ \
		some_req_seq_parse.exec(); \
	}
#define simple_seq_parse_if_jp_named(seq, some_req_seq_parse) \
	check_parse_named(seq, some_req_seq_parse) \
	if (just_parse()) \
	{ \
		seq.exec(); \
	}

//using FuncVec = vector<decltype(fp(parse_program))>;
using std::move;
using Child = ast::NodeBase::Child;

auto Parser::parse_program() -> ParseRet
{
	//const FuncVec func_vec({fp(_parse_package), fp(_parse_module)});

	//while (_opt_parse(this, func_vec))
	//{
	//	_ast_root->append(move(_pop_ast_child()));
	//}

	//check_parse_named(seq, _opt_or_parse(rseqp(package),
	//	rseqp(module)));
	TheSeqParse::debug = true;
	TheSeqParse::debug_tok_ident_map = &tok_ident_map;

	auto ret = _dup_lex_state();

	const auto seq = _opt_or_parse(rseqp(package), rseqp(module));

	if (!seq.check())
	{
		_ls_src_code_chunk(ret).err("Invalid program.");
	}
	while (seq.check())
	{
		seq.exec();
		_ast_root->append(_pop_ast_child());
	}

	return ret;
}

#define CHECK_PREFIXED_ONE_TOK(one_tok) \
	if (actual_just_test()) \
	{ \
		if (_check_prefixed_tok_seq(one_tok)) \
		{ \
			return _dup_lex_state(); \
		} \
		else \
		{ \
			return ParseRet(nullptr); \
		} \
	} \
	auto ret = _dup_lex_state(); \
	_expect(one_tok); \
	return ret

auto Parser::_parse_kw_if() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwIf);
}
auto Parser::_parse_kw_else() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwElse);
}
auto Parser::_parse_kw_for() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwFor);
}
auto Parser::_parse_kw_generate() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwGenerate);
}
auto Parser::_parse_kw_package() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPackage);
}
auto Parser::_parse_kw_port() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPort);
}
auto Parser::_parse_kw_proc() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwProc);
}
auto Parser::_parse_kw_func() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwFunc);
}
auto Parser::_parse_kw_task() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwTask);
}
auto Parser::_parse_kw_module() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwModule);
}
auto Parser::_parse_kw_const() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwConst);
}
auto Parser::_parse_kw_range() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwRange);
}
auto Parser::_parse_kw_cat() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwCat);
}
auto Parser::_parse_kw_repl() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwRepl);
}
auto Parser::_parse_kw_using() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUsing);
}
auto Parser::_parse_kw_while() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwWhile);
}
auto Parser::_parse_kw_switch() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSwitch);
}
auto Parser::_parse_kw_switchz() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSwitchz);
}
auto Parser::_parse_kw_case() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwCase);
}
auto Parser::_parse_kw_default() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwDefault);
}
auto Parser::_parse_kw_return() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwReturn);
}
auto Parser::_parse_kw_packed() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPacked);
}
auto Parser::_parse_kw_class() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwClass);
}
auto Parser::_parse_kw_virtual() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwVirtual);
}
auto Parser::_parse_kw_extends() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwExtends);
}
auto Parser::_parse_kw_public() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPublic);
}
auto Parser::_parse_kw_protected() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwProtected);
}
auto Parser::_parse_kw_private() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPrivate);
}
auto Parser::_parse_kw_enum() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwEnum);
}
auto Parser::_parse_kw_union() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUnion);
}
auto Parser::_parse_kw_assign() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAssign);
}
auto Parser::_parse_kw_initial() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwInitial);
}
auto Parser::_parse_kw_always_comb() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAlwaysComb);
}
auto Parser::_parse_kw_always_blk() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAlwaysBlk);
}
auto Parser::_parse_kw_always_ff() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAlwaysFf);
}
auto Parser::_parse_kw_posedge() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwPosedge);
}
auto Parser::_parse_kw_negedge() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwNegedge);
}
auto Parser::_parse_kw_inst() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwInst);
}
auto Parser::_parse_kw_input() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwInput);
}
auto Parser::_parse_kw_output() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwOutput);
}
auto Parser::_parse_kw_bidir() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwBidir);
}
auto Parser::_parse_kw_type() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwType);
}
auto Parser::_parse_kw_uwire() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUwire);
}
auto Parser::_parse_kw_swire() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSwire);
}
auto Parser::_parse_kw_ubit() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUbit);
}
auto Parser::_parse_kw_sbit() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSbit);
}
auto Parser::_parse_kw_void() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwVoid);
}
auto Parser::_parse_kw_auto() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwAuto);
}
auto Parser::_parse_kw_ubyte() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUbyte);
}
auto Parser::_parse_kw_sbyte() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSbyte);
}
auto Parser::_parse_kw_ushortint() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUshortint);
}
auto Parser::_parse_kw_sshortint() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSshortint);
}
auto Parser::_parse_kw_uint() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUint);
}
auto Parser::_parse_kw_sint() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSint);
}
auto Parser::_parse_kw_ulongint() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwUlongint);
}
auto Parser::_parse_kw_slongint() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwSlongint);
}
auto Parser::_parse_kw_typeof() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::KwTypeof);
}

auto Parser::_parse_punct_lparen() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::LParen);
}
auto Parser::_parse_punct_rparen() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::RParen);
}
auto Parser::_parse_punct_lbracket() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::LBracket);
}
auto Parser::_parse_punct_rbracket() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::RBracket);
}
auto Parser::_parse_punct_lbrace() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::LBrace);
}
auto Parser::_parse_punct_rbrace() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::RBrace);
}
auto Parser::_parse_punct_comma() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::Comma);
}
auto Parser::_parse_punct_semicolon() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::Semicolon);
}
auto Parser::_parse_punct_colon() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::Colon);
}
auto Parser::_parse_punct_apostrophe() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::Apostrophe);
}
auto Parser::_parse_punct_assign() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::Assign);
}
auto Parser::_parse_punct_member_access() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::MemberAccess);
}
auto Parser::_parse_punct_scope_access() -> ParseRet
{
	CHECK_PREFIXED_ONE_TOK(Tok::ScopeAccess);
}
auto Parser::_parse_header_if() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_seq_parse(rseqp(kw_if), rseqp(punct_lparen),
		rseqp(expr), rseqp(punct_rparen)))
	return ret;
}
auto Parser::_parse_header_else_if() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_seq_parse(rseqp(kw_else), rseqp(header_if)))
	return ret;
}
auto Parser::_parse_header_else() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(rseqp(kw_else))
	return ret;
}
auto Parser::_parse_header_for() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_seq_parse(rseqp(kw_for),
		rseqp(punct_lparen), rseqp(ident), rseqp(punct_colon),
		_req_or_parse(rseqp(expr), rseqp(type_range)),
		rseqp(punct_rparen)))
	return ret;
}

auto Parser::_parse_header_generate_if() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_seq_parse(rseqp(kw_generate),
		rseqp(header_if)))
	return ret;
}
auto Parser::_parse_header_else_generate_if() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_seq_parse(rseqp(kw_else),
		rseqp(header_generate_if)))
	return ret;
}
auto Parser::_parse_header_else_generate() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_seq_parse(rseqp(kw_else),
		rseqp(kw_generate)))
	return ret;
}
auto Parser::_parse_header_generate_for() -> ParseRet
{
	auto ret = _dup_lex_state();
	make_msp;
	set_msp_r(kw_generate);
	set_msp_o(ident);
	set_msp_r(header_for);

	simple_seq_parse_if_jp_named(seq, _req_seq_parse(msp(kw_generate),
		msp(ident), msp(header_for)))
	else
	{
		msp(kw_generate).exec();
		_push_num(_one_opt_parse(msp(ident)));
		msp(header_for).exec();
	}

	return ret;
}

auto Parser::_parse_package() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_seq_parse(rseqp(kw_package), rseqp(ident),
		rseqp(scope_package)))

	if (!just_parse())
	{
		auto scope_package = _pop_ast_child();
		auto ident = _pop_ast_child();
		_push_ast_child(NodePackage(_ls_src_code_chunk(ret),
			move(ident), move(scope_package)));
	}
	return ret;
}
auto Parser::_parse_scope_package() -> ParseRet
{
	return _parse_any_scope<NodeScopePackage>("scope_package",
		_req_list_parse(_req_or_parse(rseqp(generate_package),
		rseqp(package), rseqp(module), rseqp(const), rseqp(using),
		rseqp(decl_callable), rseqp(decl_cstm_type))));
}

auto Parser::_parse_generate_package() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_or_parse(rseqp(generate_package_if),
		rseqp(generate_package_for)))
	return ret;
}
auto Parser::_parse_generate_package_if() -> ParseRet
{
	return _parse_generate_any_if(named_fp(generate_package_if));
}
auto Parser::_parse_generate_package_for() -> ParseRet
{
	return _parse_generate_any_for(named_fp(generate_package_for));
}

auto Parser::_parse_member_callable_prefix() -> ParseRet
{
	auto ret = _dup_lex_state();

	const auto vec = _next_n_tokens(3, false);
	bool is_const = false;
	bool is_virtual = false;
	bool is_static = false;

	bool found = true;
	for (const auto& iter : vec)
	{
		switch (iter.tok())
		{
		case Tok::KwConst:
			is_const = true;
			break;
		case Tok::KwVirtual:
			is_virtual = true;
			break;
		case Tok::KwStatic:
			is_static = true;
			break;
		default:
			found = false;
			break;
		}

		if (!found)
		{
			break;
		}
	}
	if (actual_just_test())
	{
		if (is_const || is_virtual || is_static)
		{
			return ret;
		}
		else
		{
			return ParseRet(nullptr);
		}
	}

	size_t to_push = 0;
	if (is_const)
	{
		_next_n_tokens(1, true);
		++to_push;

		if (!just_parse())
		{
			_push_str("is_const");
		}
	}
	if (is_virtual)
	{
		_next_n_tokens(1, true);
		++to_push;

		if (!just_parse())
		{
			_push_str("is_virtual");
		}
	}
	if (is_static)
	{
		_next_n_tokens(1, true);
		++to_push;

		if (!just_parse())
		{
			_push_str("is_static");
		}
	}

	if (!just_parse())
	{
		_push_num(to_push);
	}

	return ret;
}

auto Parser::_parse_contents_modproc() -> ParseRet
{
	auto ret = _dup_lex_state();
	make_msp;
	set_msp_o(param_list);
	set_msp_r(arg_list);
	set_msp_r(scope_modproc);

	simple_seq_parse_if_jp_named(seq, _req_seq_parse(msp(param_list),
		msp(arg_list), msp(scope_modproc)))
	else
	{
		_push_one_opt_parse(msp(param_list));
		msp(arg_list).exec();
		msp(scope_modproc).exec();
	}

	return ret;
}
auto Parser::_parse_proc() -> ParseRet
{
	auto ret = _dup_lex_state();

	make_msp;
	set_msp_r(kw_proc);
	msp(type) = _req_or_parse(rseqp(ident), rseqp(kw_port),
		rseqp(const_str));
	set_msp_r(contents_modproc);

	simple_seq_parse_if_jp_anon(_req_seq_parse(msp(kw_proc), msp(type),
		msp(contents_modproc)))
	else
	{
		msp(kw_proc).exec();

		const auto parse_func_str = msp(type).first_valid_parse_func_str();
		msp(type).exec();

		Child s_ident_or_op;
		bool s_is_port = false;
		if ((parse_func_str == "ident") || (parse_func_str == "const_str"))
		{
			s_ident_or_op = _pop_ast_child();
		}
		else // if (parse_func_str == "kw_port")
		{
			s_is_port = true;
		}

		msp(contents_modproc).exec();
		auto s_scope = _pop_ast_child();
		auto s_arg_list = _pop_ast_child();
		auto s_param_list = _get_ast_child_if_pop_num();

		_push_ast_child(NodeDeclProc(_ls_src_code_chunk(ret), s_is_port,
			move(s_param_list), move(s_arg_list), move(s_ident_or_op),
			move(s_scope)));
	}
	return ret;
}
auto Parser::_parse_module() -> ParseRet
{
	auto ret = _dup_lex_state();

	//make_msp;
	//set_msp_r(kw_module);
	//set_msp_r(ident);
	//set_msp_r(contents_modproc);
	simple_seq_parse_anon(_req_seq_parse(rseqp(kw_module), rseqp(ident),
		rseqp(contents_modproc)))

	if (!just_parse())
	{
		auto s_scope = _pop_ast_child();
		auto s_arg_list = _pop_ast_child();
		auto s_param_list = _get_ast_child_if_pop_num();
		auto s_ident = _pop_ast_child();
		_push_ast_child(NodeModule(_ls_src_code_chunk(ret), move(s_ident),
			move(s_param_list), move(s_arg_list), move(s_scope)));
	}

	return ret;
}

auto Parser::_parse_scope_modproc() -> ParseRet
{
	return _parse_any_scope<NodeScopeModproc>("scope_modproc",
		_req_list_parse(_req_or_parse(rseqp(generate_modproc),
		rseqp(module), rseqp(const), rseqp(var), rseqp(using),
		rseqp(decl_callable), rseqp(decl_cstm_type),
		rseqp(hardware_block))));
}
auto Parser::_parse_generate_modproc() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_or_parse(rseqp(generate_modproc_if),
		rseqp(generate_modproc_for)))
	return ret;
}
auto Parser::_parse_generate_modproc_if() -> ParseRet
{
	return _parse_generate_any_if(named_fp(generate_modproc_if));
}
auto Parser::_parse_generate_modproc_for() -> ParseRet
{
	return _parse_generate_any_for(named_fp(generate_modproc_for));
}

auto Parser::_parse_decl_callable() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_or_parse(rseqp(func), rseqp(task),
		rseqp(proc)))
	return ret;
}
auto Parser::_parse_contents_func_task() -> ParseRet
{
	auto ret = _dup_lex_state();
	make_msp;
	set_msp_o(param_list);
	set_msp_r(arg_list);
	set_msp_r(scope_behav);
	simple_seq_parse_if_jp_anon(_req_seq_parse(msp(param_list),
		msp(arg_list), msp(scope_behav)))
	else
	{
		_push_one_opt_parse(msp(param_list));
		msp(arg_list).exec();
		msp(scope_behav).exec();
	}

	return ret;
}
auto Parser::_parse_func() -> ParseRet
{
	auto ret = _dup_lex_state();
	make_msp;
	set_msp_r(kw_func);
	set_msp_r(typename);
	msp(ident_or_op) = _req_or_parse(rseqp(ident), rseqp(const_str));
	set_msp_r(contents_func_task);

	simple_seq_parse_if_jp_anon(_req_seq_parse(msp(kw_func), msp(typename),
		msp(ident_or_op), msp(contents_func_task)))
	else
	{
		msp(kw_func).exec();
		auto s_the_typename = _pexec(msp(typename));
		auto s_ident_or_op = _pexec(msp(ident_or_op));

		msp(contents_func_task).exec();
		auto s_scope = _pop_ast_child();
		auto s_arg_list = _pop_ast_child();
		auto s_param_list = _get_ast_child_if_pop_num();
		_push_ast_child(NodeDeclFunc(_ls_src_code_chunk(ret),
			move(s_the_typename), move(s_param_list), move(s_arg_list),
			move(s_ident_or_op), move(s_scope)));
	}

	return ret;
}
auto Parser::_parse_task() -> ParseRet
{
	auto ret = _dup_lex_state();
	make_msp;
	set_msp_r(kw_task);
	msp(ident_or_op) = _req_or_parse(rseqp(ident), rseqp(const_str));
	set_msp_r(contents_func_task);

	simple_seq_parse_if_jp_anon(_req_seq_parse(msp(kw_task),
		msp(ident_or_op), msp(contents_func_task)))
	else
	{
		msp(kw_task).exec();
		auto s_ident_or_op = _pexec(msp(ident_or_op));

		msp(contents_func_task).exec();
		auto s_scope = _pop_ast_child();
		auto s_arg_list = _pop_ast_child();
		auto s_param_list = _get_ast_child_if_pop_num();
		_push_ast_child(NodeDeclTask(_ls_src_code_chunk(ret),
			move(s_param_list), move(s_arg_list), move(s_ident_or_op),
			move(s_scope)));
	}

	return ret;
}

auto Parser::_parse_scope_behav() -> ParseRet
{
	return _parse_any_scope<NodeScopeBehav>("scope_behav",
		_req_list_parse(rseqp(inner_scope_behav)));
}
auto Parser::_parse_inner_scope_behav() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_or_parse(rseqp(generate_behav),
		rseqp(const), rseqp(var), rseqp(using), rseqp(stmt_assign),
		rseqp(stmt_if), rseqp(stmt_for), rseqp(stmt_while),
		rseqp(stmt_switch), rseqp(stmt_switchz), rseqp(stmt_return),
		rseqp(ident_etc), rseqp(decl_cstm_type), rseqp(scope_behav)))
	return ret;
}

auto Parser::_parse_generate_behav() -> ParseRet
{
	auto ret = _dup_lex_state();
	simple_seq_parse_anon(_req_or_parse(rseqp(generate_behav_if),
		rseqp(generate_behav_for)))
	return ret;
}
auto Parser::_parse_generate_behav_if() -> ParseRet
{
	return _parse_generate_any_if(named_fp(generate_behav_if));
}
auto Parser::_parse_generate_behav_for() -> ParseRet
{
	return _parse_generate_any_for(named_fp(generate_behav_for));
}

auto Parser::_parse_const() -> ParseRet
{
	auto ret = _dup_lex_state();
	make_msp;
	set_msp_r(kw_const);
	set_msp_o(typename);
	set_msp_r(one_const);
	msp(list_one_const) = _opt_list_parse(rseqp(punct_comma),
		rseqp(one_const));
	set_msp_r(punct_semicolon);
	simple_seq_parse_if_jp_anon(_req_seq_parse(msp(kw_const),
		msp(typename), msp(one_const), msp(list_one_const),
		msp(punct_semicolon)))
	else
	{
		msp(kw_const).exec();
		auto s_the_typename = _get_one_opt_parse(msp(typename));

		NodeIdentTermEqualsExtraList s_ident_term_equals_extra_list
			(_ls_src_code_chunk(_dup_lex_state()));
		s_ident_term_equals_extra_list.append(_pexec(msp(one_const)));
		_list_pexec(s_ident_term_equals_extra_list, msp(list_one_const));

		msp(punct_semicolon).exec();
		_push_ast_child(NodeDeclConstList(_ls_src_code_chunk(ret),
			move(s_the_typename),
			_to_ast_child(move(s_ident_term_equals_extra_list))));
	}

	return ret;
}
auto Parser::_parse_one_const() -> ParseRet
{
	auto ret = _dup_lex_state();
	make_msp;

	return ret;
}
auto Parser::_parse_var() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_one_var() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_using() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

auto Parser::_parse_stmt_assign() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_stmt_if() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_stmt_for() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_stmt_while() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_stmt_switch() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_stmt_switchz() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_scope_switch() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_stmt_case() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_stmt_default() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_stmt_return() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

auto Parser::_parse_decl_cstm_type() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_class() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_extends() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

auto Parser::_parse_scope_class() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_member_callable() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_generate_class() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_generate_class_if() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_generate_class_for() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_member_access_label() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

auto Parser::_parse_enum() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_union() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

auto Parser::_parse_hardware_block() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_cont_assign() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_initial() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_always_comb() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_always_blk() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_always_ff() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_edge_list() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_posedge_inst() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_negedge_inst() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

auto Parser::_parse_inst() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

auto Parser::_parse_param_list() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_param_sublist() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_arg_list() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_arg_sublist() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_arg_port_sublist() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_pararg_var_sublist() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_pararg_type_sublist() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_param_module_sublist() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_pararg_ident_equals_typename_sublist() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_param_inst_list() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_arg_inst_list() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

auto Parser::_parse_pos_pararg_inst_list() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_named_pararg_inst_list() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

auto Parser::_parse_typename() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_param_possible_typename() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_no_param_possible_typename() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_typeof() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_type_range() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_range_suffix() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

auto Parser::_parse_expr() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_inner_expr() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_op_logical() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

auto Parser::_parse_expr_logical() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_inner_expr_logical() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_op_compare() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

auto Parser::_parse_expr_compare() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_inner_expr_compare() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_op_plus_minus() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

auto Parser::_parse_expr_add_sub() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_inner_expr_add_sub() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_op_mul_div_mod_etc() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

auto Parser::_parse_expr_mul_div_mod_etc() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_inner_expr_mul_div_mod_etc() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_op_unary() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

auto Parser::_parse_dollar_global_clock() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_dollar_pow_expr() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_num_expr() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_raw_num() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_const_str() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

auto Parser::_parse_expr_pre_dollar_func_of_one() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_expr_post_dollar_func_of_one() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_dollar_func_of_one() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_expr_cat() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_expr_repl() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

auto Parser::_parse_ident_etc() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_ident_member_access() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_ident_scope_access() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_ident_non_member_scope_access() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_ident_call() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_ident_no_param_overloaded_call() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_ident_param_member_overloaded_call() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_ident_terminal() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_ident() -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}
auto Parser::_parse_generate_any_if(const string& parse_scope_func_str,
	ParseFunc parse_scope_func) -> ParseRet
{
	auto ret = _dup_lex_state();
	return ret;
}
auto Parser::_parse_generate_any_for(const string& parse_scope_func_str,
	ParseFunc parse_scope_func) -> ParseRet
{
	auto ret = _dup_lex_state();

	return ret;
}

template<typename AstNodeScopeType>
auto Parser::_parse_any_scope(const string& scope_type_str,
	const TheSeqParse& list_seq) -> ParseRet
{
	auto ret = _dup_lex_state();
	return ret;
}

void Parser::_finish_parse_expr_any_dollar_func_of_one
	(const SrcCodeChunk& s_src_code_chunk)
{
	auto s_expr = _pop_ast_child();

	switch (_pop_tok())
	{
	case Tok::KwDollarUnsgn:
		_push_ast_child(NodeExprUnopDollarUnsgn(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarSgn:
		_push_ast_child(NodeExprUnopDollarSgn(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarIsUnsgn:
		_push_ast_child(NodeExprUnopDollarIsUnsgn(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarIsSgn:
		_push_ast_child(NodeExprUnopDollarIsSgn(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarRange:
		_push_ast_child(NodeExprUnopDollarRange(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarSize:
		_push_ast_child(NodeExprUnopDollarSize(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarFirst:
		_push_ast_child(NodeExprUnopDollarFirst(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarLast:
		_push_ast_child(NodeExprUnopDollarLast(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarHigh:
		_push_ast_child(NodeExprUnopDollarHigh(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarLow:
		_push_ast_child(NodeExprUnopDollarLow(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarClog2:
		_push_ast_child(NodeExprUnopDollarClog2(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarPast:
		_push_ast_child(NodePseudoExprDollarPast(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarStable:
		_push_ast_child(NodePseudoExprDollarStable(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarRose:
		_push_ast_child(NodePseudoExprDollarRose(s_src_code_chunk,
			move(s_expr)));
		break;
	case Tok::KwDollarFell:
		_push_ast_child(NodePseudoExprDollarFell(s_src_code_chunk,
			move(s_expr)));
		break;
	default:
		s_src_code_chunk.err("_finish_parse_expr_any_dollar_func_of_one"
			"():  Eek!");
	}
}

} // namespace frost_hdl
