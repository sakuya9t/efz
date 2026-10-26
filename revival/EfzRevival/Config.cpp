// EfzRevival.dll compiles the same Config.cpp as the launcher (and DDRAW.dll): the
// ini keys and the DIK_/BUTTON_ tables are identical. The addresses below are the
// DLL's copies, which link-time code generation laid out in this order.
#include "../EfzRevivalLauncher/Config.cpp"

// FUNCTION: 0x100655a0 Config::readKey
// FUNCTION: 0x10065620 Config::loadPadNames
// FUNCTION: 0x10065d70 Config::loadKeyNames
// FUNCTION: 0x100688d0 Config::readInt
// FUNCTION: 0x10068900 Config::readString
// FUNCTION: 0x10068980 Config::load
// FUNCTION: 0x1006a140 Config::~Config
// FUNCTION: 0x1006a1c0 Config::Config
// FUNCTION: 0x1006a2a0 ?to_utf8@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@2@@Z
// FUNCTION: 0x1006a2e0 ?to_utf8@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PB_WH@Z
// FUNCTION: 0x1006a630 isValidAddress
