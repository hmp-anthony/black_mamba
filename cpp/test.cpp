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
    var(const double& v) : value_(v){};

    double value() const { return value_; }

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
        var r(std::exp(e.value()));

        return r;
    }
};
}  // namespace function

int main() {
    var a(1);
    var b(10);
    auto exp_ = function::exp();

    auto c = exp_(a + b);

    std::cout << c << std::endl;

}
