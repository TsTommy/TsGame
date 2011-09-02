#include "data.h"

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
#if 0
enum parser_state {
	SEEKING_KEY
	, READING_KEY
	, SEEKING_EQUALS_OR_BRACE
	, SEEKING_VALUE
	, READING_VALUE
	, READING_MULTI_COMMENT
};
#endif

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

void parse(std::istream& in)
{
	std::stringstream key_buffer;
	std::stringstream value_buffer;
	parser_state mode;
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
				else
					assert(("data::init(): Unexpected character",false));
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
					child_[key_buffer.str()] = new data(in);
					key_buffer.str(std::string());
					mode = SEEKING_KEY;
				}
				else
					assert(("data::init(): Unexpected character",false));
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
					assert(("data::init(): Unexpected character",false));
				break;
			case SEEKING_VALUE:
				if(curr == '\"')
					mode = READING_VALUE;
				else if(is_whitespace(curr))
					(void) 0; //ignore whitespace
				else
					assert(("data::init(): Unexpected character",false));
				break;
			case READING_VALUE:
				if(curr == '\"')
				{
					char next = in.get();

					if(in.good() && next == '\"')
						value_buffer << '\"'; //double double quote is literal double quote
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
				assert(("data::init(): Unexpected end of input stream",false));
		}
	}
}

} //namespace
