
#include "neshta.h"

#include <unistd.h>
#include <dirent.h> 



struct TVnode* PURVI_TV=NULL;




struct TVnode{
	char*id;
	char*model;
	char*proizvoditel;
	float cena;
	int godina;
	struct TVnode*next;
};





int isfile(char*dir){
	return access(dir, F_OK)!=-1;
}


char* tvdir(char*nomer){
	char*dir = new_str("televizori/");
	append_str_str(&dir, nomer);
	return dir;
}




char* read_model(char*nomer){
	char*dir = tvdir(nomer);
	
	FILE*f = fopen(dir, "rb");
	if(f==NULL)error2("Ne moga da otvorq faila za televozora: ", nomer);
	
	char*line=NULL;
	size_t size=0;
	
	getline(&line, &size, f); //model
	//printf("Model: %s\n", line);
	
	fclose(f);
	
	line[strlen(line)-1] = 0;
	return line;
}

char*read_proizvoditel(char*nomer){
	char*dir = tvdir(nomer);
	
	FILE*f = fopen(dir, "rb");
	if(f==NULL)error2("Ne moga da otvorq faila za televozora: ", nomer);
	
	char*line=NULL;
	size_t size=0;
	
	getline(&line, &size, f); //model
	//printf("Model: %s\n", line);
	getline(&line, &size, f); //proizvoditel
	
	fclose(f);
	
	line[strlen(line)-1] = 0;
	return line;
}



float read_cena(char*nomer){
	char*dir = tvdir(nomer);
	
	FILE*f = fopen(dir, "rb");
	if(f==NULL)error2("Ne moga da otvorq faila za televozora: ", nomer);
	
	char*line=NULL;
	size_t size=0;
	
	getline(&line, &size, f); //model
	//printf("Model: %s\n", line);
	getline(&line, &size, f); //proizvoditel
	//printf("Proizv: %s\n", line);
	getline(&line, &size, f); //cena
	//printf("Cena: %s\n", line);
	
	fclose(f);
	
	line[strlen(line)-1] = 0;
	return atof(line);
}


int read_godina(char*nomer){
	char*dir = tvdir(nomer);
	
	FILE*f = fopen(dir, "rb");
	if(f==NULL)error2("Ne moga da otvorq faila za televozora: ", nomer);
	
	char*line=NULL;
	size_t size=0;
	
	getline(&line, &size, f); //model
	//printf("Model: %s\n", line);
	getline(&line, &size, f); //proizvoditel
	//printf("Proizv: %s\n", line);
	getline(&line, &size, f); //cena
	//printf("Cena: %s\n", line);
	getline(&line, &size, f); //godina
	
	fclose(f);
	
	line[strlen(line)-1] = 0;
	return atoi(line);
}



int set_cena(char*nomer, float nova_cena){
	char*dir = tvdir(nomer);
	
	FILE*f = fopen(dir, "rb");
	if(f==NULL)error2("Ne moga da otvorq faila za televozora: ", nomer);
	
	char*new_data = new_str("");
	
	char*line=NULL;
	size_t size=0;
	
	getline(&line, &size, f); //model
	append_str_str(&new_data, line);
	//append_str_char(&new_data, '\n');

	getline(&line, &size, f); //proizvoditel
	append_str_str(&new_data, line);
	//append_str_char(&new_data, '\n');
	
	getline(&line, &size, f); //cena
	
	
	char cena_str[12];
	
	int len = 0;
	float tmp = nova_cena;
	while(tmp > 1){
		len++;
		tmp /= 10;
	}
	/*
	tmp = nova_cena - ( (int)nova_cena );
	printf("%f\n", tmp);
	while(tmp < 1){
		len++;
		tmp *= 10;
	}*/
	
	gcvt(nova_cena, len+2, cena_str);
	//printf("%d %s\n", len+2, cena_str);
	
	append_str_str(&new_data, cena_str);//NDASDUASHDUHAS
	append_str_char(&new_data, '\n');
	
	getline(&line, &size, f); //godina
	append_str_str(&new_data, line);
	append_str_char(&new_data, '\n');
	
	fclose(f);
	
	
	
	f= fopen(dir, "wb");
	if(f==NULL)error2("Ne moga da otvorq faila ", dir);
	free(dir);
	
	fprintf(f, "%s", new_data);
	free(new_data);
	
	fclose(f);
	
	
	struct TVnode* next;
	next = PURVI_TV;
	for(;;){
		if(next==NULL)break;
		if(strcmp(next->id, nomer)==0){
			next->cena = nova_cena;
		}
		next = next->next;
	}
	
	
}








void DOBAVQNE_NA_TELEVIZOR(char*nomer, char*model, char*proizvoditel, float cena, int godina){
	//char*f_name = new_str("televizori/");
	//append_str_str(&f_name, nomer);
	char*f_name = tvdir(nomer);
	
	//if(access(f_name, F_OK)!=-1){
	if(isfile(f_name)){
		char*inp = input("Televizor s tova ime veche sushtestvuva, iskash li da overwrite-nesh? (y): ");
		if(strcmp(inp, "y")!=0){
			echo("Abroting...");
			return;
		}
	}
	
	FILE*f= fopen(f_name, "wb");
	if(f==NULL)error2("Ne moga da otvorq faila ", f_name);
	free(f_name);
	
	fprintf(f, "%s\n%s\n%f\n%d\n", model, proizvoditel, cena, godina);
	
	fclose(f);
	
	
	struct TVnode* sledvasht = NULL;
	sledvasht = (struct TVnode*)malloc(sizeof(struct TVnode));
	sledvasht->next = NULL;
	
	sledvasht->id = nomer;
	sledvasht->model = model;
	sledvasht->proizvoditel = proizvoditel;
	sledvasht->cena = cena;
	sledvasht->godina = godina;
	
	
	if(PURVI_TV==NULL){
		PURVI_TV = sledvasht;
		return;
	}
	
	struct TVnode* next;
	next = PURVI_TV;
	struct TVnode* prev;
	prev = PURVI_TV;
	
	for(;;){
		if(next==NULL)break;
		prev = next;
		next = next->next;
	}
	//echo("3");
	//printf("ID: %s\n", prev->id);
	prev->next = sledvasht;
	//echo("4");
}









int strint_GREATER_strint(char*str1, char*str2){
	int len1;
	for(unsigned int i=0; i<strlen(str1); i++){
		if(str1[i] == '0')continue;
		len1 = strlen(str1) - i;
		break;
	}
	
	int len2;
	for(unsigned int i=0; i<strlen(str2); i++){
		if(str2[i] == '0')continue;
		len2 = strlen(str2) - i;
		break;
	}
	
	//printf("%d %d\n", len1, len2);
	
	if(len1 > len2)return 1;
	if(len1 < len2)return 0;
	
	for(; len1 > 0; len1--){
		int ind = strlen(str1) - len1;
		
		//printf("num1: %c   num2: %c\n", str1[ind], str2[ind]);
		int num1 = char_to_int(str1[ind]);
		int num2 = char_to_int(str2[ind]);
		if(num1 > num2)return 1;
		if(num1 < num2)return 0;
	}
	return 0;
}









char* nomerTV_input(){
	
	for(;;){
		char*inp = input("Unikalen nomer: ");
		if(0==is_str_int(inp)){
			echo("Nevalided nomer");
			free(inp);
			continue;
		}
		if( strint_GREATER_strint(inp, "999999999999") ){
			echo("Nomera trqbva da e nai-mnogo 12-cifren");
			free(inp);
			continue;
		}

		char*unikalen_nomer = new_str("");
		unsigned int i;
		for(i=0; i<strlen(inp); i++){
			if(inp[i]!='0')break;
		}
		for(; i<strlen(inp); i++){
			append_str_char(&unikalen_nomer, inp[i]);
		}
		free(inp);
		return unikalen_nomer;
	}
	
}


void dobavqne_na_nov_televizor(){
	char*unikalen_nomer = nomerTV_input();
	/*
	for(;;){
		char*inp = input("Unikalen nomer: ");
		if(0==is_str_int(inp)){
			echo("Nevalided nomer");
			free(inp);
			continue;
		}
		if( strint_GREATER_strint(inp, "999999999999") ){
			echo("Nomera trqbva da e nai-mnogo 12-cifren");
			free(inp);
			continue;
		}

		//unikalen_nomer = inp;
		unikalen_nomer = new_str("");
		unsigned int i;
		for(i=0; i<strlen(inp); i++){
			if(inp[i]!='0')break;
		}
		for(; i<strlen(inp); i++){
			append_str_char(&unikalen_nomer, inp[i]);
		}
		free(inp);
		break;
	}
	*/
	
	
	char*model;
	for(;;){
		char*inp = input("Model: ");
		if(strlen(inp) > 20){
			echo("Modela trqbva da e do 20 cifri");
			free(inp);
			continue;
		}
		model = inp;
		break;
	}
	
	char*proizvoditel;
	for(;;){
		char*inp = input("Proizvoditel: ");
		if(strlen(inp) > 20){
			echo("Proizvoditelq trqbva da e do 20 cifri");
			free(inp);
			continue;
		}
		proizvoditel = inp;
		break;
	}
	
	float cena = float_input("Cena: ");
	
	int godina_na_proizvodstvo = int_input("Godina na proizvodstvo: ");
	
	/*
	printf("Nomera: %s\n", unikalen_nomer);
	printf("Modela: %s\n", model);
	printf("Proizvoditel: %s\n", proizvoditel);
	printf("Cena: %f\n", cena);
	printf("Godina: %d\n", godina_na_proizvodstvo);
	*/
	
	DOBAVQNE_NA_TELEVIZOR(unikalen_nomer, model, proizvoditel, cena, godina_na_proizvodstvo);
	
	free(unikalen_nomer);
}

void maksimalna_cena(){
	
	float max_cena = -1;
	
	struct TVnode* next;
	next = PURVI_TV;
	for(;;){
		if(next==NULL)break;
		if(next->cena > max_cena){
			max_cena = next->cena;
		}
		next = next->next;
	}
	
	if(max_cena==-1){
		echo("Nqma televizori proizvedeni sled 2007");
		return;
	}
	printf("Nai skupiq televizor ot 2007 struva: %.2f\n", max_cena);
}

void iztrivane_na_dannite(){
	
	char*proizvoditel = input("Proizvoditel: ");
	
	/*
	struct dirent *de;
	DIR *dr = opendir("televizori"); 
	if (dr == NULL)error("Ne moga da otvorq papkata s televizorite");
	
	while( (de=readdir(dr)) != NULL){
		char*nomer = de -> d_name;
		if( strcmp(nomer,".")==0 || strcmp(nomer,"..")==0)continue;
		//printf("%s\n", nomer);
		char*proiz = get_proizvoditel(nomer);
		//printf("%s\n", proiz);
		//printf("%d\n", strcmp(proizvoditel, proiz));
		if(strcmp(proizvoditel, proiz)==0){
			printf("Iztrivam televizor %s\n", nomer);
			
			char*dir = new_str("televizori/");
			append_str_str(&dir, nomer);
			
			int res = remove(dir);
			if(res!=0)echo("Ne mojah da go iztriq");
			free(dir);
		}
	}
	
	free(proizvoditel);
	* */
	
	struct TVnode* next;
	next = PURVI_TV;
	struct TVnode* prev;
	prev = NULL;
	for(;;){
		if(next==NULL)break;
		if(strcmp(next->proizvoditel, proizvoditel)==0){
			char*nomer = next->id;
			printf("Iztrivam televizor %s\n", nomer);
			
			char*dir = new_str("televizori/");
			append_str_str(&dir, nomer);
			
			int res = remove(dir);
			if(res!=0)echo("Ne mojah da go iztriq");
			free(dir);
			
			prev->next = next->next;
			free(next);
			next = prev;
		}
		prev = next;
		next = next->next;
	}
	
	
}

void aktualizaciq_na_cena(){
	
	char*nomer = nomerTV_input();
	char*dir = tvdir(nomer);
	if(isfile(dir)==0){
		echo("Nqma televizor s takuv nomer");
		return;
	}
	
	float cena = float_input("Nova cena: ");
	
	set_cena(nomer, cena);
	
}





void dinamichno_zarejdane(){
	
	struct TVnode* nachalo = NULL;
	nachalo = (struct TVnode*)malloc(sizeof(struct TVnode));
	nachalo->next = NULL;
	
	struct TVnode* posleden = nachalo;
	
	
	struct dirent *de;
	DIR *dr = opendir("televizori"); 
	if (dr == NULL)error("Ne moga da otvorq papkata s televizorite");
	
	while( (de=readdir(dr)) != NULL){
		char*nomer = de -> d_name;
		if( strcmp(nomer,".")==0 || strcmp(nomer,"..")==0)continue;
		
		struct TVnode* sledvasht = NULL;
		sledvasht = (struct TVnode*)malloc(sizeof(struct TVnode));
		sledvasht->next = NULL;
		
		sledvasht->id = nomer;
		sledvasht->model = read_model(nomer);
		sledvasht->proizvoditel = read_proizvoditel(nomer);
		sledvasht->cena = read_cena(nomer);
		sledvasht->godina = read_godina(nomer);
		posleden->next = sledvasht;
		
		posleden = sledvasht;
		
	}
	
	if(nachalo->next == NULL){
		return;
	}
	
	struct TVnode* item;
	item = nachalo->next;
	PURVI_TV = item;
	
	for(;;){
		
		echo("");
		printf("ID: %s\n", item->id);
		printf("Model: %s\n", item->model);
		printf("Proizvoditel: %s\n", item->proizvoditel);
		printf("Cena: %.2f\n", item->cena);
		printf("Godina na proizvodstvo: %d\n", item->godina);
		
		item = item->next;
		if(item==NULL){
			break;
		}
	}
	
}



void main(){
	
	dinamichno_zarejdane();
	
	for(;;){
		echo("");
		echo("1/ Dobavqne na nov televizor");//gotovo
		echo("2/ Maksimalna cena na televizorite proizvedeni sled 2007");//gotovo .2 !!
		echo("3/ Iztrivane na dannite za vsichki televizori ot daden proizvoditel");//gotovo
		echo("4/ Aktualizaciq na cena, po nomer");//gotovo
		//echo("5/ Dinamichno zarejdane na dannite");
		
		int izbor = int_input("Izberi opciq: ");
		
		switch(izbor){
			case 1: 
				dobavqne_na_nov_televizor();
				break;
			case 2: 
				maksimalna_cena();
				break;
			case 3: 
				iztrivane_na_dannite();
				break;
			case 4: 
				aktualizaciq_na_cena();
				break;
			//case 5:
			//	dinamichno_zarejdane();
			//	break;
			default: printf("Nevaliden izbor: %d\n", izbor);
		}
		
	}
	
}



