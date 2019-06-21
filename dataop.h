#ifndef _DATAOP_H_
#define _DATAOP_H_
#include "data.h"
#include "floatfunc.h"
#include <cmath>
#include <functional>
namespace computational_graph
{
    typedef std::pair<const_pDiff,const_pDiff> pairdiff;
    std::ostream& operator<<(std::ostream &out, const Data &x);
    const_pTensor to_Tensor(const_pData x);

	const_pDiff operator+(const_pDiff left,const_pDiff right);
	const_pDiff operator-(const_pDiff left,const_pDiff right);
	const_pDiff operator*(const_pDiff left,const_pDiff right);

    const_pData operator+(const_pData left,const_pData right); //need to do variable type check
    const_pData operator-(const_pData left,const_pData right);
    const_pData operator*(const_pData left,const_pData right);
    const_pData operator/(const_pData left,const_pData right);
    const_pData plus(const_pData left,const_pData right); //initialize std::function
    const_pData minus(const_pData left,const_pData right);
    const_pData multi(const_pData left,const_pData right);
    const_pData div(const_pData left,const_pData right);

    pairdiff diff_plus(const_pData left,const_pData right);
    pairdiff diff_minus(const_pData left,const_pData right);
    pairdiff diff_multi(const_pData left,const_pData right);
    pairdiff diff_div(const_pData left,const_pData right);

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
		SingleTensorOp() =default;
		SingleTensorOp(const SingleTensorOp &y) =delete;
		SingleTensorOp& operator=(const SingleTensorOp &y) =delete;
		SingleTensorOp(SingleTensorOp &&y) =delete;
		SingleTensorOp& operator=(SingleTensorOp &&y) =delete;
		SingleTensorOp(std::function<double(double)> _op,std::function<double(double)> _diffop);
		const_pData operator()(const_pData x) const;
		const_pDiff diff(const_pData x) const;
		static const SingleTensorOp sin, log, exp, tanh, sigmoid;
	};
    class BinaryTensorOp
    {
        std::function<const_pData(const_pData,const_pData)> op;
        std::function<pairdiff(const_pData,const_pData)> diffop;
    public:
		BinaryTensorOp() =default;
		BinaryTensorOp(const BinaryTensorOp &y) =delete;
		BinaryTensorOp& operator=(const BinaryTensorOp &y) =delete;
		BinaryTensorOp(BinaryTensorOp &&y) =delete;
		BinaryTensorOp& operator=(BinaryTensorOp &&y) =delete;
        BinaryTensorOp(std::function<const_pData(const_pData,const_pData)> _op, std::function<pairdiff(const_pData,const_pData)> _diffop);
        const_pData calc(const_pData x,const_pData y) const;
        pairdiff diff(const_pData x,const_pData y) const;
        static const BinaryTensorOp tensor_plus,tensor_minus,tensor_multi,tensor_div;
    };

    //��������������ͼ��������⣨�紫��Data������󣬴���nullptr�����׳�std::runtime_error
    //����������㶨������log�Ա���<=0������0���������Message::message���Ҫ��Ĵ�����Ϣ���׳�std::range_error
}
#endif
