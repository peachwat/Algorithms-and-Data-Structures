#pragma once
using namespace std;

enum class Tokens {
    space,
	integer, 
	comma,
	dot,
	open, // "("
	close, // ")"
	pls, //plus
	mns, //minus
	dz, //dzielenie
	mn, //mnozenie
	min,
	max,
	n, //negacja
	iff //if
};

ostream& operator<<(std::ostream& os, const Tokens& token) {
    switch (token) {
    case Tokens::space:
        break;
    case Tokens::integer:
        break;
    case Tokens::comma:
        break;
    case Tokens::dot:
        break;
    case Tokens::open:
        break;
    case Tokens::close:
        break;
    case Tokens::pls:
        os << "+ ";
        break;
    case Tokens::mns:
        os << "- ";
        break;
    case Tokens::dz:
        os << "/ ";
        break;
    case Tokens::mn:
        os << "* ";
        break;
    case Tokens::min:
        os << "MIN";
        break;
    case Tokens::max:
        os << "MAX";
        break;
    case Tokens::n:
        os << "N ";
        break;
    case Tokens::iff:
        os << "IF ";
        break;
    }
    return os;
}
