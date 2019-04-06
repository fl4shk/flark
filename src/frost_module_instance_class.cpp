#include "frost_module_instance_class.hpp"

namespace frost_hdl
{

FrostModuleInstance::FrostModuleInstance
	(const SrcCodePos& s_src_code_pos, SavedString s_ident)
	: _src_code_pos(s_src_code_pos), _ident(s_ident)
{
}

FrostModuleInstance::~FrostModuleInstance()
{
}

} // namespace frost_hdl
