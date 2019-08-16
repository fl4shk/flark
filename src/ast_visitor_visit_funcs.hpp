// src/ast_visitor_visit_funcs.hpp

virtual void visitProgram(NodeProgram* node) = 0;
virtual void visitPackage(NodePackage* node) = 0;
virtual void visitScopePackage(NodeScopePackage* node) = 0;
virtual void visitModule(NodeModule* node) = 0;
virtual void visitScopeModproc(NodeScopeModproc* node) = 0;
virtual void visitParamArgTypeSublist(NodeParamArgTypeSublist* node) = 0;
virtual void visitArgPortSublist(NodeArgPortSublist* node) = 0;
virtual void visitParamArgVarSublist(NodeParamArgVarSublist* node) = 0;
virtual void visitParamModuleSublist(NodeParamModuleSublist* node) = 0;
virtual void visitParamList(NodeParamList* node) = 0;
virtual void visitArgList(NodeArgList* node) = 0;
virtual void visitLeftRightBase(NodeLeftRightBase* node) = 0;
virtual void visitIdentTerminal(NodeIdentTerminal* node) = 0;
virtual void visitIdentMemberAccess(NodeIdentMemberAccess* node) = 0;
virtual void visitIdentScopeAccess(NodeIdentScopeAccess* node) = 0;
virtual void visitCall(NodeCall* node) = 0;
virtual void visitIdentEtc(NodeIdentEtc* node) = 0;
virtual void visitNumExpr(NodeNumExpr* node) = 0;
virtual void visitSizedNumExpr(NodeSizedNumExpr* node) = 0;
virtual void visitBracketPair(NodeBracketPair* node) = 0;
virtual void visitParenPair(NodeParenPair* node) = 0;
virtual void visitHasString(NodeHasString* node) = 0;
virtual void visitIdent(NodeIdent* node) = 0;
virtual void visitConstString(NodeConstString* node) = 0;
virtual void visitScopeBehav(NodeScopeBehav* node) = 0;
virtual void visitEnum(NodeEnum* node) = 0;
virtual void visitScopeEnum(NodeScopeEnum* node) = 0;
virtual void visitClass(NodeClass* node) = 0;
virtual void visitScopeClass(NodeScopeClass* node) = 0;
virtual void visitExtends(NodeExtends* node) = 0;
virtual void visitMemberCallable(NodeMemberCallable* node) = 0;
virtual void visitUnion(NodeUnion* node) = 0;
virtual void visitScopeUnion(NodeScopeUnion* node) = 0;
virtual void visitParamPossibleTypename(NodeParamPossibleTypename* node) = 0;
virtual void visitNoParamPossibleTypename(NodeNoParamPossibleTypename* node) = 0;
virtual void visitTypeof(NodeTypeof* node) = 0;
virtual void visitTypeRange(NodeTypeRange* node) = 0;
virtual void visitRangeSuffix(NodeRangeSuffix* node) = 0;
virtual void visitAuto(NodeAuto* node) = 0;
virtual void visitVoid(NodeVoid* node) = 0;
virtual void visitUwire(NodeUwire* node) = 0;
virtual void visitSwire(NodeSwire* node) = 0;
virtual void visitUbit(NodeUbit* node) = 0;
virtual void visitSbit(NodeSbit* node) = 0;
virtual void visitUbyte(NodeUbyte* node) = 0;
virtual void visitSbyte(NodeSbyte* node) = 0;
virtual void visitUshortint(NodeUshortint* node) = 0;
virtual void visitSshortint(NodeSshortint* node) = 0;
virtual void visitUint(NodeUint* node) = 0;
virtual void visitSint(NodeSint* node) = 0;
virtual void visitUlongint(NodeUlongint* node) = 0;
virtual void visitSlongint(NodeSlongint* node) = 0;
virtual void visitSelf(NodeSelf* node) = 0;
virtual void visitPosParamArgInstList(NodePosParamArgInstList* node) = 0;
virtual void visitNamedParamArgInstList(NodeNamedParamArgInstList* node) = 0;
virtual void visitOneParamArgInst(NodeOneParamArgInst* node) = 0;
virtual void visitExprBase(NodeExprBase* node) = 0;
virtual void visitExprBinopBase(NodeExprBinopBase* node) = 0;
virtual void visitExprUnopBase(NodeExprUnopBase* node) = 0;
virtual void visitExprBinopLogAnd(NodeExprBinopLogAnd* node) = 0;
virtual void visitExprBinopLogOr(NodeExprBinopLogOr* node) = 0;
virtual void visitExprBinopCmpEq(NodeExprBinopCmpEq* node) = 0;
virtual void visitExprBinopCmpNe(NodeExprBinopCmpNe* node) = 0;
virtual void visitExprBinopCmpLt(NodeExprBinopCmpLt* node) = 0;
virtual void visitExprBinopCmpGt(NodeExprBinopCmpGt* node) = 0;
virtual void visitExprBinopCmpLe(NodeExprBinopCmpLe* node) = 0;
virtual void visitExprBinopCmpGe(NodeExprBinopCmpGe* node) = 0;
virtual void visitExprBinopPlus(NodeExprBinopPlus* node) = 0;
virtual void visitExprBinopMinus(NodeExprBinopMinus* node) = 0;
virtual void visitExprBinopMul(NodeExprBinopMul* node) = 0;
virtual void visitExprBinopDiv(NodeExprBinopDiv* node) = 0;
virtual void visitExprBinopMod(NodeExprBinopMod* node) = 0;
virtual void visitExprBinopBitAnd(NodeExprBinopBitAnd* node) = 0;
virtual void visitExprBinopBitOr(NodeExprBinopBitOr* node) = 0;
virtual void visitExprBinopBitXor(NodeExprBinopBitXor* node) = 0;
virtual void visitExprBinopBitLsl(NodeExprBinopBitLsl* node) = 0;
virtual void visitExprBinopBitLsr(NodeExprBinopBitLsr* node) = 0;
virtual void visitExprBinopBitAsr(NodeExprBinopBitAsr* node) = 0;
virtual void visitExprUnopLogNot(NodeExprUnopLogNot* node) = 0;
virtual void visitExprUnopBitNot(NodeExprUnopBitNot* node) = 0;
virtual void visitExprUnopPlus(NodeExprUnopPlus* node) = 0;
virtual void visitExprUnopMinus(NodeExprUnopMinus* node) = 0;
virtual void visitExprUnopDollarUnsigned(NodeExprUnopDollarUnsigned* node) = 0;
virtual void visitExprUnopDollarSigned(NodeExprUnopDollarSigned* node) = 0;
virtual void visitExprUnopDollarIsUnsigned(NodeExprUnopDollarIsUnsigned* node) = 0;
virtual void visitExprUnopDollarIsSigned(NodeExprUnopDollarIsSigned* node) = 0;
virtual void visitExprUnopDollarRange(NodeExprUnopDollarRange* node) = 0;
virtual void visitExprUnopDollarRevrange(NodeExprUnopDollarRevrange* node) = 0;
virtual void visitExprUnopDollarSize(NodeExprUnopDollarSize* node) = 0;
virtual void visitExprUnopDollarFirst(NodeExprUnopDollarFirst* node) = 0;
virtual void visitExprUnopDollarLast(NodeExprUnopDollarLast* node) = 0;
virtual void visitExprUnopDollarHigh(NodeExprUnopDollarHigh* node) = 0;
virtual void visitExprUnopDollarLow(NodeExprUnopDollarLow* node) = 0;
virtual void visitExprUnopDollarClog2(NodeExprUnopDollarClog2* node) = 0;
virtual void visitExprBinopDollarPow(NodeExprBinopDollarPow* node) = 0;
virtual void visitPseudoExprDollarBase(NodePseudoExprDollarBase* node) = 0;
virtual void visitPseudoExprDollarPast(NodePseudoExprDollarPast* node) = 0;
virtual void visitPseudoExprDollarStable(NodePseudoExprDollarStable* node) = 0;
virtual void visitPseudoExprDollarRose(NodePseudoExprDollarRose* node) = 0;
virtual void visitPseudoExprDollarFell(NodePseudoExprDollarFell* node) = 0;
virtual void visitPseudoExprDollarGlobalClock(NodePseudoExprDollarGlobalClock* node) = 0;
virtual void visitExprUnopTypeof(NodeExprUnopTypeof* node) = 0;
virtual void visitExprCat(NodeExprCat* node) = 0;
virtual void visitListCat(NodeListCat* node) = 0;
virtual void visitExprRepl(NodeExprRepl* node) = 0;
virtual void visitExprRangeAny(NodeExprRangeAny* node) = 0;
virtual void visitRangeOne(NodeRangeOne* node) = 0;
virtual void visitRangeTwo(NodeRangeTwo* node) = 0;
virtual void visitStmtList(NodeStmtList* node) = 0;
virtual void visitStmtAnyFor(NodeStmtAnyFor* node) = 0;
virtual void visitStmtFor(NodeStmtFor* node) = 0;
virtual void visitStmtGenerateFor(NodeStmtGenerateFor* node) = 0;
virtual void visitStmtIf(NodeStmtIf* node) = 0;
virtual void visitStmtGenerateIf(NodeStmtGenerateIf* node) = 0;
virtual void visitStmtWhile(NodeStmtWhile* node) = 0;
virtual void visitStmtBehavAssign(NodeStmtBehavAssign* node) = 0;
virtual void visitStmtContAssign(NodeStmtContAssign* node) = 0;
virtual void visitStmtMemberAccessPublic(NodeStmtMemberAccessPublic* node) = 0;
virtual void visitStmtMemberAccessProtected(NodeStmtMemberAccessProtected* node) = 0;
virtual void visitStmtMemberAccessPrivate(NodeStmtMemberAccessPrivate* node) = 0;
virtual void visitStmtSwitch(NodeStmtSwitch* node) = 0;
virtual void visitStmtSwitchz(NodeStmtSwitchz* node) = 0;
virtual void visitStmtCase(NodeStmtCase* node) = 0;
virtual void visitStmtDefault(NodeStmtDefault* node) = 0;
virtual void visitScopeSwitch(NodeScopeSwitch* node) = 0;
virtual void visitStmtUsing(NodeStmtUsing* node) = 0;
virtual void visitStmtInstModule(NodeStmtInstModule* node) = 0;
virtual void visitStmtReturn(NodeStmtReturn* node) = 0;
virtual void visitStmtInitial(NodeStmtInitial* node) = 0;
virtual void visitStmtAlwaysComb(NodeStmtAlwaysComb* node) = 0;
virtual void visitStmtAlwaysBlk(NodeStmtAlwaysBlk* node) = 0;
virtual void visitStmtAlwaysFf(NodeStmtAlwaysFf* node) = 0;
virtual void visitStmtAssert(NodeStmtAssert* node) = 0;
virtual void visitStmtAssume(NodeStmtAssume* node) = 0;
virtual void visitStmtCover(NodeStmtCover* node) = 0;
virtual void visitStmtRestrict(NodeStmtRestrict* node) = 0;
virtual void visitStmtStaticAssert(NodeStmtStaticAssert* node) = 0;
virtual void visitPosedgeInst(NodePosedgeInst* node) = 0;
virtual void visitNegedgeInst(NodeNegedgeInst* node) = 0;
virtual void visitEdgeList(NodeEdgeList* node) = 0;
virtual void visitDeclCallable(NodeDeclCallable* node) = 0;
virtual void visitDeclFunc(NodeDeclFunc* node) = 0;
virtual void visitDeclProc(NodeDeclProc* node) = 0;
virtual void visitDeclTask(NodeDeclTask* node) = 0;
virtual void visitIdentTermEqualsExtra(NodeIdentTermEqualsExtra* node) = 0;
virtual void visitIdentTermEqualsExtraList(NodeIdentTermEqualsExtraList* node) = 0;
virtual void visitDeclConstList(NodeDeclConstList* node) = 0;
virtual void visitDeclVarList(NodeDeclVarList* node) = 0;
virtual void visitModport(NodeModport* node) = 0;
virtual void visitModportSubList(NodeModportSubList* node) = 0;
virtual void visitIdentList(NodeIdentList* node) = 0;
