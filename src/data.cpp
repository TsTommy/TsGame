#include "data.h"

#include <fstream>
#include "foreach.h"

data::data()
		: value_()
		, child_()
	{}

data::data(std::istream& file)
		: value_()
		, child_()
{
	init(file);
}

data::data(const char* filename)
		: value_()
		, child_()
{
	init(filename);
}

data::data(std::string const& filename)
		: value_()
		, child_()
{
	init(filename);
}

std::ostream& data::print(std::ostream& out) const
{
	foreach(values_t::value_type const& pair, value_)
	{
		out << pair.first << "=\"";
		foreach(char const& c, pair.second)
		{
			if(c!='\"')
				out << c;
			else //gotta escape it
				out << c << c;
		}
		out << '\"';
	}
	foreach(children_t::value_type const& pair, child_)
		out << pair.first <<"{"<< *pair.second <<"}";
	return out;
}

//forward declaration
namespace { void parse(std::istream& in, data::values_t& out1, data::children_t& out2); }

/*private*/
void data::init(std::istream& in)
{
	parse(in,value_,child_);
}

/*private*/
void data::init(char const* filename)
{
	std::ifstream file(filename);
	init(file);
	file.close();
}

/*private*/
void data::init(std::string const& filename)
{
	init(filename.c_str());
}

//===========
//data parser
namespace {
enum parser_state {
	SEEKING_KEY
	, READING_KEY
	, SEEKING_EQUALS_OR_BRACE
	, SEEKING_VALUE
	, READING_VALUE
	, READING_MULTI_COMMENT
};

inline bool is_whitespace(char x)
{
	switch(x)
	{
	case '\0': //fallthrough
	case '\t': //fallthrough
	case '\n': //fallthrough
	case '\r': //fallthrough
	case ' ':
		return true; //implicit break
	default:
		return false; //implicit break
	}
}

inline bool is_identifier_char(char x)
	{return (x>='a'&&x<='z') || (x>='A'&&x<='Z') || (x=='_');}

void parse(std::istream& in, data::values_t& value_, data::children_t& child_)
{
	std::stringstream key_buffer;
	std::stringstream value_buffer;
	parser_state mode = SEEKING_KEY;
	char curr;
	while(in.good())
	{
		curr = in.get();
		if(in.good())
		{
			switch(mode)
			{
			case SEEKING_KEY:
				if(is_identifier_char(curr))
				{
					key_buffer << curr;
					mode = READING_KEY;
				}
				else if(is_whitespace(curr))
					(void) 0; //ignore whitespace
				else if(curr == '}')
					return;
				else
					throw "data::init(): Unexpected character";
				break;
			case READING_KEY:
				if(is_identifier_char(curr))
					key_buffer << curr;
				else if(curr == '=')
					mode = SEEKING_VALUE;
				else if(is_whitespace(curr))
					mode = SEEKING_EQUALS_OR_BRACE;
				else if(curr == '{')
				{
					boost::shared_ptr<data> child(new data(in));
					child_.insert(std::make_pair(key_buffer.str(),child));
					key_buffer.str(std::string());
					mode = SEEKING_KEY;
				}
				else
					throw "data::init(): Unexpected character";
				break;
			case SEEKING_EQUALS_OR_BRACE:
				if(curr == '=')
					mode = SEEKING_VALUE;
				else if(is_whitespace(curr))
					(void) 0; //ignore whitespace
				else if(curr == '{')
				{
					child_.insert(std::make_pair(key_buffer.str(),new data(in)));
					key_buffer.str(std::string());
					mode = SEEKING_KEY;
				}
				else
					throw "data::init(): Unexpected character";
				break;
			case SEEKING_VALUE:
				if(curr == '\"')
					mode = READING_VALUE;
				else if(is_whitespace(curr))
					(void) 0; //ignore whitespace
				else
					throw "data::init(): Unexpected character";
				break;
			case READING_VALUE:
				if(curr == '\"')
				{
					char next = in.peek();

					if(in.good() && next == '\"')
					{
						value_buffer << '\"'; //double double quote is literal double quote
						if(!in.ignore())
							throw "I/O problem";
					}
					else
					{
						value_[key_buffer.str()] = value_buffer.str();
						key_buffer.str(std::string());
						value_buffer.str(std::string());
						mode = SEEKING_KEY;
					}
				}
				else
					value_buffer << curr;
				break;
			}
		}
		else //could not read another character
		{
			if(mode == SEEKING_KEY)
				break;
			else
				throw "data::init(): Unexpected end of input stream";
		}
	}
}

} //namespace
