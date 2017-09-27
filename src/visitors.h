#pragma once

#include "var.h"
#include <boost/variant.hpp>

namespace et{
/*
class var_visitor : public boost::static_visitor<term_type> {
public:
    term_type operator()(double) const { return term_type::double_t;}
    term_type operator()(MatrixXd) const { return term_type::matrix_t;}
    term_type operator()(VectorXd) const { return term_type::vector_t;}
};
*/

class eval_plus_visitor : public boost::static_visitor<term_t> {
public:
    term_t operator()(double lhs, double rhs) const{
        return {double(lhs + rhs)};
    }
    term_t operator()(double lhs, const VectorXd& rhs) const{
        return {VectorXd(lhs + rhs.array())};
    }
    term_t operator()(double lhs, const MatrixXd& rhs) const{
        return {MatrixXd(lhs + rhs.array())};
    }
    term_t operator()(const VectorXd& lhs, double rhs) const{
        return operator()(rhs, lhs);
    }
    term_t operator()(const VectorXd& lhs, const VectorXd& rhs) const{
        return {VectorXd(lhs + rhs)};
    }
    term_t operator()(const VectorXd& lhs, const MatrixXd& rhs) const{
        // Vector + Matrix will always be rowwise additions.
        // For example:
        // >>> y = np.ones((5,))
        // >>> x = np.ones((3,5))
        // >>> x + y
        // array([[ 2.,  2.,  2.,  2.,  2.],
        //        [ 2.,  2.,  2.,  2.,  2.],
        //        [ 2.,  2.,  2.,  2.,  2.]])
        return {MatrixXd(rhs.rowwise() + lhs.transpose())};
    }
    term_t operator()(const MatrixXd& lhs, double rhs) const{
        return operator()(rhs, lhs);
    }
    term_t operator()(const MatrixXd& lhs, const VectorXd& rhs) const{
        return operator()(rhs, lhs);
    }
    term_t operator()(const MatrixXd& lhs, const MatrixXd& rhs) const{
        return {MatrixXd(lhs + rhs)};
    }
};

class eval_minus_visitor : public boost::static_visitor<term_t> {
public:
    term_t operator()(double lhs, double rhs) const{
        return {double(lhs - rhs)};
    }
    term_t operator()(double lhs, const VectorXd& rhs) const{
        return {VectorXd(lhs - rhs.array())};
    }
    term_t operator()(double lhs, const MatrixXd& rhs) const{
        return {MatrixXd(lhs - rhs.array())};
    }
    term_t operator()(const VectorXd& lhs, double rhs) const{
        return {VectorXd(lhs.array() - rhs)};
    }
    term_t operator()(const VectorXd& lhs, const VectorXd& rhs) const{
        return {VectorXd(lhs - rhs)};
    }
    term_t operator()(const VectorXd& lhs, const MatrixXd& rhs) const{
        // Vector + Matrix will always be rowwise additions.
        // For example:
        // >>> y = np.ones((5,))
        // >>> x = np.ones((3,5))
        // >>> x + y
        // array([[ 2.,  2.,  2.,  2.,  2.],
        //        [ 2.,  2.,  2.,  2.,  2.],
        //        [ 2.,  2.,  2.,  2.,  2.]])
        return {MatrixXd((-rhs.rowwise()) + lhs.tranpose())};
    }
    term_t operator()(const MatrixXd& lhs, double rhs) const{
        return {MatrixXd(lhs.array() - rhs)}; 
    }
    term_t operator()(const MatrixXd& lhs, const VectorXd& rhs) const{
        return {MatrixXd(lhs.rowwise() - rhs.transpose())};
    }
    term_t operator()(const MatrixXd& lhs, const MatrixXd& rhs) const{
        return {MatrixXd(lhs - rhs)};
    }
};

}


