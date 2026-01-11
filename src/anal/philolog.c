int get_philolog(char *word) {
    return 26;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC  1000000         /* ANSI C clock ticks per sec */
#endif
#include <time.h>
#include <gkstring.h>

#define ARGS		"ILcixSVpm:"
#define PATH_SEP	'/'

int		quickflag = 0;
int		alpheiosCheckstring(const char* string, PrntFlags prntflags, FILE* fout);
void	cleanstring(char*);

extern Dialect	WantDialects;

char *philolog_morph(char *line, int lang, char *lib_path)
{
    FILE *stream;
    char *buf = NULL;
    size_t len = 0;
    stream = open_memstream(&buf, &len);
    if (stream == NULL) {
        return NULL;
    }
    if (lib_path) {
        SetMorphPath(lib_path);
    }
    if (lang) {
        set_lang(lang);
    }

	PrntFlags	flags = (PERSEUS_FORMAT|STRICT_CASE);
	/* flags |= input_flags; */

	int			rval;
	long		freemem = 0;
	int			c;
	int			errflg = 0;

	/* process arguments */
	/*
	while (!errflg && (c = getopt(argc, argv, ARGS)) != -1)
	{
		switch (c)
		{
		  case 'c':
			flags |= CHECK_PREVERB;
			break;
		  case 'I':
			set_lang(ITALIAN);
			break;
		  case 'L':
			set_lang(LATIN);
			break;
		  case 'i':
			flags |= SHOW_FULL_INFO;
			break;
		  case 'x':
			flags |= LEXICON_OUTPUT;
			break;
		  case 'V':
			flags |= VERBS_ONLY;
			break;
		  case 'S':
			flags &= ~(STRICT_CASE);
			break;
		  case 'p':
			flags |= PARSE_FORMAT;
			break;
		  case 'm':
			SetMorphPath(optarg);
			break;
		  default:
			errflg++;
			break;
		}
	}
	*/

	/* process input */
	int	nwords = 0;

	/* for each word in line */
	char*	word = strtok(line, " \t");
	for (; word; word = strtok(NULL, " \t"))
	{
		cleanstring(word);
		if (!*word)
			continue;
		if (nwords == 0)
			printf("<words>\n");

		if (!alpheiosCheckstring(word, flags, stream))
		{
			printf("<unknown xml:lang=");
			if (cur_lang() == GREEK)
				printf("\"grc-x-beta\"");
			else if (cur_lang() == LATIN)
				printf("\"lat\"");
			printf(">%s</unknown>\n", word);
		}
		++nwords;
	}

	if (nwords == 0)
	{
		/* printf("<error>No words</error>\n"); */
		return NULL;
	}
	else
	{
		fprintf(stream, "</words>\n");
	}

	fflush(stream); /*  Updates 'buf' and 'len' */
	fclose(stream); /* Finalizes 'buf' and 'len', closes the stream */

	return buf;
}

/* do analysis and call alpheios print routine */
int	alpheiosCheckstring(const char* string, PrntFlags prntflags, FILE* fout)
{
	gk_word * gkword = NULL;

	if (is_blank(string))
		return(0);
	if (strlen(string) >= MAXWORDSIZE)
		return(0);

	gkword = (gk_word*) CreatGkword(1);

	set_dialect(gkword,WantDialects);
	set_workword(gkword,string);
	set_prntflags(gkword,prntflags);
	set_rawword(gkword,workword_of(gkword));
	if (cur_lang() != ITALIAN)
		standword(workword_of(gkword));
	stand_phonetics(gkword);

	checkstring1(gkword);

	int	nanals = totanal_of(gkword);
	if (prntflags && (nanals > 0))
	{
		alpheiosPrintWord(gkword, prntflags, fout);
	}
	FreeGkword(gkword);

	return(nanals);
}

/* clean string: lowercase and strip trailing digits */
void	cleanstring(char *s)
{
	char*	ptr = s + strlen(s);
	while ((ptr > s) && isdigit(*--ptr))
		*ptr = '\0';

	char*	endPtr = s + strlen(s);
	for (ptr = s; ptr < endPtr; ++ptr)
		*ptr = tolower(*ptr);
}
