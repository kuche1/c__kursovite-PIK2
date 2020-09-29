
#include "neshta.c"



struct Node{ //#...
	char*id;
	char*ime_avtor;
	char*ime_kartina;
	float cena;
	int godina;
	
	struct Node*next;
};

struct Node* PURVI=NULL;





/////////////////////////

char*node_dir_str(char*id){
	char*dir = new_str("nodes/");
	append_str_str(&dir, id);
	return dir;
}

/////////////////////////




void print_node(struct Node*node){ //#...
	printf("kod: %s \n", node->id);
	printf("ime avtor: %s \n", node->ime_avtor);
	printf("ime kartina: %s \n", node->ime_kartina);
	printf("cena: %f \n", node->cena);
	printf("godina: %d \n", node->godina);
}

char*kod_input(char*prompt){
	char*res = "";
	
	for(;;){
		res = new_str("");
		
		for(;;){
            printf("%s", prompt);

			char bukva = getchar();
			if(bukva=='\n'){
				echo("Nevalidno");
				continue;
			}
			if( (bukva >= 'a' && bukva <= 'z') || (bukva >= 'A' && bukva <= 'Z') ){
				append_str_char(&res, bukva);
				break;
			}
			echo("Nevalidno");
			continue;
		}
		
		int failed = 0;
		for(;;){
			char cifra = getchar();
			if( cifra=='\n' ){
				break;
			}
			if( cifra=='0' || cifra=='1' || cifra=='2' || cifra=='3' || cifra=='4' || cifra=='5' || cifra=='6' || cifra=='7' || cifra=='8' || cifra=='9'){
				append_str_char(&res, cifra);
			}else{
				echo("Nevalidno");
				failed = 1;
			}
		}
		if( strlen(res)==0 )failed=1;
		
		if(failed){
			free(res);
			continue;
		}
		else break;
		
	}
	
	return res;
}

struct Node*node_input(){ //#...
	char*id;
	for(;;){
		id = kod_input("Kod: ");/////
		
		int failed = 0;
		struct Node*next = PURVI;
		for(;;){
			if(next == NULL)break;
			if(next->id == id){
				echo("Tozi nomer veche e zaet");
				failed = 1;
				break;
			}
			next = next->next;
		}
		if(failed==0)break;
	}
		
	char*ime_avtor;
	for(;;){
		char*test = input("Ime na avtor: ");/////
		if(strlen(test)>50){
			echo("Imeto trqbva da e do 50 simvola");
			free(test);
			continue;
		}
		ime_avtor = test;////
		break;
	}
	
	char*ime_kartina;
	for(;;){
		char*test = input("Ime na kartinata: ");/////
		if(strlen(test)>50){
			echo("Imeto trqbva da e do 50 simvola");
			free(test);
			continue;
		}
		ime_kartina = test;////
		break;
	}
	
	float cena = float_input("Cena: ");/////
	int godina = int_input("Godina: ");/////
	
	
	struct Node* sledvasht = NULL;
	sledvasht = (struct Node*)malloc(sizeof(struct Node));
	sledvasht->next = NULL;
	
	sledvasht-> id = id;
	sledvasht-> ime_avtor = ime_avtor;
	sledvasht-> ime_kartina = ime_kartina;
	sledvasht-> cena = cena;
	sledvasht-> godina = godina;
	
	return sledvasht;
}

void append_node(struct Node*node){ //#...
	char*f_name = node_dir_str(node->id);
	FILE*f= fopen(f_name, "wb");
	if(f==NULL)error2("Ne moga da otvorq faila ", f_name);
	free(f_name);
	fprintf(f, "%s\n", node-> ime_avtor);
	fprintf(f, "%s\n", node-> ime_kartina);
	fprintf(f, "%f\n", node-> cena);
	fprintf(f, "%d\n", node-> godina);
	fclose(f);
	
	if(PURVI==NULL){
		PURVI = node;
		return;
	}
	struct Node*next = PURVI;
	for(; next->next!=NULL ; next = next->next){
	}
	next->next = node;
}

void load_nodes(){ //#...
	
	struct Node* nachalo = NULL;
	nachalo = (struct Node*)malloc(sizeof(struct Node));
	nachalo->next = NULL;
	
	struct dirent *de;
	DIR *dr = opendir("nodes"); 
	if (dr == NULL)error("Ne moga da otvorq papkata s node-ovete");
	
	while( (de=readdir(dr)) != NULL){
		char*node_file_name = copy_str(de -> d_name);
		if( strcmp(node_file_name,".")==0 || strcmp(node_file_name,"..")==0)continue;
		
		char*dir = node_dir_str(node_file_name);
		FILE*f = fopen(dir, "rb");
		free(dir);
		if(f==NULL)error2("Ne moga da otvorq failla na node-a: ", node_file_name);
		
		
		struct Node* sledvasht = NULL;
		sledvasht = (struct Node*)malloc(sizeof(struct Node));
		sledvasht->next = NULL;
		
		sledvasht-> id = node_file_name;
		
		char*line0=read_line(f);
		sledvasht-> ime_avtor = line0;
		
		char*line1=read_line(f);
		sledvasht-> ime_kartina = line1;
		
		char*line2=read_line(f);
		sledvasht-> cena = str_to_float(line2);
		free(line2);
		
		char*line3=read_line(f);
		sledvasht-> godina = str_to_int(line3);
		free(line3);
		
		fclose(f);
		
		append_node(sledvasht);
		
	}
	
}



void delete_node(struct Node*node){
	struct Node*prev = NULL;
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		if( strcmp(next->id, node->id)==0 ){
			
			char*dir = node_dir_str(next->id);
			int res = remove(dir);
			free(dir);
			if(res!=0)echo("Ne mojah da iztriq faila");
			
			struct Node*real_next = next->next;
			free(next);
			if(prev==NULL){
				PURVI = real_next;
			}else{
				prev->next = real_next;
			}
			return;
		}
		prev = next;
	}
	error("Cant delete a node that doesnt exist");
}
///////////////////////////////////

struct Node*choose_node(){
	for(;;){
		struct Node*next = PURVI;
		int i=1;
		for(;;i++){
			if(next==NULL)break;
			echo("");
			printf("IZBOR NOMER: %d\n", i);
			print_node(next);
			echo("");
			next = next->next;
		}
		i--;
		uint izbor = uint_input("Izberi: ");
		if( izbor > (uint)i || izbor == 0 ){
			echo("Nevaliden izbor");
			continue;
		}
		
		int izbrana_figura = (int)izbor;
		
		i=1;
		for(struct Node*next = PURVI; ; next = next->next){
			if(i==izbrana_figura)return next;
			i++;
		}
		break;
	}
}


