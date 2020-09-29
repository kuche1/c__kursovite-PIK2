
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// errors

void error_msg(){
	printf("ERROR: ");
}
void error_exit(){
	exit(1);
}

void error(char*info){
	error_msg();
	printf("%s\n", info);
	error_exit();
}

void error2(char*info1, char*info2){
	error_msg();
	printf("%s%s\n", info1, info2);
	error_exit();
}

void error2_str_char(char*info1, char info2){
	error_msg();
	printf("%s%c\n", info1, info2);
	error_exit();
}




// stuff

void echo(char*text){
	printf("%s\n", text);
}





// converter

int is_char_int(char c){
	switch(c){
		case '0'...'9': return 1;
	}
	return 0;
}

int is_str_int(char*str){
	for(unsigned int i=0; i<strlen(str); i++){
		if(is_char_int(str[i])==0)return 0;
	}
	return 1;
}

int char_to_int(char c){
	switch(c){
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
	}
	error2_str_char("cant conver character to integer: ", c);
}

int str_to_int(char*str){
	if(strlen(str)==0)error("cant convert an empty string to integer");
	
	unsigned int i=0;
	
	int negative= 0;
	if(str[0]=='-'){
		i++;
		negative= 1;
		if(strlen(str)==1)error("cant convert a dash string (\"-\") to integer");
	}
	
	int current_value= 0;
	
	for(; i<strlen(str); i++){
		current_value*= 10;
		if(current_value < 0)error("integer overflow");
		
		int c_val= char_to_int(str[i]);
		current_value += c_val;
		if(current_value < 0)error("integer overflow");
		
	}
	
	if(negative)return -1*current_value;
	return current_value;
}





// new

char*new_str(char*value){
	char*obj= malloc(sizeof(char)*(1+strlen(value)));
	if(obj==NULL)error("cant use malloc to create a new string");
	for(unsigned int i=0; i<=strlen(value); i++){
		obj[i]= value[i];
	}
	return obj;
}

// append str

void append_str_char(char**p_str, char c){
	int size= strlen(*p_str);
	*p_str= realloc(*p_str, sizeof(char)*(size+2));
	(*p_str)[size]= c;
	(*p_str)[size+1]= '\0';
}

void append_str_str(char**p_str1, char*str2){
	for(unsigned int i=0; i<strlen(str2); i++){
		append_str_char(p_str1, str2[i]);
	}
}


// head tail

char*head_str_int(char*str, int chop_point){
	if(chop_point >= strlen(str))error("head_str_int: chop point bigger than string length");
	
	char*res= new_str("");
	for(unsigned int i=0; i<chop_point; i++){
		append_str_char(&res, str[i]);
	}
	return res;
}

char*tail_str_int(char*str, int chop_point){
	if(chop_point >= strlen(str))error("tail_str_int: chop point bigger than string length");
	
	char*res= new_str("");
	for(unsigned int i=chop_point; i<strlen(str); i++){
		append_str_char(&res, str[i]);
	}
	return res;
}




// console input

char*input(char*prompt){
	printf("%s",prompt);
	
	char*res= new_str("");
	for(;;){
		char c= getchar();
		if(c=='\n')break;
		append_str_char(&res, c);
	}
	return res;
}

int int_input(char*prompt){
	char*inp= input(prompt);
	int res= str_to_int(inp);
	free(inp);
	return res;
}


float float_input(char*text){
	
	for(;;){
		char*inp = input(text);
		if(is_str_int(inp)==1){
			float ret = (float)str_to_int(inp);
			free(inp);
			return ret;
		}
		int separator=-1;
		int count = 0;
		for(unsigned int i=0; i<strlen(inp); i++){
			if(inp[i] == '.'){
				separator = i;
				count++;
			}
		}
		if(separator==-1 || count>1){
			free(inp);
			echo("Ne si vuvel ne cqlo chislo");
			continue;
		}
		
		// return atof(inp);
		char*head = head_str_int(inp, separator);
		char*tail = tail_str_int(inp, separator+1);
		free(inp);
		
		if(0==is_str_int(head)){
			echo("Ne si vuvel chislo");
			continue;
		}
		int head_value = str_to_int(head);
		free(head);
		
		if(0==is_str_int(tail)){
			echo("Ne si vuvel chislo");
			continue;
		}
		int tail_value = str_to_int(tail);
		free(tail);
		
		float value = (float)head_value;
		float tail_float = (float)tail_value;
		while(tail_float > 1){
			tail_float /= (float)10;
		}
		
		value += tail_float;
		
		return value;
		
	}
}


