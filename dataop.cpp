#include "data.h"
#include "dataop.h"
namespace computational_graph
{
    std::ostream& operator<<(std::ostream &out, const Data &x)
    {
        out << x.to_string();
        return out;
    }
    const_pTensor to_Tensor(const_pData x) //type check, change const_pData into const_pFloat
    {
        if(!x) throw std::runtime_error("Computation failed on null data.");
        if (auto x_f = std::dynamic_pointer_cast<const Tensor>(x))
            return x_f;
        throw std::runtime_error("Computation failed on non-tensor data.");
    }
    const_pData plus(const_pData left,const_pData right)
    {
        auto left_f = to_Tensor(left);
        auto right_f = to_Tensor(right);
        return std::make_shared<const Float>(left_f -> get_val() + right_f -> get_val()); 
    }
    const_pData minus(const_pData left,const_pData right)
    {
        auto left_f = to_Tensor(left);
        auto right_f = to_Tensor(right);
        return std::make_shared<const Float>(left_f -> get_val() - right_f -> get_val()); 
    }
    const_pData multi(const_pData left,const_pData right)
    {
        auto left_f = to_Tensor(left);
        auto right_f = to_Tensor(right);
        return std::make_shared<const Float>(left_f -> get_val() * right_f -> get_val()); 
    }
    const_pData div(const_pData left,const_pData right)
    {
        auto left_f = to_Tensor(left);
        auto right_f = to_Tensor(right);
        if (right_f -> get_val() != 0)
            return std::make_shared<const Float>(left_f -> get_val() / right_f -> get_val()); 
        Message::message("ERROR: Division by zero");
        throw std::range_error("Division by zero");
    }
    const_pData operator+(const_pData left,const_pData right){return plus(left, right);}
    const_pData operator-(const_pData left,const_pData right){return minus(left, right);}
    const_pData operator*(const_pData left,const_pData right){return multi(left, right);}
    const_pData operator/(const_pData left,const_pData right){return div(left, right);}
    const_pData less_float(const_pData left,const_pData right)
    {
        auto left_f = to_Tensor(left);
        auto right_f = to_Tensor(right);
        return std::make_shared<const Float>(left_f -> get_val() < right_f -> get_val()); 
    }
    const_pData greater_float(const_pData left,const_pData right)
    {
        auto left_f = to_Tensor(left);
        auto right_f = to_Tensor(right);
        return std::make_shared<const Float>(left_f -> get_val() > right_f -> get_val()); 
    }
    const_pData leq_float(const_pData left,const_pData right)
    {
        auto left_f = to_Tensor(left);
        auto right_f = to_Tensor(right);
        return std::make_shared<const Float>(left_f -> get_val() <= right_f -> get_val()); 

    }
    const_pData geq_float(const_pData left,const_pData right)
    {
        auto left_f = to_Tensor(left);
        auto right_f = to_Tensor(right);
        return std::make_shared<const Float>(left_f -> get_val() >= right_f -> get_val()); 
    }
    const_pData equal_float(const_pData left,const_pData right)
    {
        auto left_f = to_Tensor(left);
        auto right_f = to_Tensor(right);
        return std::make_shared<const Float>(left_f -> get_val() == right_f -> get_val()); 
    } //�����Ƚ����㷵��float
    const_pData sin(const_pData x)
    {
        auto x_f = to_Tensor(x);
        return std::make_shared<const Float>(std::sin(x_f -> get_val()));    
    }  
    const_pData log(const_pData x)
    {
        auto x_f = to_Tensor(x);
        if (x_f -> get_val() > 0)
            return std::make_shared<const Float>(std::log(x_f -> get_val()));
        Message::message("ERROR: LOG operator's input must be positive");
        throw std::range_error("LOG operator's input must be positive");
    }
    const_pData exp(const_pData x)
    {
        auto x_f = to_Tensor(x);
        return std::make_shared<const Float>(std::exp(x_f -> get_val()));
    }
    const_pData tanh(const_pData x)
    {
        auto x_f = to_Tensor(x);
        return std::make_shared<const Float>(std::tanh(x_f -> get_val()));
    }
    const_pData sigmoid(const_pData x)
    {
        auto x_f = to_Tensor(x);
        return std::make_shared<const Float>(1.0 / (1.0 + std::exp(-1 * x_f -> get_val())));   
    }
    //��������������ͼ��������⣨�紫��Data������󣬴���nullptr�����׳�std::runtime_error
    //����������㶨������log�Ա���<=0������0���������Message::message���Ҫ��Ĵ�����Ϣ���׳�std::range_error  
}