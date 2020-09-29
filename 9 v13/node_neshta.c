
#include "neshta.c"




char*node_dir(char* id){
	char*dir = new_str("nodes/");
	append_str_str(&dir, id);
	return dir;
}

/////////////////////////


struct Node{ //#...
	char*id;
	char*imena;
	char*adres;
	char*egn;
	uint knigi;
	
	struct Node*next;
};

struct Node* PURVI=NULL;






int id_same(char* id1, char*id2){
	return strcmp(id1, id2)==0;
}


char*id_input(){ //#...
	for(;;){
		char*test = input("Nomer: ");
		if( strlen(test) > 0 && strlen(test) <= 8 && is_str_int(test)==1 ){
			int failed = 0;
			for(struct Node*next = PURVI; next!=NULL ; next = next->next){
				if( strcmp(next->id, test) ==0){ //
					failed = 1;
					break;
				}
			}
			if(failed==0)return test;
		}
		free(test);
		echo("Nevalidno");
	}
}

char*imena_input(char*prompt){
	for(;;){
		char*test = input(prompt);
		int failed = 0;
		for(int ind=0; ind<strlen(test); ind++){
			char c = test[ind];
			if( c==' ' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ){
			}else{
				printf("Invalid character: '%c'\n", c);
				failed = 1;
				break;
			}
		}
		if(failed==0){
			if( strlen(test) > 0 && strlen(test) <= 80){
				return test;
			}
		}
		echo("Nevalidno");
		free(test);
	}
}




void print_node(struct Node*node){ //#...
	printf("Nomer: %s\n", node->id);
	printf("Imena: %s\n", node->imena);
	printf("Adres: %s\n", node->adres);
	printf("EGN: %s\n", node->egn);
	printf("Vzeti knigi: %u\n", node->knigi);
}


struct Node*node_input(){ //#...
	struct Node* sledvasht = NULL;
	sledvasht = (struct Node*)malloc(sizeof(struct Node));
	sledvasht->next = NULL;
	
	sledvasht->id = id_input();//
	
	sledvasht->imena = imena_input("Imena: ");//
	
	for(;;){
		char*test = input("Adres: ");
		int failed = 0;
		for(int ind=0; ind<strlen(test); ind++){
			char c = test[ind];
			if( c==' ' || c==',' || (c >= 'A' && c <= 'Z') || (c >='a' && c <= 'z') ){
			}else{
				failed = 1;
				break;
			}
		}
		if(failed){
			echo("Nevalidno");
			free(test);
		}else{
			if( strlen(test) > 0 && strlen(test) <= 80){
				sledvasht->adres = test;//
				break;
			}
		}
	}
	
	sledvasht->egn = EGN_input("EGN: ");//
	
	sledvasht->knigi = uint_input("Broi vzeti knigi: ");//
	
	return sledvasht;
}

void append_node(struct Node*node){ //#...
	char*f_name = node->id;//
	
	f_name = node_dir(f_name);
	FILE*f= fopen(f_name, "wb");
	if(f==NULL)error2("Ne moga da otvorq faila ", f_name);
	free(f_name);
	
	write_str(f, node->imena);//
	write_str(f, node->adres);//
	write_str(f, node->egn);//
	write_uint(f, node->knigi);//
	
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
		sledvasht -> imena = read_str(f); //
		sledvasht -> adres = read_str(f); //
		sledvasht -> egn = read_str(f); //
		sledvasht -> knigi = read_uint(f); //
		
		fclose(f);
		
		append_node(sledvasht);
		
	}
	
}


void delete_node(struct Node*node){
	struct Node*prev = NULL;
	for(struct Node*next = PURVI; next!=NULL ; next = next->next){
		if( id_same(next->id, node->id) ){ //
			
			char*tmp = next->id; //
			
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


