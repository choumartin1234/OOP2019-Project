#ifndef _NODE_H_
#define _NODE_H_
#include "data.h"
#include <memory>
#include <vector>
#include <functional>
namespace computational_graph
{

    class Graph;
    class Session;

    //the member function "run" of Node and its derived class may throw exception std::range_error when calculating
    class Node
    {
    protected:
        int id;
        //type=0 Node
        //type=1 Variable
        //type=2 Placeholder
        //type=3 Constant
        //type=4 Arith
        //type=5 Single_op
        //type=6 Print
        //type=7 Cmp
        //type=8 Cond
        Graph *g;
        std::vector<int> father;
        Node(Graph *_g);
        void give_id(int newid);//warning when id is not -1
    public:
        const std::vector<int> &get_father() const;
        int get_id() const;
        Graph *get_graph() const;
        void give_symbol(std::string symbol) const;
        virtual int get_type() const;
        virtual const_pData run(Session *sess,std::vector<const_pData> father_value) const;//error
        friend class Graph;
    };
    typedef std::shared_ptr<const Node> const_pNode;

    class Variable : public Node
    {
    protected:
        const_pData default_value;
    public:
        Variable(Graph *_g,const_pData default_v);
        const_pData get_default_value() const;
        virtual int get_type() const;
        virtual const_pData run(Session *sess,std::vector<const_pData> father_value) const;//warning
    };

    class Placeholder : public Node
    {
    public:
        Placeholder(Graph *_g);
        virtual int get_type() const;
        virtual const_pData run(Session *sess,std::vector<const_pData> father_value) const;//error
    };

    class Constant : public Node
    {
    protected:
        const_pData value;
    public:
        Constant(Graph *_g,const_pData v);
        virtual int get_type() const;
        virtual const_pData run(Session *sess,std::vector<const_pData> father_value) const;
    };
        
    typedef std::function<const_pData(const_pData,const_pData)> arith_op;
    class Arith : public Node
    {
        static std::map<std::string,arith_op> str2op;
    protected:
        arith_op op;
    public:
        Arith(Graph *_g,int left_id,int right_id,std::string op_str);
        virtual int get_type() const;
        virtual const_pData run(Session *sess,std::vector<const_pData> father_value) const;
    };

    typedef std::function<const_pData(const_pData)> single_op;
    class Single_op : public Node
    {
        static std::map<std::string,single_op> str2op;
    protected:
        single_op op;
    public:
        Single_op(Graph *_g,int x_id,std::string op_str);
        virtual int get_type() const;
        virtual const_pData run(Session *sess,std::vector<const_pData> father_value) const;
    }

    class Print : public Node
    {
    protected:
        std::string father_symbol;
    public:
        Print(Graph *_g,int x_id,std::string x_symbol);
        virtual int get_type() const;
        virtual const_pData run(Session *sess,std::vector<const_pData> father_value) const;
    };

    typedef std::function<const_pData(const_pData,const_pData)> cmp_op;
    class Cmp : public Node
    {
        static std::map<std::string,cmp_op> str2op;
    protected:
        cmp_op op;
    public:
        Cmp(Graph *_g,int left_id,int right_id,std::string op_str);
        virtual int get_type() const;
        virtual const_pData run(Session *sess,std::vector<const_pData> father_value) const;
    }

    class Cond : public Node
    {
    public:
        Cond(Graph *_g,int cond_id,int true_id,int false_id);
        virtual int get_type() const;
        virtual const_pData run(Session *sess,std::vector<const_pData> father_value) const;
    };

    const_pNode operator +(const_pNode left,const_pNode right);
    const_pNode operator -(const_pNode left,const_pNode right);
    const_pNode operator *(const_pNode left,const_pNode right);
    const_pNode operator /(const_pNode left,const_pNode right);
    const_pNode sin(const_pNode x);
    const_pNode log(const_pNode x);
    const_pNode exp(const_pNode x);
    const_pNode tanh(const_pNode x);
    const_pNode sigmoid(const_pNode x);
    const_pNode operator <(const_pNode left,const_pNode right);
    const_pNode operator >(const_pNode left,const_pNode right);
    const_pNode operator <=(const_pNode left,const_pNode right);
    const_pNode operator >=(const_pNode left,const_pNode right);
    const_pNode operator ==(const_pNode left,const_pNode right);
}
#endif
