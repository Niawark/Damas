#include <fstream>
using namespace std;

class Moviment 
{

public:
	void inicialitza(int fo, int co, int fd, int cd) 
	{
		m_filaorigen = fo;
		m_columnaorigen = co;
		m_filadesti = fd;
		m_columnadesti = cd;
	}

	int get_filaorigen() { return m_filaorigen; }
	int get_filadesti() { return m_filadesti; }
	int get_columnaorigen() { return m_columnaorigen; }
	int get_columnadesti() { return m_columnadesti; }

private:

	int m_filaorigen, m_filadesti, m_columnaorigen, m_columnadesti;

};

