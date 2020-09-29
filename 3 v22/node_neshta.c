
#include "neshta.c"



struct Node{ //#...
	int id;
	char*ime;
	unsigned int steni;
	float obem;
	float lice;
	
	struct Node*next;
};

struct Node* PURVI=NULL;





/////////////////////////

char*node_dir_str(char*id){
	char*dir = new_str("nodes/");
	append_str_str(&dir, id);
	return dir;
}
char*node_dir(uint id){
	char*dir = new_str("nodes/");
	append_str_uint(&dir, id);
	return dir;
}

/////////////////////////




void print_node(struct Node*node){ //#...
	printf("kod: %u\n", node->id);
	printf("ime: %s\n", node->ime);
	printf("steni: %u\n", node->steni);
	printf("obem: %f\n", node->obem);
	printf("lice: %f\n", node->lice);
}

struct Node*node_input(){ //#...
	unsigned int id;
	for(;;){
		id = uint_input("Kod: ");/////
		
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
		
	char*ime;
	for(;;){
		char*test_ime = input("Ime: ");/////
		if(strlen(test_ime)>50){
			echo("Imeto trqbva da e do 50 simvola");
			free(test_ime);
			continue;
		}
		int invalid = 0;
		for(unsigned int i=0; i<strlen(test_ime); i++){
			char c = test_ime[i];
			if(c >= 'A' && c <= 'Z'){
			}else{
				invalid = 1;
				break;
			}
		}
		if(invalid==1){
			echo("Trqbva imeto da sadurja samo glavni bukvi");
			continue;
		}
		
		ime = test_ime;
		break;
	}
	
	uint steni = uint_input("Steni: ");/////
	float obem = ufloat_input("Obem: ");/////
	float lice = ufloat_input("Lice: ");/////
	
	
	struct Node* sledvasht = NULL;
	sledvasht = (struct Node*)malloc(sizeof(struct Node));
	sledvasht->next = NULL;
	
	sledvasht-> id = id;
	sledvasht-> ime = ime;
	sledvasht-> steni = steni;
	sledvasht-> obem = obem;
	sledvasht-> lice = lice;
	
	return sledvasht;
}

void append_node(struct Node*node){ //#...
	char*f_name = node_dir(node->id);
	FILE*f= fopen(f_name, "wb");
	if(f==NULL)error2("Ne moga da otvorq faila ", f_name);
	free(f_name);
	//fprintf(f, "%s\n%u\n%f\n%f\n", node->ime, node->steni, node->obem, node->lice);
	
	write_str(f, node->ime);
	write_uint(f, node->steni);
	write_float(f, node->obem);
	write_float(f, node->lice);
	
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
		
		sledvasht-> id = (uint)str_to_int(node_file_name);
		
		sledvasht -> ime = read_str(f);
		sledvasht -> steni = read_uint(f);
		sledvasht -> obem = read_float(f);
		sledvasht -> lice = read_float(f);
		
		fclose(f);
		
		append_node(sledvasht);
		
	}
	
}

///////////////////////////////////

void delete_node(struct Node*node){
	struct Node*prev = NULL;
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		if(next->id == node->id){
			
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


