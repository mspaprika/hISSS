
#include <hiSSS.h>

class Sandbox : public Hisss::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};


Hisss::Application* Hisss::CreateApplication()
{
	return new Sandbox();
}