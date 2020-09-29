
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h> 

// win
typedef unsigned int uint;

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

int isfile(char*dir){
	return access(dir, F_OK)!=-1;
}



// converter

int is_char_int(char c){
	switch(c){
		case '0'...'9': return 1;
	}
	return 0;
}

int is_str_int(char*str){
	unsigned int i=0;
	if(str[0]=='-')i=1;
	for(; i<strlen(str); i++){
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

float str_to_float(char*str){
	return atof(str);
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

void append_str_uint(char**p_str, uint num){
	char buff[20];
	sprintf(buff,"%u",num);
	append_str_str(p_str, buff);
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

// copy

char*copy_str(char*str_to_copy){
	char*new = new_str("");
	append_str_str(&new, str_to_copy);
	return new;
}




// input

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

char*input_capital_50(char*prompt){
	for(;;){
		char*test = input(prompt);
		if(strlen(test) > 50){
			free(test);
			continue;
		}
		int failed = 0;
		for(int ind=0; ind<strlen(test); ind++){
			char c = test[ind];
			if( c>='A' && c<='Z' ){}
			else{
				failed = 1;
				break;
			}
		}
		if(failed){
			free(test);
			continue;
		}
		return test;
	}
}

char* input_date(char*prompt){//#...
	for(;;){
		char*test = input(prompt);
		if(strlen(test)!=10){
			echo("Greshen format, greshna duljina");
			free(test);continue;
		}
		if( (test[4]=='.' && test[7]=='.')==0 ){
			echo("Greshen format, nqma tochki kudeto trqbva");
			free(test);continue;
		}
		if( ( is_char_int(test[0])&&is_char_int(test[1])&&is_char_int(test[2])&&is_char_int(test[3]) )==0 ){
			echo("Greshen format, godinata trqbva da e cifra");
			free(test);continue;
		}
		if( ( is_char_int(test[5])&&is_char_int(test[6]) )==0 ){
			echo("Greshen format, meseca trqbva da e cifra");
			free(test);continue;
		}
		if( (char_to_int(test[5])>3) || (char_to_int(test[5])==3 && char_to_int(test[6])>1) ){
			echo("Greshen format, takuv den ot meseca nqma");
			free(test);continue;
		}
		if( (char_to_int(test[8])>1) || (char_to_int(test[8])==1 && char_to_int(test[9])>2) ){
			echo("Greshen format, takuv mesec nqma");
			free(test);continue;
		}
		return test;
	}
}

int int_input(char*prompt){
	for(;;){
		char*inp= input(prompt);
		if(is_str_int(inp)==1){
			int res= str_to_int(inp);
			free(inp);
			return res;
		}
		free(inp);
		echo("Trqbva da vuvedesh cqlo chislo");
	}
}

uint uint_input(char*prompt){
	for(;;){
		int test_int = int_input(prompt);
		if(test_int < 0){
			echo("Trqbva da vuvedesh chislo, po-glqmo ili ravno na 0");
			continue;
		}
		return (unsigned int)test_int;
	}
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
		
		return atof(inp);
		
	}
}

float ufloat_input(char*prompt){
	for(;;){
		float test_float = float_input(prompt);
		if(test_float < 0){
			echo("Trqbva da e po-golqmo ili ravno na 0");
			continue;
		}
		return test_float;
	}
}


// file writing

void write_int(FILE*f, int num){
	fwrite(&num, sizeof(num), 1, f);
}

void write_uint(FILE*f, uint num){
	fwrite(&num, sizeof(num), 1, f);
}

void write_float(FILE*f, float num){
	fwrite(&num, sizeof(num), 1, f);
}

void write_str(FILE*f, char*str){
	int len = strlen(str)+1;
	//fwrite(&len, sizeof(len), 1, f);
	write_int(f, len);
	fwrite(str, sizeof(char), len, f);
}

// file reading

int read_int(FILE*f){
	int num=0;
	fread(&num, sizeof(int), 1, f);
	return num;
}

uint read_uint(FILE*f){
	uint num = 0;
	fread(&num, sizeof(uint), 1, f);
	return num;
}

float read_float(FILE*f){
	float num = 0.0;
	fread(&num, sizeof(float), 1, f);
	return num;
}

char*read_str(FILE*f){
	int len = read_int(f);
	char*str = malloc(sizeof(char)*len);
	fread(str, sizeof(char), len, f);
	return str;
}
