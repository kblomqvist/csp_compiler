/**
 * \mainpage
 * \author Kim Blomqvist, Petri Hodju, Tianyu Huang
 *
 * \section introduction INTRODUCTION
 * CSP is an abbreviation for CServer Page. Briefly CSP is a dynamic
 * markup language for creating web pages. The language
 * is baised on pretty strict XML and is common to JSP.
 * This CSP compiler compiles CSP markup language to C++ source code
 * that is then compiled to CGI-program by using g++ compiler.
 *
 * Web pages that are designed with CSP consist of files that
 * we call csp fragments. It's recommend to give .cspf suffix for
 * these files.
 *
 * <strong>A typical web page that is constructed by
 * CSP</strong>
 * \code
 * <csp:page contentType="text/html;charset=iso-8859-1" />
 * <csp:page import="course.hh" />
 * <csp:page import="student.hh" />
 *
 * <csp:include file="header.cspf" />
 *
 * <table>
 *     <caption>Test results</caption>
 *     <thead>
 *         <th>Student id</th>
 *         <th>Points</th>
 *     </thead>
 *     <csp:foreach var="Student stud" items="csp_course.students">
 *         <tr>
 *             <td>${stud.id}</td>
 *             <td>${stud.points}</td>
 *         </tr>
 *     </csp:foreach>
 * </table>
 *
 * <csp:include file="footer.cspf" />
 * \endcode
 *
 *
 *****************************************************************************
 * \section usage USAGE OF THE COMPILER
 * csp <sourcefile> [-o <output>]
 *
 * csp <sourcefile> generates out.cc source file and compiles out.cc to
 * out.csp file. Out.csp file is the executable file which is ready to use.
 *
 * In addition an output filename can be specified by using -o <output>
 * parameters. This specifies the output filename according to parameter.
 *
 * For example: csp index.cspf -o index.csp
 * This generates out.cc and index.csp from index.cspf.
 *
 *
 *****************************************************************************
 * \section markup STANDARD CSP ELEMENTS
 *
 * \subsection page The PAGE element
 * <strong>SYNOPSIS</strong>
 * \code
 * <csp:page [contentType] [errorPage] [import] [language] />
 * \endcode
 *
 * <strong>DESCRIPTION</strong>
 *
 * Page element is a directive for the CSP page. csp:page cannot
 * have a content.
 *
 * <strong>ATTRIBUTES</strong>
 *
 * - contentType, <small>optional</small>
 *   - Specifies the type of the content of the page.
 *   - By default <i>"text/html;charset=iso-8859-1"</i>.
 * - errorPage, <small>optional</small>
 *   - Takes a file name where web surfer is directed when error
 *   is occurred.
 * - import, <small>optional</small>
 *   - Includes the content of the C++ header file/files. Compare
 *   to C++ #include.
 * - language, <small>optional</small>
 *   - Tells the server what language the page is using.
 * .
 *
 *****************************************************************************
 * \subsection include The INCLUDE element
 * <strong>SYNOPSIS</strong>
 * \code
 * <csp:include [_file_] />
 * \endcode
 *
 * <strong>DESCRIPTION</strong>
 *
 * This tag includes the given file to the line where csp:include was invoked.
 * csp:include executes CSP compiler recursively so CSP markup
 * can also be included in includes. csp:include cannot have a
 * content.
 *
 * <strong>ATTRIBUTES</strong>
 * - <strong>file</strong>, <small>obligatory</small>
 *   - The file name that is liked to be included.
 * .
 *
 * <strong>ALIASES</strong>
 * - csp:i
 * .
 *
 *****************************************************************************
 * \subsection foreach The FOREACH element
 * <strong>SYNOPSIS</strong>
 * \code
 * <csp:foreach [_var_] [_items_]> ... </csp:foreach>
 * \endcode
 *
 * <strong>DESCRIPTION</strong>
 *
 * This tag implements the content for every given item.
 * Typically used for printing the rows of the table.
 *
 * <strong>ATTRIBUTES</strong>
 * - <strong>var</strong>, <small>obligatory</small>
 *   - Takes variable type and name separated by whitespace.
 * - <strong>items</strong>, <small>obligatory</small>
 *   - Takes a container that includes the variables.
 * .
 *
 * <strong>EXAMPLE</strong>
 * \code
 * <table>
 *     <caption>Test results</caption>
 *     <thead>
 *         <th>Student id</th>
 *         <th>Points</th>
 *     </thead>
 *     <csp:foreach var="Student stud" items="csp_course.students">
 *         <tr>
 *             <td>${stud.id}</td>
 *             <td>${stud.points}</td>
 *         </tr>
 *     </csp:foreach>
 * </table>
 * \endcode
 *
 *
 *****************************************************************************
 * \subsection if The IF element
 * <strong>SYNOPSIS</strong>
 * \code
 * <csp:if [_clause_]> ... </csp:if>
 * \endcode
 *
 * <strong>DESCRIPTION</strong>
 *
 * This tag implements if statement. If given conditional clause
 * is true the content of the tag is shown.
 *
 * <strong>ATTRIBUTES</strong>
 * - <strong>clause</strong>, <small>obligatory</small>
 *   - Defines the conditional clause.
 * .
 *
 * <strong>EXAMPLE</strong>
 * \code
 * <csp:if clause="number % 2">
 *   <span class="evenNumber">${number} is even</span>
 * </csp:if>
 * \endcode
 *
 *
 *****************************************************************************
 * \subsection else The ELSE element
 * <strong>SYNOPSIS</strong>
 * \code
 * <csp:else> ... </csp:else>
 * \endcode
 *
 * <strong>DESCRIPTION</strong>
 *
 * This tag implements else statement and it must straight follow
 * csp:if tag.
 *
 * <strong>ATTRIBUTES</strong>
 * - none
 * .
 *
 * <strong>EXAMPLE</strong>
 * \code
 * <csp:if clause="number % 2">
 *   <span class="evenNumber">${number} is even</span>
 * </csp:if>
 * <csp:else>
 *   <span class="oddNumber">${number} is odd</span>
 * </csp:else>
 * \endcode
 *
 *
 *****************************************************************************
 * \subsection cpp The CPP element
 * <strong>SYNOPSIS</strong>
 * \code
 * <csp:cpp> ... </csp:cpp>
 * \endcode
 * or
 * \code
 * <csp:cpp ... />
 * \endcode
 *
 * <strong>DESCRIPTION</strong>
 *
 * This tag takes any amount of valid C++ code. Class or function
 * declarations cannot be made with this tag.
 *
 * <strong>ATTRIBUTES</strong>
 * - none
 * .
 *
 * <strong>EXAMPLE</strong>
 * \code
 * <csp:page import="<iostream>" />
 * <csp:page import="hello.hh" />
 * <csp:cpp>
 *   std::cout << hello() << " !" << std::endl;
 * </csp:cpp>
 * \endcode
 *
 *
 *****************************************************************************
 * \subsection print The PRINT element
 * <strong>SYNOPSIS</strong>
 * \code
 * <csp:print ... />
 * \endcode
 * or
 * \code
 * <csp:print> ... </csp:print>
 * \endcode
 *
 * <strong>DESCRIPTION</strong>
 *
 * This tag takes anything and that will be converted to the string
 * that will be displayed. Note that objects that are liked to be
 * printed out have to be given in C++ form! Not in form
 * ${object}. You have to also take care to real escape quotation
 * marks and backslashes: \", \' and \\.
 *
 * <strong>ATTRIBUTES</strong>
 * - none
 * .
 *
 * <strong>ALIASES</strong>
 * - csp:p
 * .
 *
 * <strong>EXAMPLE</strong>
 * \code
 * <csp:cpp>std::string user("foobar");</csp:cpp>
 * <csp:print "Welcome " + user + " !" />
 * \endcode
 *
 *
 *****************************************************************************
 * \section vars CSP VARIABLES
 * It's easy to print variables in CSP page. If you have
 * initialized a variable named 'foo', you can print the value of
 * 'foo' anywhere in the page by using the following markup
 *
 * \code
 * ${foo}
 * \endcode
 *
 * There is one exception. You cannot use this variable in this
 * way in <csp:cpp> tag that takes C++ code as a content. In cpp
 * tag you have to use variables in the same way than you
 * would in C++, without dollar character and {} parentheses.
 *
 *
 *****************************************************************************
 * \section cgivars CGI ENVIRONMENT VARIABLES
 * Attributes and parameter given in URL, can be reached by using _GET
 * variable, which is a map<string, string>. The first value of map is
 * the name of parameter, and the second value is the value of parameter.
 *
 * The corresponding variable for POST-method is _POST, which is the same
 * as _GET variable, except the origin of data.
 */
