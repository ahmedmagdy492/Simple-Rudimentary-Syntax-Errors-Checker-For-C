#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Stack.h"

#define FILE_SIZE 1024

void validate_syntax(char* str, int len);
char get_oppsite_char(char c);

main(int argc, char** argv) {
  if(argc != 2) {
    printf("Usage: %s <filename.c>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  FILE* file_handle = fopen(argv[1], "r+");
  size_t file_size;
  char *buffer = (char*)malloc(sizeof(char)*FILE_SIZE);
  int temp;
  memset(buffer, 0, FILE_SIZE);
  
  file_size = 0;
  temp = 0;

  while((temp = fread(buffer, 1, FILE_SIZE, file_handle)) != 0) {
    file_size += temp;
  }
  
  validate_syntax(buffer, file_size);

  fclose(file_handle);
}

void validate_syntax(char* str, int len) {
  int i, in_string, in_comment;

  in_string = 0, in_comment = 0;

	for (i = 0; i < len; ++i) {
	  if(in_comment == 0 && in_string == 0 && str[i] == '/' && str[i+1] == '*') {
	    in_comment = 1;
	  }
	  else if(in_comment == 1 && str[i] == '*' && str[i+1] == '\\') {
	    in_comment = 0;
	  }
	  if(in_comment == 0 && in_string == 0 && str[i] == '"') {
	    in_string = 1;
	  }
	  else if(in_string == 1 && str[i] == '"') {
	    in_string = 0;
	  }
	  if(in_string == 0 && in_comment == 0) {
	    if (str[i] == '{' || str[i] == '[' || str[i] == '(') {
	      push(str[i]);
	    }
	    else if (str[i] == '}' || str[i] == ']' || str[i] == ')') {
	      if(get_oppsite_char(str[i]) != peak()) {
		printf("missing the begining of %c\n", str[i]);
	      }
	      else {
		pop();
	      }
	    }
	  }
	}

	while(in_string == 0 && peak() != -1) {
	  printf("missing end of %c\n", peak());
	  pop();
	}

	if(in_string == 1) {
	  printf("missing the end double qoute of a string\n");
	}
}

char get_oppsite_char(char c) {
	if (c == '[') {
		return ']';
	}
	else if (c == '{') {
		return '}';
	}
	else if (c == '(') {
		return ')';
	}
	else if (c == ']') {
		return '[';
	}
	else if (c == '}') {
		return '{';
	}
	else if (c == ')') {
		return '(';
	}

	return c;
}
