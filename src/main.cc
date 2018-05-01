//#include "config.h"


#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <fstream>
#include <stack>
#include <stdlib.h>

#include "tagfactory.hh"
#include "parser.hh"


using namespace std;

int main(int argc, char** argv)
{
	char *sourcefile = 0;
     	char *outputfile = 0;
	bool param = false;
	char default_outputfile[] = "out.csp";
	bool recursive = false;
	
	if(argc == 2)
	{
	    sourcefile = argv[1];
	    outputfile = default_outputfile;	    
	}
	else if(argc == 3)
	{
	    if(string(argv[2]) != "-r")
	    {
		std::cout << "Usage: " << argv[0] << " <sourcefile> [-o <outputfile>] [-r] [-p <parameters>]" << std::endl;
		return 0;
	    }
	    sourcefile = argv[1];
	    recursive = true;
	}
	else if(argc == 4)
	{
	    if(string(argv[2]) != "-o")
	    {
		std::cout << "Usage: " << argv[0] << " <sourcefile> [-o <outputfile>] [-r] [-p <parameters>]" << std::endl;
		return 0;
	    }
	    sourcefile = argv[1];
	    outputfile = argv[3];
	}
	else if(argc == 5)
	{
	    if(string(argv[4]) == "-p")
	    {
		std::cout << "Usage: " << argv[0] << " <sourcefile> [-o <outputfile>] [-r] [-p <parameters>]" << std::endl;
		return 0;
	    }
	    if(string(argv[2]) != "-o" || string(argv[4]) != "-r")
	    {
		std::cout << "Usage: " << argv[0] << " <sourcefile> [-o <outputfile>] [-r] [-p <parameters>]" << std::endl;
		return 0;
	    }
	    sourcefile = argv[1];
	    outputfile = argv[3];
	    recursive = true;
	}

	else if(argc > 5)
	{
		if(string(argv[2]) != "-o" || string(argv[4]) != "-p")
		{
			std::cout << "Usage: " << argv[0] << " <sourcefile> [-o <outputfile>] [-r] [-p <parameters>]" << std::endl;
			return 0;
		}

		sourcefile = argv[1];
            	outputfile = argv[3];
		param = true;
	}

        std::ostringstream main_oss;
        std::ostringstream header_oss;
        std::ostringstream input_oss;

	// Initialization for source file

	header_oss << "#include <iostream>\n#include <map>\n#include <string>\n#include <stdlib.h>\n#include \"initializer.hh\"\n\n\n";
        main_oss << "int main()\n{\n" << "std::map<std::string, std::string> _GET;\nstd::map<std::string, std::string> _POST;\nCSPInit::Initializer csp_initializer;\ncsp_initializer.initGET(_GET);\n";
	main_oss << "csp_initializer.initPOST(_POST);\n\n\n";
	if(!recursive)
	    main_oss << "std::cout << \"Content-type: \" << _contentType << \"\\n\\n\";\n\n";


        ///////////////////////////////////////////////////////////////////////////////
        // Read the input
        std::ifstream inputstream(sourcefile, std::ios::binary);

	if(!inputstream.good())
	{
	    std::cout << "Cannot open file" << std::endl;
	    return 1;
	}
	
        // Do the stuff

        CSPParser parser;

    	std::string line;
    	std::string match;

	//
    	// stack for open tags
    	//
    	std::stack<Tag*> stack;

    	//
    	// We need root element to collect whole output
    	//
    	stack.push(TagFactory::produce("root"));

    	//
    	// Parse line by line
    	//
    	while(getline(inputstream, line, '\n'))
    	{
	    line += "\n";
	    //
	    // In case of partial tag matching we have to inject one space when
	    // concatenating lines to match string
	    //
	    match += " " + line;
	    parser.setParseLine(match);
	    
	    while(CSPParser::token t = parser.findNextToken())
	    {
		switch(t)
		{
		    case CSPParser::OPEN:
		    {
			//
			// push the just created tag to the stack
			//
			stack.push(parser.getTag());
			
			//
			// feed in attributres, either in string or map format
			//
			try
			{
			    stack.top()->open(parser.getAttributesAsString());
			}
			catch(exception& e)
			{
			    stack.top()->open(parser.getAttributesAsMap());
			}
			
			//
			// if the tag is inline type, pop it, close it and feed it to
			// the new current open tag right away.
			// However if tag is header type, then the tag is feeded directly
			// into header outputstream
			//
			if(parser.isTagInline())
			{
			    Tag* tag = stack.top();
			    tag->close();
			    stack.pop();
			    if(tag->isHeader())
			    {
				header_oss << *tag;
			    }
			    else
			    {
				*stack.top() << *tag;
			    }
			    delete tag;
			}
		    }
		    break;
		    
		    case CSPParser::CLOSE:
		    {
			//
			// Check that we are closing currently open tag
			//
			if(stack.top()->getTagName() != parser.getTagType())
			{
			    cout << "Mismatch in tag close: closing '" 
				 << parser.getTagType() << "'"
				 << " instead of expected '" 
				 << stack.top()->getTagName() << "'" << endl;
			}
			
			//
			// Pop and close it. Feed it to the new current open tag
			// If tag is header type, then feed it into header_oss
			//
			Tag* tag = stack.top();
			tag->close();
			stack.pop();
			if(tag->isHeader())
			{
			    header_oss << *tag;
			}
			else
			{
			    *stack.top() << *tag;
			}
			delete tag;
		    }
		    break;
		    
		    case CSPParser::TEXT:
		    {
			*stack.top() << parser.getText();
		    }
		    break;
		    
		    case CSPParser::EOL:
		    {
			match.clear();
		    }
		    break;
		    
		    case CSPParser::PARTIAL:
		    {
			//
			// Partial match. Take what is left to parse and 
			// continue to read next line of input
			//
			match = match.substr(parser.matchDone());
		    }
		    break;
	    	}
	    	if(t == CSPParser::EOL || t == CSPParser::PARTIAL)
		    break;
	    }
	}
	
    	//
    	// Finally pop the root tag and do postprocessing by
    	// transforming all ${...} tags to '" << ... << "'
    	//
	
    	Tag* tag = stack.top();
    	tag->close();
    	stack.pop();
	
	//
	// Feed the tag context into main outputstream
	//
    	main_oss << *tag;
   	main_oss << "std::cout << std::endl;\nreturn 0;\n}\n";
	
	
    	match = main_oss.str();
	
    	parser.setParseLine(match);
	
    	while(parser.findNextVariable())
    	{
	    regex::Match m = parser(0);
	    match.replace(m.beg, m.end - m.beg, "\" << " + parser[1] + " << \"");
	    parser.setParseLine(match);
    	}
	
    	delete tag;
	
	header_oss << "#ifndef _contentType\n#define _contentType \"text/html\"\n#endif\n\n";
							      
	//////////////////////////////////////////////////////////////////////////////
	// Write the temporary C++ source file and then compile it
        std::fstream filestream("out.cc", std::ios::out);
        filestream << header_oss.str() << "\n" << match << std::endl;
        filestream.close();
	
	std::string compileCmd("g++ out.cc ");

	if(param == true)
	{
		for(int x=5;x<argc;x++)
		{
			compileCmd += argv[x];
			compileCmd += " ";
		}
	}

	compileCmd += "-o ";
	compileCmd += outputfile;
	
	system(compileCmd.c_str());

        return 0;
	
}

