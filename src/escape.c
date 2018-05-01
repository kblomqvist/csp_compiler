#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Escapes " and ' chars in given string by backslashing them.
int escapeString(char **str) {
    /* allocate mem for escaped string */
    size_t L = strlen(*str);
    char *es = calloc(2*L+1, sizeof(char));

    /*
     * i = idx for *str
     * j = idx for es
     */
    size_t i = 0, j = 0;
    for(; (*str)[i]; i++) {
	if((*str)[i] == '\"' || (*str)[i] == '\'') {
	    es[j++] = '\\';
	    es[j++] = (*str)[i];
	}
	else
	    es[j++] = (*str)[i];
    }
 
    es = realloc(es, j+1); // free unused mem if any
    if(es) {
	char *tmp = *str;
	*str = es; // make *str to point escaped string
	free(tmp); // free tmp points to unescaped string
	return j-i; // return number of escaped chars
    }
    return -1; // error while reallocating es
}

int main() {
    char *s = "<span class=\"myNumber\">Number ${number} is</span>";
    char *str = malloc(strlen(s)+1);
    strcpy(str, s);

    // escape str that equals s
    int ret = escapeString(&str);
    if(!ret) {
	printf("Error\n");
    }

    printf("Given string: %s\n", s);
    printf("Escaped string: %s\n", str);
    printf("Number of escaped chars: %i\n", ret);

    free(str);
    return 0;
}

