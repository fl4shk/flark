// src/ast_node_type_enum.hpp

enum class Type
{
	Base,
	List,
	Package,
	ScopePackage,
	Module,
	ScopeModule,
	InputSubPortArgList,
	OutputSubPortArgList,
	BidirSubPortArgList,
	SubParamArgList,
	SubParamModule,
	SubParamModuleList,
	ParamArgList,
	LeftRightBase,
	IdentBracket,
	IdentScope,
	Call,
	IdentEtc,
	NumExpr,
	SizedNumExpr,
	BracketPair,
	HasString,
	Ident,
	ConstString,
	ScopeUnnamed,
	Enum,
	ScopeEnum,
	Class,
	ScopeClass,
	Extends,
	Union,
	ScopeUnion,
	Typename,
	Type,
	Auto,
	Void,
	Uwire,
	Swire,
	Ubit,
	Sbit,
	Ubyte,
	Sbyte,
	Ushortint,
	Sshortint,
	Uint,
	Sint,
	Ulongint,
	Slongint,
	Self,
	PosParamArgInstList,
	NamedParamArgInstList,
	OneParamArgInst,
	ExprBase,
	ExprBinopBase,
	ExprUnopBase,
	ExprBinopLogAnd,
	ExprBinopLogOr,
	ExprBinopCmpEq,
	ExprBinopCmpNe,
	ExprBinopCmpLt,
	ExprBinopCmpGt,
	ExprBinopCmpLe,
	ExprBinopCmpGe,
	ExprBinopPlus,
	ExprBinopMinus,
	ExprBinopMul,
	ExprBinopDiv,
	ExprBinopMod,
	ExprBinopBitAnd,
	ExprBinopBitOr,
	ExprBinopBitXor,
	ExprBinopBitLsl,
	ExprBinopBitLsr,
	ExprBinopBitAsr,
	ExprUnopLogNot,
	ExprUnopBitNot,
	ExprUnopPlus,
	ExprUnopMinus,
	ExprUnopDollarUnsgn,
	ExprUnopDollarSgn,
	ExprUnopDollarIsUnsgn,
	ExprUnopDollarIsSgn,
	ExprUnopDollarRange,
	ExprUnopDollarSize,
	ExprUnopDollarMsbpos,
	ExprUnopDollarFirst,
	ExprUnopDollarLast,
	ExprUnopDollarHigh,
	ExprUnopDollarLow,
	ExprUnopDollarClog2,
	ExprBinopDollarPow,
	PseudoExprDollarBase,
	PseudoExprDollarPast,
	PseudoExprDollarStable,
	PseudoExprDollarRose,
	PseudoExprDollarFell,
	PseudoExprDollarGlobalClock,
	ExprUnopTypeof,
	ExprCat,
	ListCat,
	ExprRepl,
	ExprRangeAny,
	RangeOne,
	RangeTwo,
	StmtList,
	StmtAnyFor,
	StmtFor,
	StmtGenerateFor,
	StmtAnyIf,
	StmtAnyElse,
	StmtIf,
	StmtElse,
	StmtGenerateIf,
	StmtGenerateElse,
	StmtAnyWhile,
	StmtGenerateWhile,
	StmtWhile,
	StmtGenerateDoWhile,
	StmtDoWhile,
	StmtGenerateAlone,
	StmtBehavAssign,
	StmtContAssign,
	StmtLabMemberAccessPublic,
	StmtLabMemberAccessProtected,
	StmtLabMemberAccessPrivate,
	StmtSwitch,
	StmtSwitchz,
	StmtCase,
	StmtDefault,
	StmtUsing,
	StmtInstModule,
	StmtReturn,
	StmtInitial,
	StmtAlwaysComb,
	StmtAlwaysBlk,
	StmtAlwaysFf,
	StmtAssert,
	StmtAssume,
	StmtCover,
	StmtRestrict,
	StmtStaticAssert,
	PosedgeInst,
	NegedgeInst,
	EdgeList,
	DeclCallable,
	DeclFunc,
	DeclProc,
	DeclTask,
	DeclVar,
	DeclConst,
	DeclGenvar,
	DeclVarList,
};
