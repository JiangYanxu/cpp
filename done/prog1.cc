#include "tools.h"
int main()
{
	byte_view(sizeof("我爱你ABCD"), (u_char *)"我爱你ABCD");
	byte_view(sizeof(u"我爱你ABCD"), (u_char *)u"我爱你ABCD");
	byte_view(sizeof(U"我爱你ABCD"), (u_char *)U"我爱你ABCD");
	byte_view(sizeof(L"我爱你ABCD"), (u_char *)L"我爱你ABCD");
	byte_view(sizeof(u8"我爱你ABCD"), (u_char *)u8"我爱你ABCD");
	return 0;
}
