#include <cmath>
#include <iostream>
#include <memory>
#include <optional>
#include <vector>

class var {
private:
    double value_;
    std::string op_;
    std::shared_ptr<var> left_;
    std::shared_ptr<var> right_;

public:
    var(const var& v)
        : value_(v.value_), left_(v.left_), right_(v.right_), op_(v.op_) {}
    var(const double& v) : value_(v){};
    void set_left(std::shared_ptr<var> v) { left_ = v; }
    void set_right(std::shared_ptr<var> v) { right_ = v; }

    std::shared_ptr<var> get_left() { return left_; }
    std::shared_ptr<var> get_right() { return right_; }

    double value() const { return value_; }

    bool is_operation() {
        if (op_ == "") return false;
        return true;
    }

    std::string operation() { return op_; }

    var operator=(const var& v) {
        value_ = v.value_;
        left_ = v.left_;
        right_ = v.right_;
        op_ = v.op_;
        return *this;
    }

    friend var operator+(const var& l, const var& r) {
        var result(l.value_ + r.value_);
        result.left_ = std::make_shared<var>(l.value_);
        result.right_ = std::make_shared<var>(r.value_);
        result.op_ = "+";
        return result;
    }

    friend var operator*(const var& l, const var& r) {
        var result(l.value_ * r.value_);
        result.left_ = std::make_shared<var>(l.value_);
        result.right_ = std::make_shared<var>(r.value_);
        result.op_ = "*";
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const var& var) {
        os << var.value_;
        return os;
    }
};

namespace function {
struct exp {
    exp() {}
    var operator()(const var e) {
        var result(std::exp(e.value()));
        result.set_left(std::make_shared<var>(e));
        return result;
    }
};
}  // namespace function

int main() {
    // tests are in reverse order of complexity
    {
        var x(10);
        var y(20);
        var z(4.5);

        auto w = (x + y) * z + (z + x) * y;

        auto pl = w.get_left();
        auto pr = w.get_right();
        auto o = w.operation();
        std::cout << *pl << o << *pr << std::endl;

        auto pl_1 = pl->get_left();
        auto pr_1=  pl->get_right();
        auto o_1 = pl->operation();
        std::cout << *pl_1 << o_1 << *pr_1 << std::endl;

        auto pl_2 = pr->get_left();
        auto pr_2=  pr->get_right();
        auto o_2 = pr->operation();
        std::cout << *pl_2 << o_2 << *pr_2 << std::endl;
    }

    // testing basic addition
    {
        var a(1);
        var b(10);

        auto x_ = a + b;
        auto a_ = x_.get_left();
        auto b_ = x_.get_right();

        std::cout << x_ << std::endl;
        std::cout << *b_ << std::endl;
        std::cout << *a_ << std::endl;

        // testing functions
        auto exp_ = function::exp();

        var y_1(10);
        var y_2(1);
        var y_3 = y_1 + y_2;

        auto z_1 = exp_(y_1 + y_2);
        auto z_2 = exp_(y_3);
        // Obtains a pointer to var of which the value is 11
        auto w_1 = z_1.get_left();

        // attempt to get children of w;
        auto k_1 = w_1->get_left();
        auto l_1 = w_1->get_right();

        std::cout << *w_1 << std::endl;
        std::cout << *k_1 << std::endl;
        std::cout << *l_1 << std::endl;

        // Obtains a pointer to var of which the value is 11
        auto w_2 = z_2.get_left();

        // attempt to get children of w;
        auto k_2 = w_2->get_left();
        auto l_2 = w_2->get_right();

        std::cout << *w_2 << std::endl;
        std::cout << *k_2 << std::endl;
        std::cout << *l_2 << std::endl;
    }
}
