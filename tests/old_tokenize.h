// void tokenize(const char* str,
// 			   const char* delims,
// 			   char dest[][10],
// 			   int max_tokens)
// {
// 	const char* prev = str;
// 	const char* c = strpbrk(str, delims);
// 	size_t toksize=0;
// 	int idx=0;

// 	while(c != NULL && idx < max_tokens)
// 	{
// 		toksize = c-prev;
// 		if(toksize != 0)
// 		{
// 			strncpy(dest[idx], prev, toksize);
// 			dest[idx][toksize] = '\0';
// 			idx++;
// 		}
// 		dest[idx][0] = *c;
// 		dest[idx][1] = '\0';
// 		prev = ++c;
// 		c = strpbrk(c, delims);
// 		idx++;
// 	}
// 	if(*prev)
// 	{
// 		strcpy(dest[idx], prev);
// 		idx++;
// 	}
// 	dest[idx][0] = '\0';
// }


// void debug_parse_str(const char* fmt, int loglevel)
// {
// 	char currstr[100];
// 	int idx = 0;
// 	const char* cptr = fmt;
// 	bool brk = 0;
// 	while(idx < 100 && !brk)
// 	{
// 		switch(*cptr)
// 		{
// 			case ' ':
// 				cptr++;
// 				break;
// 			case '\0':
// 				brk = true;
// 				if(!idx)
// 					break;
// 			case ',':
// 				currstr[idx] = '\0';
// 				idx = 0;
// 				debug_single_spec(currstr, loglevel);
// 				cptr++;
// 				break;
// 			default:
// 				currstr[idx] = *cptr;
// 				cptr++;
// 				idx++;
// 				break;
// 		}
// 	}
// }

// void debug_single_spec(char str[100], int loglevel)
// {
// 	tokenize(str, delims, tokens, 100);
// 	Tree* tree = create_token_tree(tokens, loglevel);
// 	print_tree(tree, true);
// 	delete_tree(tree);
// 	for(int i=0; i<100 && (tokens[i][0] != '\0'); i++)
// 		printf("%s ", tokens[i]);
// 	printf("\n\n");
// }


// Tree* make_tree_from_tokens(int *i, 
// 	uint32_t ctx, 
// 	uint32_t* ctxsig,
// 	char parent,
// 	char tokens[][10],
// 	int loglevel,
// 	Tree* mainroot)
// {
// 	init_precedence_table();
// 	char tstr[100];
// 	Tree* root = (Tree*) malloc(sizeof(Tree));
// 	if(mainroot == NULL)
// 		mainroot = root;
// 	root->left = NULL;
// 	root->right = NULL;
// 	Tree* curr = root, *temp = NULL;
// 	int j=0;
// 	char *cptr;
// 	while(*i<100 && tokens[*i][0])
// 	{
// 		cptr = tokens[*i];
// 		if(loglevel)
// 		{
// 			printf("\n--> %s\n", cptr);
// 			if(ctx & PARENS_OPEN)
// 				printf("() YES, ");
// 			else
// 				printf("() NO, ");

// 			// if(ctx & READ_PARENT)
// 			// printf("Parens open? %s, Read parent? %s\n",
// 			// 		boolstr((ctx & PARENS_OPEN)), boolstr((ctx & READ_PARENT)));
// 			// printf("ctx: %u\n", ctx);
// 			if(parent)
// 			{
// 				printf("Parent: %c\n", parent);
// 			}
// 			else
// 				printf("Top level\n");			
// 		}
// 		if(loglevel >= Full)
// 		{
// 			printf("-------------------\n");
// 			print_tree(curr, true);
// 			printf("-------------------\n");
// 		}

// 		if(isdigit(*cptr))
// 		{
// 			strcpy(&(curr->str[j]), cptr);
// 			j=0;
// 			cptr = tokens[++(*i)];
// 			continue;
// 		}
// 		// "(" --> keep target until ")" ?
// 		switch(*cptr)
// 		{
// 			// case '[':
// 			// 	if(has_precedence_over(parent, '[')
// 			// 		&& !(ctx & PARENS_OPEN))
// 			// 	{
// 			// 		return curr;
// 			// 	}
// 			// 	ctx |= SEQUENCE_OPEN;

// 			// 	++(*i);
// 			// 	temp = make_
// 			// 	// temp = 


// 			case '!':
// 				curr->str[0] = *cptr;
// 				curr->str[1] = '\0';
// 				++(*i);
// 				j = 0;
// 				curr->left = make_tree_from_tokens(i, 
// 					0, 
// 					ctxsig, 
// 					*cptr, 
// 					tokens,
// 					loglevel,
// 					mainroot);
// 				curr->right = NULL;
// 				break;
// 			case '(':
// 				ctx |= PARENS_OPEN;
// 				cptr = tokens[++(*i)];
// 				break;
// 			case ')':
// 				// return curr;

// 				// ++(*i);
// 				// return curr;
// 				if(ctx & PARENS_OPEN)
// 				{
// 					++(*i);
// 					ctx &= ~(PARENS_OPEN);
// 					break;
// 				}
// 				else
// 				{
// 					return curr;
// 				}


// 				// if(ctx & PARENS_OPEN)
// 				// 	return curr;
// 				// else
// 				// {
// 				// 	// ctx 
// 				// 	++(*i);
// 				// }
// 				// break;
// 			case 'B':
// 			case '$':
// 			case 'b':
// 			case 'u':
// 			case 'i':
// 				// temp = (Tree*) malloc(sizeof(Tree));
// 				curr->str[0] = *cptr;
// 				curr->str[1] = '\0';
// 				j = 0;
// 				++(*i);
// 				// ctx |= READ_PARENT;
// 				curr->left = make_tree_from_tokens(i, 
// 					0, 
// 					ctxsig, 
// 					*cptr, 
// 					tokens, 
// 					loglevel,
// 					mainroot);
// 				curr->right = NULL;
// 				break;
// 			// case '$':
// 			// 	j = 0;
// 			// 	curr->str[0] = *cptr;
// 			// 	curr->str[1] = '\0';
// 			// 	j++;
// 			// 	cptr = tokens[++(*i)];
// 			// 	break;
// 			case '*':
// 			case '=':
// 				// if(tokens[*(i+1)][0] == '=')
// 				// {

// 				// }

// 			case '%':
// 			case '-':
// 			case '+':
// 				// if(loglevel >= Debug)
// 				// {
// 				// 	dump_precedence(parent, *cptr);
// 				// }
// 				if(has_precedence_over(*cptr, parent)
// 					&& !(ctx & PARENS_OPEN)
// 					)
// 				{
// 					if(loglevel >= Debug)
// 						printf("%c has precender over %c, returning\n", parent, *cptr);
// 					return curr;
// 				}
					
// 				// if(((ctx & READ_PARENT) || (ctx & SKIP_PARENT)) &&
// 				// 	!(ctx & PARENS_OPEN))
// 				// {
// 				// 	return curr;
// 				// }
// 				ctx &= ~(READ_PARENT);
// 				temp = (Tree*) malloc(sizeof(Tree));
// 				temp->str[0] = *cptr;
// 				temp->str[1] = '\0';
// 				j = 0;
// 				temp->left = curr;
// 				curr = temp;
// 				++(*i);
// 				curr->right = make_tree_from_tokens(i, 
// 					0, 
// 					ctxsig, 
// 					*cptr, 
// 					tokens, 
// 					loglevel,
// 					mainroot);
// 				break;
// 				// cptr = tokens[*i];
// 			default:
// 				printf("Unrecognized token: %s\n", cptr);
// 				++(*i);
// 		}
// 		ctx |= *(ctxsig);
// 	}
// 	return curr;
// }

// Tree* create_token_tree(char tokens[][10], int loglevel)
// {
// 	int i=0;
// 	uint32_t sig = 0;
// 	return make_tree_from_tokens(&i, 0, &sig, '\0', tokens, loglevel, NULL);
// }