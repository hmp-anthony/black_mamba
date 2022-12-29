#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

class var {
private:
    double value_;
    std::shared_ptr<var> left_;
    std::shared_ptr<var> right_;

public:
    var(const var& v) : value_(v.value_), left_(v.left_), right_(v.right_) {}
    var(const double& v) : value_(v){};
    void set_left(std::shared_ptr<var> v) { left_ = v; }
    void set_right(std::shared_ptr<var> v) { right_ = v; }

    std::shared_ptr<var> get_left() { return left_; }
    std::shared_ptr<var> get_right() { return right_; }

    double value() const { return value_; }

    var operator=(const var& v) {
        value_ = v.value_;
        left_ = v.left_;
        right_ = v.right_;
        return *this;
    }

    friend var operator+(const var& l, const var& r) {
        var result(l.value_ + r.value_);
        result.left_ = std::make_shared<var>(l.value_);
        result.right_ = std::make_shared<var>(r.value_);
        return result;
    }

    friend var operator*(const var& l, const var& r) {
        var result(l.value_ * r.value_);
        result.left_ = std::make_shared<var>(l.value_);
        result.right_ = std::make_shared<var>(r.value_);
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
    // testing basic addition
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
