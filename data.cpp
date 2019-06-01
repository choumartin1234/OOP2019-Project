#include <cmath>
#include <memory>
#include <string>
#include <stdio.h>
#include <iostream>
#include "data.h"
#include "message.h"
namespace computational_graph
{

    string double_to_string(double v)
    {
        char buffer[50];
        std::sprintf(buffer, "%.4lf", v); //4-digits output
        return std::string(buffer);
    }

    const double eps=1e-7;
    bool double_boolean(double v)
    {
        return v>eps;
    }

    Tensor::Tensor(const Tensor &y):shape(y.shape), dim(y.dim), size(y.size)
    {
        p=new double[size];
        memcpy(p,y.p,size*sizeof(double));
    }
    Tensor::Tensor(vector<double> init_v, vector<int> init_shape):shape(init_shape), dim(init_shape.size())
    {
        int s=1;
        for(auto i: shape) s*=i;
        if(init_v.size()!=s)
        {
            throw std::runtime_error("Fail to construct a tensor: size doesn't fit.");
        }
        p=new double[s];
        size=s;
        for(int i=0;i<size;++i) p[i]=init_v[i];
    }
    
    shared_ptr<const Tensor> Tensor::create(double *init_v, vector<int> init_shape)
    {
        return make_shared<const Tensor>(init_v, std::move(init_shape));
    }

    string Tensor::to_string() const
    {
        string res;
        vector<int> index(dim,0);
        for(int i=0;i<dim;++i) res+="[";
        for(int i=0;i<size;++i)
        {
            res+=double_to_string(p[i]);
            int j=dim-1;
            while(j>=0&&index[j]==shape[j]-1)
            {
                index[j]=0;
                res+="]";
                --j;
            }
            if(j>=0)
            {
                ++index[j];
                res+=", ";
            }
        }
        return res;
    }
    vector<double> Tensor::get_val() const
    {
        return vector<double>(p,p+size);
    }
    double Tensor::getval(vector<int> index) const
    {
        int indexid=0,t=1;
        for(int i=index.size()-1;i>=0;--i)
        {
            indexid+=index[i]*t;
            t*=shape[i];
        }
        return p[indexid];
    }
    bool Tensor::boolean() const
    {
        if(size==1) return double_boolean(p[0]);
        Message::error("connot convert a tensor(which is not a scalar) to boolean value. returning false.");
        return false;
    }
    unique_ptr<const Data> Tensor::copy() const
    {
        return make_unique<const Tensor>(*this);
    }
    vector<int> Tensor::get_shape() const
    {
        return shape;
    }
    shared_ptr<const Tensor> Tensor::reshape(vector<int> nshape)
    {
        int nsize=1;
        for(int i:nshape) nsize*=i;
        if(nsize!=size)
        {
            Message::error("Fail to reshape:size doesn't fit.");
            return nullptr;
        }
        return make_shared<const Tensor>(vector<double>(p,p+size), nshape);
    }
    Tensor::~Tensor()
    {
        delete[] p;
    }

    Float::Float(const Float &y):Tensor(y){}
    Float::Float(double init_v):shape(1,1), dim(1), size(1)
    {
        p=new double[1];
        p[0]=init_v;
    }
    shared_ptr<const Float> Float::create(double init_v)
    {
        return make_shared<const Float>(init_v);
    }
    double Float::get_val() const
    {
        return p[0];
    }
    string Float::to_string() const
    {
        return double_to_string(p[0]);
    }
    unique_ptr<const Data> Float::copy() const
    {
        return make_unique<const Float>(*this);
    }

    Diff::Diff(const Diff &y):Tensor(y),dim1(y.dim1),dim2(y.dim2) {}
    Diff::Diff(vector<double> init_v,vector<int> init_shape, int dimf):
        dim1(dimf),dim2(init_shape.size()-dimf),Tensor(init_v,init_shape) 
    {}
    shared_ptr<const Diff> create(vector<double> init_v,vector<int> init_shape, int dimf)
    {
        return make_shared<const Diff>(init_v,init_shape,dimf);
    }
    unique_ptr<const Data> Diff::copy() const
    {
        return make_unique<const Diff>(*this);
    }
    
    Matrix::Matrix(const Matrix &y):Diff(y),n(y.n),m(y.m) {}
    Matrix::Matrix(vector<double> init_v, int d1,int d2):
        Diff(init_v,vector<int>{n,m},1),n(d1),m(d2)
    {
        if(d1*d2!=init_v.size())
        {
            throw std::runtime_error("Fail to construct a matrix: size doesn't fit.");
        }
    }
    shared_ptr<const Matrix> Matrix::create(vector<double> init_v,int n,int m)
    {
        return make_shared<const Matrix>(init_v,n,m);
    }
    unique_ptr<const Data> Matrix::copy() const
    {
        return make_unique<const Matrix>(*this);
    }
    
    Graddata::Grad(map<int,const_pDiff> init_grad):grad(init_grad){}
    unique_ptr<const Data> Graddata::copy() const
    {
        return make_unique<const Grad>(*this);
    }
    const_pDiff Graddata::get_grad(int x_id) const
    {
        auto it=grad.find(x_id);
        if(it!=grad.end()) return it->second;else return nullptr;
    }
    const vector<int>& Graddata::get_fshape()
    {
        return fshape;
    }
}
