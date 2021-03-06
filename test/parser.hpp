#include <boost/spirit/include/qi.hpp>
#include "grammar/skipper.hpp"

namespace {

namespace error {
struct unable_parse {};
}
template<
  template<class iterator, class skipper> class rule_t
, class iterator_t = std::string::const_iterator
, class skipper_t = sapphire::core::parser::skipper<iterator_t>
, class result_t = typename rule_t<iterator_t, skipper_t>::start_type::attr_type
>
struct tester_t {
    using result_type = result_t;
    static result_t parse(const std::string& input) {
        skipper_t skipper;
        rule_t<iterator_t,skipper_t> rule;
        result_t result;
        auto it = input.begin();
        const auto& end = input.end();
        try {
            if(!boost::spirit::qi::phrase_parse(it,end,rule,skipper,result) || it != end) {
                throw error::unable_parse();
            }
        } catch(...) {
            std::cout << "parse failed" << std::endl;
            std::cout << std::string(it,end) << std::endl;
            throw error::unable_parse();
            return {};
        }
        return result;
    }
};
}