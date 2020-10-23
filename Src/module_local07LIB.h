#include <iostream>

namespace pets
{
	class Pet
	{
	protected:
		std::string m_name;
	public:
		Pet(const std::string &name):m_name(name){}
		const std::string& getName() const {return m_name;}
	};
}
