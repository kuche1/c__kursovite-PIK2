
#include "neshta.c"





char*node_dir_str(char*id){
	char*dir = new_str("nodes/");
	append_str_str(&dir, id);
	return dir;
}
char*node_dir(char* id){// uint id ???
	char*dir = new_str("nodes/");
	append_str_str(&dir, id);
	return dir;
}

/////////////////////////


struct Node{ //#...
	char*id;
	char*adres;
	uint otdeleniq;
	uint legla;
	float biudjet;
	
	struct Node*next;
};

struct Node* PURVI=NULL;




void print_node(struct Node*node){ //#...
	printf("Ime: %s\n", node->id);
	printf("Adres: %s\n", node->adres);
	printf("Otdeleniq: %u\n", node->otdeleniq);
	printf("Legla: %u\n", node->legla);
	printf("Biudjet: %f\n", node->biudjet);
}

struct Node*node_input(){ //#...
	struct Node* sledvasht = NULL;
	sledvasht = (struct Node*)malloc(sizeof(struct Node));
	sledvasht->next = NULL;
	
	
	sledvasht-> id = input_capital_50("Naimenovalie: ");////
	sledvasht-> adres = input("Adres: ");////
	sledvasht-> otdeleniq = uint_input("Otdeleniq: ");//
	sledvasht-> legla = uint_input("Legla: ");//
	sledvasht-> biudjet = float_input("Biudjet: ");////
	
	
	return sledvasht;
}

void append_node(struct Node*node){ //#...
	char*f_name = node_dir(node->id);
	FILE*f= fopen(f_name, "wb");
	if(f==NULL)error2("Ne moga da otvorq faila ", f_name);
	free(f_name);
	
	
	//write_str(f, node->id);//
	write_str(f, node->adres);//
	write_uint(f, node->otdeleniq);//
	write_uint(f, node->legla);//
	write_float(f, node->biudjet);//

	
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
		
		
		sledvasht-> id = node_file_name; //
		sledvasht -> adres = read_str(f); //
		sledvasht -> otdeleniq = read_uint(f); //
		sledvasht -> legla = read_uint(f); //
		sledvasht -> biudjet = read_float(f); //
		
		fclose(f);
		
		append_node(sledvasht);
		
	}
	
}


void delete_node(struct Node*node){
	struct Node*prev = NULL;
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		if( strcmp(next->id, node->id)==0 ){ //
			
			char*dir = node_dir(next->id);
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


