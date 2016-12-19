#include"LexAn.h"


void LexAn::scanwords()
{
	char c;
	int i, j, k;
	int count = 0;
	int chgLine = 0;

	while (1)
	{
		c = fgetc(fin);
		if (c == EOF)
		{
			break;
		}
		/*Newline character*/
		if (c == '\n' || count == 256 - 2)
		{
			if (count == 256 - 2)
			{
				bufferin[buffernum][count] = c;
				for (i = count; i > 0; i--)
				{
					if (spaces(bufferin[buffernum][i]) == 1)
					{
						for (j = 0, k = i + 1; k <= count; k++, j++)
						{
							bufferin[1 - buffernum][j] = bufferin[buffernum][k];
						}
						bufferin[1 - buffernum][j] = '\0';
						bufferin[buffernum][i + 1] = '\0';
					}
				}
			}
			else
			{
				bufferin[buffernum][count] = '\0';
			}

			if (c == '\n')
			{
				chgLine = 1;
			}

			clearnotes();

			if (strlen(bufferin[buffernum]) > 0)
			{
				strcpy(bufferscan, bufferin[buffernum]);
				getwords(0);
			}
			if (count == 256 - 2)
			{
				buffernum = 1 - buffernum;
			}
			if (chgLine == 1)
			{
				chgLine = 0;
			}
			count = 0;
		}
		else
		{
			bufferin[buffernum][count++] = c;
		}
	}
	printf("The processed data has been written to out.txt\n");
}

void LexAn::clearnotes()
{
	int i, j, k;
	int noteCount = 0;
	int flag = 0;
	char note[100];

	/*notes*/
	for (i = 0; bufferin[buffernum][i] != '\0'; i++)
	{
		if (bufferin[buffernum][i] == '"')
		{
			flag = 1 - flag;
			continue;
		}
		if (bufferin[buffernum][i] == '/' && flag == 0)
		{
			if (bufferin[buffernum][i + 1] == '/')
			{
				for (j = i; bufferin[buffernum][j] != '\0'; j++)
				{
					note[noteCount++] = bufferin[buffernum][j];
				}
				note[noteCount] = '\0';
				noteCount = 0;
				fprintf(fout, "  [ %s ]  ----  [ notes ]\n", note);
				bufferin[buffernum][i] = '\0';
				break;
			}

			if (bufferin[buffernum][i + 1] == '*')
			{
				note[noteCount++] = '/';
				note[noteCount++] = '*';
				for (j = i + 2; bufferin[buffernum][j] != '\0'; j++)
				{
					note[noteCount++] = bufferin[buffernum][j];
					if (bufferin[buffernum][j] == '*' && bufferin[buffernum][j + 1] == '/')
					{
						j += 2;
						note[noteCount++] = bufferin[buffernum][j];
						note[noteCount] = '\0';
						noteCount = 0;
						fprintf(fout, "  [ %s ]  ----  [ notes ]\n", note);
						break;
					}
				}
				for (; bufferin[buffernum][j] != '\0'; j++, i++)
				{
					bufferin[buffernum][i] = bufferin[buffernum][j];
				}
				if (bufferin[buffernum][j] == '\0')
				{
					bufferin[buffernum][i] = '\0';
				}
			}
		}
	}

	//Spaces
	for (i = 0, flag = 0; bufferin[buffernum][i] != '\0'; i++)
	{
		if (bufferin[buffernum][i] == '"')
		{
			flag = 1 - flag;
			continue;
		}
		if (bufferin[buffernum][i] == ' ' && flag == 0)
		{
			for (j = i + 1; bufferin[buffernum][j] != '\0' && bufferin[buffernum][j] == ' '; j++)
			{
			}
			if (bufferin[buffernum][j] == '\0')
			{
				bufferin[buffernum][i] = '\0';
				break;
			}
			if (bufferin[buffernum][j] != '\0' && ((spaces(bufferin[buffernum][j]) == 1) || (i > 0 && spaces(bufferin[buffernum][i - 1]) == 1)))
			{
				for (k = i; bufferin[buffernum][j] != '\0'; j++, k++)
				{
					bufferin[buffernum][k] = bufferin[buffernum][j];
				}
				bufferin[buffernum][k] = '\0';
				i--;
			}
		}
	}

	//Tabs
	for (i = 0, flag = 0; bufferin[buffernum][i] != '\0'; i++)
	{
		if (bufferin[buffernum][i] == '\t')
		{
			for (j = i; bufferin[buffernum][j] != '\0'; j++)
			{
				bufferin[buffernum][j] = bufferin[buffernum][j + 1];
			}
			i = -1;
		}
	}
}
//state machine
void LexAn::getwords(int state)
{
    char word[100];
	int charCount = 0;
	int finish = 0;
	int num;
	int i, j, k;
	for (i = 0; bufferscan[i] != '\0'; i++)
	{
		switch (state / 10)
		{
		case 0:
			switch (charkind(bufferscan[i]))
			{
			case 1:
				word[charCount++] = bufferscan[i];
				state = 10;
				break;
			case 2:
				word[charCount++] = bufferscan[i];
				state = 20;
				break;
			case 3:
				word[charCount++] = bufferscan[i];
				state = 30;
				break;
			case 0: case 5:
				word[charCount++] = bufferscan[i];
				switch (bufferscan[i])
				{
				case '"':
					state = 41;
					break;
				case '\'':
					state = 42;
					break;
				case '(': case ')': case '{': case '}': case '[': case ']': case ';': case ',': case '.':
					state = 50;
					word[charCount] = '\0';
					finish = 1;
					break;
				case '=':
					state = 43;
					break;
				default:
					state = 40;
					break;
				}
				break;
			default: word[charCount++] = bufferscan[i]; break;
			}
			break;
		case 1:
			switch (charkind(bufferscan[i]))
			{
			case 1:
				word[charCount++] = bufferscan[i];
				state = 10;
				break;
			case 2:
				word[charCount++] = bufferscan[i];
				state = 20;
				break;
			case 3:
				word[charCount++] = bufferscan[i];
				state = 30;
				break;
			case 0:case 5:
				word[charCount] = '\0';
				num = 0;
				while (word[num] != '\0')
					num++;

				//Length of the data! .
                // will be and idenftiers
                if (num>7)
					word[7] = '\0';

				i--;
				finish = 1;
				state = 50;
				break;
			default: word[charCount++] = bufferscan[i]; break;
			}
			break;
		case 2:
			switch (charkind(bufferscan[i]))
			{
			case 1:
				word[charCount++] = bufferscan[i];
				state = 20;
				break;
			case 2:
				word[charCount++] = bufferscan[i];
				state = 20;
				break;
			case 3:
				word[charCount++] = bufferscan[i];
				state = 30;
				break;
			case 0:
				if (bufferscan[i] == '.')
				{
					word[charCount++] = bufferscan[i];
					state = 20;
					break;
				}
				word[charCount] = '\0';
				i--;
				finish = 1;
				state = 50;
				break;
			default: word[charCount++] = bufferscan[i]; break;
			}
			break;
		case 3:
			switch (charkind(bufferscan[i]))
			{
			case 1:
				word[charCount++] = bufferscan[i];
				state = 30;
				break;
			case 2:
				word[charCount++] = bufferscan[i];
				state = 30;
				break;
			case 3:
				word[charCount++] = bufferscan[i];
				state = 30;
				break;
			case 0:
				word[charCount] = '\0';
				i--;
				finish = 1;
				state = 50;
				break;
			default: word[charCount++] = bufferscan[i]; break;
			}
			break;
		case 4:
			switch (state)
			{
			case 40:
				switch (charkind(bufferscan[i]))
				{
				case 1:
					word[charCount] = '\0';
					i--;
					finish = 1;
					state = 50;
					break;
				case 2:
					word[charCount] = '\0';
					i--;
					finish = 1;
					state = 50;
					break;
				case 3:
					word[charCount] = '\0';
					i--;
					finish = 1;
					state = 50;
					break;
				case 0:
					word[charCount++] = bufferscan[i];
					state = 40;
					break;
				default: word[charCount++] = bufferscan[i]; break;
				}
				break;
			case 41:
				word[charCount++] = bufferscan[i];
				if (bufferscan[i] == '"')
				{
					if (charkind(bufferscan[i - 1]) == 4)
					{
					}
					else
					{
						word[charCount] = '\0';
						finish = 1;
						state = 50;
					}
				}
				break;
			case 42:
				word[charCount++] = bufferscan[i];
				if (bufferscan[i] == '\'')
				{
					word[charCount] = '\0';
					finish = 1;
					state = 50;
				}
				break;
			case 43:
				if (bufferscan[i] == '=')
				{
					word[charCount++] = bufferscan[i];
					state = 43;
				}
				else
				{
					word[charCount] = '\0';
					finish = 1;
					i--;
					state = 50;
				}
				break;
			default: word[charCount++] = bufferscan[i]; break;
			}
			break;
		case 5:
			finish = 0;
			state = 0;
			charCount = 0;
			i--;

			wordkind(word);
			break;
		default:break;
		}
		if (bufferscan[i + 1] == '\0')
		{
			word[charCount] = '\0';
			wordkind(word);
		}
	}
}
void LexAn::wordkind(char str[])
{
	int i, j, k;
	int flag = 0;

	/*Determine whether the keyword or identifier*/
	if (keyword(str) == 1)
	{
		if (strcmp(str, "true") == 0 || strcmp(str, "false") == 0)
		{
			fprintf(fout, "  [ %s ]  ----  [ Boolean type ]\n", str);
		}
		else
		{
			fprintf(fout, "  [ %s ]  ----  [ Keyword ]\n", str);
		}
	}
	else if (signwords(str) == 1)
	{
		fprintf(fout, "  [ %s ]  ----  [ Identifiers ]\n", str);
	}
	else if (integers(str) == 1)
	{
		fprintf(fout, "  [ %s ]  ----  [ Integer ]\n", str);
	}
	else if (floats(str) == 1)
	{
		fprintf(fout, "  [ %s ]  ----  [ float ]\n", str);
	}
	else if (str[0] == '\'' && str[strlen(str) - 1] == '\'')
	{
		fprintf(fout, "  [ %s ]  ----  [ Character ]\n", str);
	}
	else if (str[0] == '"' && str[strlen(str) - 1] == '"')
	{
		fprintf(fout, "  [ %s ]  ----  [ string ]\n", str);
	}
	else if (spaces(str[0]) == 1 && str[0] != '"' && str[0] != '\'')
	{
		if (strcmp(str, "<") == 0 || strcmp(str, ">") == 0 || strcmp(str, "<=") == 0 || strcmp(str, ">=") == 0)
		{
			fprintf(fout, "  [ %s ]  ----  [ < > <= >= ]\n", str);
		}
		else if (strcmp(str, "<<") == 0 || strcmp(str, ">>") == 0 || strcmp(str, ">>>") == 0 || strcmp(str, "<<<") == 0)
		{
			fprintf(fout, "  [ %s ]  ----  [ << >> ]\n", str);
		}
		else if (strchr(str, '=') != NULL)
		{
			if (strcmp(str, "==") == 0 || strcmp(str, "!=") == 0)
			{
				fprintf(fout, "  [ %s ]  ----  [ == != ]\n", str);
			}
			else
			{
				fprintf(fout, "  [ %s ]  ----  [ Operator ]\n", str);
			}
		}
		else if (strcmp(str, "||") == 0)
		{
			fprintf(fout, "  [ %s ]  ----  [ || ]\n", str);
		}
		else if (strcmp(str, "&&") == 0)
		{
			fprintf(fout, "  [ %s ]  ----  [ && ]\n", str);
		}
        else if (strcmp(str, "++") == 0 || strcmp(str, "--") == 0 ){
            fprintf(fout, "  [ %s ]  ----  [ Operator ]\n", str);
        }
            else if( strcmp(str, "!") == 0 || strcmp(str, "~") == 0){
            fprintf(fout, "  [ %s ]  ----  [ ! ~ ]\n", str);

            }


		else if (strlen(str) == 1)
		{
			switch (str[0])
			{
			case '?': case ':': fprintf(fout, "  [ %s ]  ----  [ ?: ]\n", str); break;
			case ' ': fprintf(fout, "  [ %s ]  ----  [ Spaces ]\n", str); break;
			case '{':case '}': fprintf(fout, "  [ %s ]  ----  [ {} ]\n", str); break;
			case '[':case ']':case '(':case ')':case '.': fprintf(fout, "  [ %s ]  ----  [ [] () . ]\n", str); break;
			case ',': fprintf(fout, "  [ %s ]  ----  [ , ]\n", str); break;
			case ';': fprintf(fout, "  [ %s ]  ----  [ ; ]\n", str); break;
			case '+':case '-': fprintf(fout, "  [ %s ]  ----  [ + ]\n", str); break;
			case '*':case '/':case '%': fprintf(fout, "  [ %s ]  ----  [ * / ]\n", str); break;
			case '|': fprintf(fout, "  [ %s ]  ----  [ | ]\n", str); break;
			case '^': fprintf(fout, "  [ %s ]  ----  [ ^ ]\n", str); break;
			case '&': fprintf(fout, "  [ %s ]  ----  [ & ]\n", str); break;
			default: fprintf(fout, "  [ %s ]  ----  [ Other symbols ]\n", str); break;
			}
		}
	}
	else
	{
		fprintf(fout, "  [ %s ]  ----  [ The wrong word ]\n", str);
	}
}
LexAn::~LexAn()
{
	fclose(fin);
	fclose(fout);
}
