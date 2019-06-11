#ifndef _DATAOP_H_
#define _DATAOP_H_
#include "data.h"
#include "floatfunc.h"
#include <cmath>
#include <functional>
namespace computational_graph
{
    std::ostream& operator<<(std::ostream &out, const Data &x);
    const_pData operator+(const_pData left,const_pData right); //need to do variable type check
    const_pData operator-(const_pData left,const_pData right);
    const_pData operator*(const_pData left,const_pData right);
    const_pData operator/(const_pData left,const_pData right);
    const_pData plus(const_pData left,const_pData right); //initialize std::function
    const_pData minus(const_pData left,const_pData right);
    const_pData multi(const_pData left,const_pData right);
    const_pData div(const_pData left,const_pData right);
    const_pData less_float(const_pData left,const_pData right);
    const_pData greater_float(const_pData left,const_pData right);
    const_pData leq_float(const_pData left,const_pData right);
    const_pData geq_float(const_pData left,const_pData right);
    const_pData equal_float(const_pData left,const_pData right);
    //�����Ƚ����㷵��float
    
    class SingleTensorOp
    {
		std::function<double(double)> op,diffop;
	public:
		SingleTensorOp(std::function<double(double)> op,std::function<double(double)> diffop);
		const_pData operator()(const_pData x) const;
		const_pDiff diff(const_pData x) const;
		static const SingleTensorOp sin, log, exp, tanh, sigmoid;
	};
    //��������������ͼ��������⣨�紫��Data������󣬴���nullptr�����׳�std::runtime_error
    //����������㶨������log�Ա���<=0������0���������Message::message���Ҫ��Ĵ�����Ϣ���׳�std::range_error
}
#endif