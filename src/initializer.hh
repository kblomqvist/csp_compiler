// initGET and decodeURL works


#include <string>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <map>


namespace CSPInit
{

	class Initializer
	{
public:
		Initializer()
		{
		}

		~Initializer()
		{
		}


		//
		// Initializes GET map
		//
		void initGET(std::map<std::string, std::string> &input)
		{
			// Lets copy the environment variable
			char* query_string = getenv("QUERY_STRING");

			// Empty
			if(query_string == NULL)
			{
				return;
			}



			std::string temp;
			std::string variableName;
			std::string variableValue;


			// Loop through
			while(true)
			{
				// When reaching the end, break the loop
				if(*query_string == '\0')
				{
					break;
				}


				// When we are getting next variable
				else if(*query_string == '&')
				{
					if(variableName.size())
					{
						variableValue.clear();
						variableValue = decodeURL(temp);
						input[decodeURL(variableName)] = variableValue;
					}
					variableName.clear();
					temp.clear();
				}

				// When we are getting equal sign
				else if(*query_string == '=')
				{
					variableName = decodeURL(temp);
					temp.clear();
				}


				// Just copying letters
				else
				{
					temp += (*query_string);
				}


				// Increment position
				query_string++;
			}

			// Go through the last variable
			if(variableName.size())
			{
				variableValue.clear();
				variableValue = decodeURL(temp);
				input[decodeURL(variableName)] = variableValue;
			}
		}


		//
		// Initializes POST map
		//
		void initPOST(std::map<std::string, std::string> &input)
		{
			std::string varKey, varValue;
			std::string *tmp = &varKey;
			char *inputBuffer;
		  	unsigned int contentSize;
			char *buffer;


			// Get length
			char *strContentSize = getenv("CONTENT_LENGTH");
			// If none
			if(strContentSize == NULL)
			{
				return;
			}

			contentSize = atoi(strContentSize);
			// If none
			if(contentSize == 0)
			{
				return;
			}
	

			// Allocate buffer
			try
			{
				buffer = new char[contentSize*sizeof(char)];
			}
			catch (std::bad_alloc err)
			{
				return;
			}


			// Read the stdin into buffer and check if size matches
			if(fread(buffer, sizeof(char), contentSize, stdin) != (unsigned int)contentSize)
			{
				return;
			}


			// Add a \0 at the end as an EOF mark
			*(buffer+contentSize) = '\0';
			inputBuffer = buffer;
			// Do the parsing
			while(*inputBuffer != '\0')
			{
				if(*inputBuffer == '&')
				{
					if(varKey != "")
					{
						input[decodeURL(varKey)] = decodeURL(varValue);
					}

					varKey.clear();
					varValue.clear();
					tmp = &varKey;
				}
				else if(*inputBuffer == '=')
				{
					tmp = &varValue;
				}
				else
				{
					(*tmp) += (*inputBuffer);
				}
				inputBuffer++;
			}

			if(varKey != "")
			{
				input[decodeURL(varKey)] = decodeURL(varValue);
				varKey.clear();
				varValue.clear();
			}
		}


private:

		//
		// Decodes an URL encoded string
		//
		std::string decodeURL(std::string input)
		{
			std::string retval;

			for(int i=0;i<input.size();i++)
			{
				// Decoding a hex to char
				if(input[i] == '%')
				{
					// Two numbers/letters after % is required
					if((i+2) < input.size())
					{
						// Lets make hexadecimals to convert
						std::string chartmp;
						chartmp += input[i+1];
						chartmp += input[i+2];

						// Convert
						std::istringstream iss(chartmp);
						int chartmp2;
						iss >> std::hex >> chartmp2;


						retval += (char)chartmp2;
						i += 2;
					}
					else
					{
						// Error logic on URL-decoding...
						// Lets do none. Just copy the chars like they were normal characters.
						retval += input[i];
					}
				}

				// Handling + letter, which means space
				else if(input[i] == '+')
				{
					retval += ' ';
				}

				// Normal char
				else
				{
					retval += input[i];
				}
			}

			return retval;
		}

	};
}
