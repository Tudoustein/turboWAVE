#include "meta_base.h"
#include "computeTool.h"
#include "physics.h"


bool ADK::Test()
{
	ionizationPotential = 24.587*tw::dims::temperature >> cgs >> native;
    electrons = 2;
    protons = 2;
    Initialize();
    if (task->strip[0].Get_rank()==0)
    {
        const tw::Float field = (0.1-cutoff_field)*tw::dims::electric_field >> atomic >> native;
        const tw::Float rate = AverageRate(1.0,field)*tw::dims::frequency >> native >> atomic;
        const tw::Float expected = 4.546e-7;
        assert(fabs(rate-expected)<expected/100);
    }
	return true;
}

bool PPT_Tunneling::Test()
{
	ionizationPotential = 24.587*tw::dims::temperature >> cgs >> native;
    electrons = 2;
    protons = 2;
    Initialize();
    if (task->strip[0].Get_rank()==0)
    {
        const tw::Float field = (0.1-cutoff_field)*tw::dims::electric_field >> atomic >> native;
        const tw::Float rate = AverageRate(1.0,field)*tw::dims::frequency >> native >> atomic;
        const tw::Float expected = 3.6774e-7;
        assert(fabs(rate-expected)<expected/100);
    }
	return true;
}
