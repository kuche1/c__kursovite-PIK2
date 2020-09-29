

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

void copy_paste_str(char*target, char*source){
	for(int i=0; i <= strlen(source); i++){
		target[i] = source[i];
	}
}

/////////////////////////


struct Optimal_node{ //#...
	char id[13];
	char ime[40];
	float godina1;
	float godina2;
	float godina3;
	float godina4;
	float godina5;
	char data[10];
};

struct Node{ //#...
	char id[13];
	char ime[40];
	float godina1;
	float godina2;
	float godina3;
	float godina4;
	float godina5;
	char data[10];
	
	struct Node*next;
};

struct Node* PURVI=NULL;



void format_node(struct Optimal_node*opt_node, struct Node*node){
	copy_paste_str( opt_node->id, node->id);
	copy_paste_str( opt_node->ime, node->ime);
	opt_node->godina1 = node->godina1;
	opt_node->godina2 = node->godina2;
	opt_node->godina3 = node->godina3;
	opt_node->godina4 = node->godina4;
	opt_node->godina5 = node->godina5;
	copy_paste_str( opt_node->data, node->data); 
}

void format_optimal_node(struct Node*node, struct Optimal_node*opt_node){
	copy_paste_str( node->id, opt_node->id);
	copy_paste_str( node->ime, opt_node->ime);
	node->godina1 = opt_node->godina1;
	node->godina2 = opt_node->godina2;
	node->godina3 = opt_node->godina3;
	node->godina4 = opt_node->godina4;
	node->godina5 = opt_node->godina5;
	copy_paste_str( node->data, opt_node->data); 
}



void print_node(struct Node*node){ //#...
	printf("Nomer: %s\n", node->id);
	printf("Ime: %s\n", node->ime);
	printf("Pechalba 2019: %f\n", node->godina1);
	printf("Pechalba 2018: %f\n", node->godina2);
	printf("Pechalba 2017: %f\n", node->godina3);
	printf("Pechalba 2016: %f\n", node->godina4);
	printf("Pechalba 2015: %f\n", node->godina5);
	printf("Data na registraciq: %s\n", node->data);
}

void input_id(char*target){//#...
	for(;;){
		//char*test = input("Danuchen nomer: ");
		printf("Danuchen nomer: ");
		target[0] = 0;
		scanf( "%s", target );
		while(getchar()!='\n');
		
		if(is_str_int(target) && strlen(target)==13){
			return;
		}
		echo("Nevalidno");
	}
}

void input_data(char addr[10], char*prompt){//#...
	for(;;){
		//char*test = input(prompt);
		printf("%s", prompt);
		addr[0] = 0;
		scanf("%s", addr);
		while(getchar()!='\n');
		char*test = addr;
		
		if(strlen(test)!=10){
			echo("Greshen format, greshna duljina");
			;continue;
		}
		
		char dot1 = test[2];
		char dot2 = test[5];
		if( dot1 != '.' || dot2 != '.'){
			echo("Greshen format, nqma tochki kudeto trqbva");
			;continue;
		}
		
		int day_int_1 = is_char_int(test[0]);
		int day_int_2 = is_char_int(test[1]);
		if( day_int_1 && day_int_2 ){
		}else{
			echo("Greshen format, denq trqbva da e cifra");
			;continue;
		}
		
		int month_int_1 = is_char_int(test[3]);
		int month_int_2 = is_char_int(test[4]);
		if( month_int_1 && month_int_2 ){
		}else{
			echo("Greshen format, meseca trqbva da e cifra");
			;continue;
		}
		
		int year_int_1 = is_char_int(test[6]);
		int year_int_2 = is_char_int(test[7]);
		int year_int_3 = is_char_int(test[8]);
		int year_int_4 = is_char_int(test[9]);
		if( year_int_1 && year_int_2 && year_int_3 && year_int_4 ){
		}else{
			echo("Greshen format, godinata trqbva da e cifra");
			;continue;
		}
		
		
		int day1 = char_to_int(test[0]);
		int day2 = char_to_int(test[1]);
		if( day1 > 3 || (day1 == 3 && day2 > 1) ){
			echo("Greshen format, takuv den ot meseca nqma");
			;continue;
		}
		
		int month1 = char_to_int(test[3]);
		int month2 = char_to_int(test[4]);
		if( month1 > 1 || (month1==1 && month2 > 2) ){
			echo("Greshen format, takuv mesec nqma");
			;continue;
		}
		
		int year1 = char_to_int(test[6]);
		int year2 = char_to_int(test[7]);
		int year3 = char_to_int(test[8]);
		int year4 = char_to_int(test[9]);
		if( year1==0 && year2==0 && year3==0 && year4==0){
			echo("Greshen format, takava godina nqma");
			;continue;
		}

		return;
	}
}

struct Node*node_input(){ //#...
	struct Node* sledvasht = NULL;
	sledvasht = (struct Node*)malloc(sizeof(struct Node));
	sledvasht->next = NULL;
	
	
	//sledvasht-> id = input_id();////
	input_id(sledvasht-> id);
	printf("ID: %s\n", sledvasht->id);
	
	for(;;){
		//char*test_ime = input("Ime: ");
		printf("Ime: "); 
		(sledvasht-> ime)[0] = 0;
		scanf("%s", sledvasht-> ime);
		while(getchar()!='\n');
		
		if(strlen(sledvasht-> ime)>50){
			echo("Imeto trqbva da e do 40 simvola");
			continue;
		}
		break;
	}
	// NENORMALNO
	//printf("ID: %s\n", sledvasht->id);
	//printf("ime: %s\n", sledvasht->ime);
	//sledvasht-> ime = ime;////
	
	sledvasht-> godina1 = float_input("Pechalba za 2019: ");////
	sledvasht-> godina2 = float_input("Pechalba za 2018: ");////
	sledvasht-> godina3 = float_input("Pechalba za 2017: ");////
	sledvasht-> godina4 = float_input("Pechalba za 2016: ");////
	sledvasht-> godina5 = float_input("Pechalba za 2015: ");////
	
	input_data(sledvasht-> data, "Vuvedi data: ");////
	
	
	return sledvasht;
}

void append_node(struct Node*node){ //#...
	char*f_name = node_dir(node->id);
	FILE*f= fopen(f_name, "wb");
	if(f==NULL)error2("Ne moga da otvorq faila ", f_name);
	free(f_name);
	/*
	struct Node*tmp = node->next;
	node->next = NULL;
	fwrite(node, sizeof(struct Node), 1, f);
	node->next = tmp;
	*/
	struct Optimal_node*optimal_node = NULL;
	optimal_node = (struct Optimal_node*)malloc(sizeof(struct Optimal_node));
	format_node(optimal_node, node);
	fwrite(optimal_node, sizeof(struct Optimal_node), 1, f);
	
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
		
		/*
		struct Node* sledvasht = NULL;
		sledvasht = (struct Node*)malloc(sizeof(struct Node));
		sledvasht->next = NULL;
		
		fread(sledvasht, sizeof(struct Node), 1, f);
		sledvasht->next = NULL;
		*/
		struct Optimal_node*node = NULL;
		node = (struct Optimal_node*)malloc(sizeof(struct Optimal_node));
		
		fread(node, sizeof(struct Optimal_node), 1, f);
		
		struct Node* sledvasht = NULL;
		sledvasht = (struct Node*)malloc(sizeof(struct Node));
		
		format_optimal_node(sledvasht, node);
		free(node);
		
		fclose(f);
		
		append_node(sledvasht);
		
	}
	
}



void delete_node(struct Node*node){//#...
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


