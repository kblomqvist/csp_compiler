# CSP Compiler

CServer Page (CSP) is a dynamic markup language for creating web pages. The CSP markup is baised on XML and is common to JSP. This CSP compiler compiles the CSP markup language to C++ source code that is then compiled to CGI script by using g++ compiler.

Web pages that are designed with CSP consist of files that we call csp fragments. It's recommend to give `.cspf` suffix for these files.

A typical web page that is constructed by CSP:

```html
<csp:page contentType="text/html;charset=iso-8859-1" />
<csp:page import="course.hh" />
<csp:page import="student.hh" />

<csp:include file="header.cspf" />

<table>
    <caption>Test results</caption>
    <thead>
        <th>Student id</th>
        <th>Points</th>
    </thead>
    <csp:foreach var="Student stud" items="csp_course.students">
        <tr>
            <td>${stud.id}</td>
            <td>${stud.points}</td>
        </tr>
    </csp:foreach>
</table>

<csp:include file="footer.cspf" />
```

A command-line call `csp <sourcefile> [-o <output>]` generates `out.cc` source file and compiles it to `out.csp` file. The `out.csp` is the executable that can be run as a CGI script.
