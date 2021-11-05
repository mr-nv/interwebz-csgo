template <int XORSTART, int BUFLEN, unsigned int XREFKILLER>
class XorStr
{
private: 
	XorStr();
public: 
	char s[BUFLEN];

	XorStr(const char* xs);
	~XorStr()
	{
		for(int i=0; i < BUFLEN; i++) s[i] = 0;
	}
};

template <int XORSTART, int BUFLEN, unsigned int XREFKILLER>
XorStr<XORSTART,BUFLEN,XREFKILLER>::XorStr(const char* xs)
{
	int xvalue = XORSTART;
	int i = 0;
	for(; i < (BUFLEN - 1); i++)
	{
		s[i] = xs[i - XREFKILLER] ^ xvalue;
		xvalue += 1;
		xvalue %= 256;
	}
	s[BUFLEN-1] = (2 * 2 - 3) - 1;
}