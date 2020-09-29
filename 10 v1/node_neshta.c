
#include "neshta.c"


char*node_dir(char* id){
	char*dir = new_str("nodes/");
	append_str_str(&dir, id);
	return dir;
}

/////////////////////////


struct Node{ //#...
	char*id;
	char*data;
	int produljitelnost;
	float cena;
	
	struct Node*next;
};

struct Node* PURVI=NULL;




int id_same(char* id1, char*id2){ //#...
	return strcmp(id1, id2)==0;
}

char*id_to_str(char*id){ //#...
	return id;
}



char*id_input(char*prompt){ //#...
	for(;;){
		printf("%s", prompt);
		
		char c;
		char*test = new_str("");
		
		c = getchar();
		if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ){
			append_str_char(&test, c);
		}else{
			while( getchar() != '\n');
			free(test);
			printf("Nevalidna bukva: %c\n", c);
			continue;
		}
		
		char*vtora_chast = input("");
		if( is_str_int(vtora_chast) ){
			append_str_str(&test, vtora_chast);
			return test;
		}
		printf("Nevalidni cifri: %s\n", vtora_chast);
		free(vtora_chast);
		
	}
}





void print_node(struct Node*node){ //#...
	printf("Kod: %s\n", node->id);
	printf("Data: %s\n", node->data);
	printf("Produljitelnost: %i\n", node->produljitelnost);
	printf("Cena: %f\n", node->cena);
}


struct Node*node_input(){ //#...
	struct Node* sledvasht = NULL;
	sledvasht = (struct Node*)malloc(sizeof(struct Node));
	sledvasht->next = NULL;
	
	sledvasht->id = id_input("Kod: ");//
	
	sledvasht->data = date_input("Data: ");//
	
	sledvasht->produljitelnost = int_input("Produljitelnost: ");//
	
	sledvasht->cena = float_input("Cena: ");//
	
	return sledvasht;
}

void append_node(struct Node*node){ //#...
	char*f_name = node->id;//
	
	f_name = node_dir(f_name);
	FILE*f= fopen(f_name, "wb");
	if(f==NULL)error2("Ne moga da otvorq faila ", f_name);
	free(f_name);
	
	write_str(f, node->data);//
	write_int(f, node->produljitelnost);//
	write_float(f, node->cena);//
	
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
		
		char*dir = node_dir(node_file_name);
		FILE*f = fopen(dir, "rb");
		free(dir);
		if(f==NULL)error2("Ne moga da otvorq failla na node-a: ", node_file_name);
		
		struct Node* sledvasht = NULL;
		sledvasht = (struct Node*)malloc(sizeof(struct Node));
		sledvasht->next = NULL;
		
		sledvasht-> id = node_file_name; //
		sledvasht -> data = read_str(f); //
		sledvasht -> produljitelnost = read_int(f); //
		sledvasht -> cena = read_float(f); //
		
		fclose(f);
		
		append_node(sledvasht);
		
	}
	
}

///////////////////////////////////

void delete_node(struct Node*node){
	struct Node*prev = NULL;
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		if( id_same(next->id, node->id) ){
			
			char*tmp = id_to_str(next->id);
			
			char*dir = node_dir( tmp );
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


