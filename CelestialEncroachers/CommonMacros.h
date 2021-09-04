#ifndef MACROS_HEADER
#define MACROS_HEADER

namespace CommonUtilites
{
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define SAFE_DELETE(a) delete(a); a = nullptr;
#define ARRAY_SAFE_DELETE(a) delete[](a); a = nullptr;
};
namespace CU = CommonUtilites;
#endif